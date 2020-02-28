// Code wrapping AXI4 (FPGA) hardware to a common 'DMA message' 

#include "../../axi.h"
#include "dma_msg.h"

// !!!!!!!  WARNING: !!!!!!!!!!!
//		THIS IMPLEMENTATION DOES NOT HAVE FLOW CONTROL LOGIC.
//		ASSUMES ALWAYS READY FOR INPUT AND OUTPUT.

// DMA data comes in chunks of 64B
#define DMA_WORD_SIZE 64
#define DMA_MSG_WORDS (DMA_MSG_SIZE/DMA_WORD_SIZE)
typedef struct dma_word_buffer_t
{
   uint8_t words[DMA_MSG_WORDS][DMA_WORD_SIZE];
} dma_word_buffer_t;

// Unpack word array into byte array
dma_msg_t deserializer_unpack(dma_word_buffer_t word_buffer)
{
  // Unpack 2D byte array word buffer into long 1D output byte array
	dma_msg_t msg;
	uint32_t word_i;
	uint32_t byte_i;
	for(word_i=0;word_i<DMA_MSG_WORDS;word_i=word_i+1)
	{
		for(byte_i=0;byte_i<DMA_WORD_SIZE;byte_i=byte_i+1)
		{
			msg.data[(word_i*DMA_WORD_SIZE)+byte_i] = word_buffer.words[word_i][byte_i];
		}
	}
	return msg;
}

// Parse input AXI-4 to a wider lower duty cycle message stream
dma_msg_size_t deserializer_word_pos;
dma_word_buffer_t deserializer_msg_buffer;
dma_msg_s deserializer(axi512_i_t axi)
{
	// Circular buffer
	// Read word from front/top (upper addr word) of circular buff
	uint8_t word[DMA_WORD_SIZE];
	word = deserializer_msg_buffer.words[DMA_MSG_WORDS-1];

	// Write incoming data to byte location in word
	uint32_t byte_i;
	byte_i = 0;
	for(byte_i=0; byte_i<DMA_WORD_SIZE; byte_i=byte_i+1)
	{
		if(axi.wstrb[byte_i])
		{
			word[byte_i] = axi.wdata[byte_i];
		}
	}
	
	// Handle the write data if valid
	if(axi.wvalid)
	{
		// Write modified word back into buffer
		deserializer_msg_buffer.words[DMA_MSG_WORDS-1] = word;
		// If current word high bytes written then next bytes will be for next word
		if(axi.wstrb[DMA_WORD_SIZE-1])
		{
			// Increment pos for next word
			deserializer_word_pos = deserializer_word_pos + 1;
			// Shift circular buffer to make room for next word if this is not the last word
			if(deserializer_word_pos != DMA_MSG_WORDS)
			{
				uint8_t word0[DMA_WORD_SIZE];
				word0 = deserializer_msg_buffer.words[0];
				uint32_t word_i;
				for(word_i=0; word_i<DMA_MSG_WORDS-1; word_i=word_i+1)
				{
					deserializer_msg_buffer.words[word_i] = deserializer_msg_buffer.words[word_i+1];
				}
				deserializer_msg_buffer.words[DMA_MSG_WORDS-1] = word0;
			}
		}
	}
	
	// Unpack message data from word buffer
	dma_msg_s msg;
	msg.data = deserializer_unpack(deserializer_msg_buffer);
	
	// Message done/valid?
	msg.valid = 0;
	if(deserializer_word_pos == DMA_MSG_WORDS)
	{
		// Validate output message
		msg.valid = 1;
		// Reset pos
		deserializer_word_pos = 0;
	}

  return msg;
}

// Pack byte array into word array buffer
dma_word_buffer_t serializer_pack(dma_msg_t msg)
{
	dma_word_buffer_t word_buffer;
	uint32_t word_i;
	uint32_t byte_i;
	for(word_i=0;word_i<DMA_MSG_WORDS;word_i=word_i+1)
	{
		for(byte_i=0;byte_i<DMA_WORD_SIZE;byte_i=byte_i+1)
		{
			word_buffer.words[word_i][byte_i] = msg.data[(word_i*DMA_WORD_SIZE)+byte_i];
		}
	}
	return word_buffer;
}

// Serialize messages as AXI
// 1. Respond to writes immediately 
// 2. Buffer incoming DMA messages to serialize
// 3. Since no flow control 
//		N reads can show up back to back repsenting 
//    the software read of the enitre DMA_MSG_SIZE bytes
//    Store/fifo these and respond to each correctly
typedef struct serializer_read_request_t
{
   dma_msg_size_t burst_words;
   uint1_t valid;
} serializer_read_request_t;
typedef enum serializer_state_t {
	GET_READ_REQ,
	SERIALIZE
} serializer_state_t;
#define SER_READ_REQ_BUFF_SIZE 4 // Back to back reads to buffer
serializer_read_request_t serializer_read_request_buffer[SER_READ_REQ_BUFF_SIZE];
dma_word_buffer_t serializer_msg_buffer;
uint1_t serializer_msg_buffer_valid;
serializer_state_t serializer_state;
serializer_read_request_t serializer_curr_read_request;
dma_msg_size_t serializer_word_pos;
axi512_o_t serializer(dma_msg_s msg, axi512_i_t axi_in)
{	
	// Start by outputing axi_out defaults
	axi512_o_t axi_out;
	// Can't really do good flow control - yet.
  // This is hacky
  // Ready for write address
  axi_out.awready = 1;
	//  Ready for write data 
  axi_out.wready = 1;
  //  Ready for read address
  axi_out.arready = 1;
	axi_out.bvalid = 0; // Invalid write response
	axi_out.bid = 0;
	axi_out.bresp = 0; // Error code
	axi_out.rvalid = 0; // Invalid read response
	axi_out.rid = 0;
	axi_out.rresp = 0;
	axi_out.rlast = 0;
	uint8_t byte_i;
	for(byte_i=0; byte_i<DMA_WORD_SIZE; byte_i=byte_i+1)
	{
		axi_out.rdata[byte_i] = 0;
	}
	
	// Respond to DMA writes immediately
	if(axi_in.wvalid & axi_in.wlast)
	{
		axi_out.bvalid = 1;
	}
	
	// DMA writes eventually produce an incoming message, buffer it
	if(msg.valid)
	{
		serializer_msg_buffer = serializer_pack(msg.data); // Stored by word
		serializer_msg_buffer_valid = 1;
	}
		
	// Buffer up to N read requests as they come in
	if(axi_in.arvalid)
	{
		// Form new request
		serializer_read_request_t new_read_request;
		// The burst length for AXI4 is defined as,
	  // Burst_Length = AxLEN[7:0] + 1,
		new_read_request.burst_words = axi_in.arlen + 1;
		new_read_request.valid = 1;
		// Put at the end of the shiftreg/buffer (assume empty)
		serializer_read_request_buffer[SER_READ_REQ_BUFF_SIZE-1] = new_read_request;	
	}
	
	// What entry is at the front of the buffer? Maybe used
	serializer_read_request_t next_read_request;
	next_read_request = serializer_read_request_buffer[0];
	
	// Shift out that next request to make room in buffer?
	uint1_t front_empty;
	front_empty = next_read_request.valid == 0;
	// Have msg to serialize and read req buffered?
	uint1_t have_buffers;
	have_buffers = serializer_msg_buffer_valid & next_read_request.valid;
	// And trying to read those buffers?
	uint1_t trying_read_buffers;
	trying_read_buffers = (serializer_state == GET_READ_REQ);
	// Then suceeded at reading front from front
	uint1_t read_good;
	read_good = have_buffers & trying_read_buffers;
	// Shift if front empty or reading good entry from front
	uint1_t do_shift;
	do_shift = front_empty | read_good;
	if(do_shift)
	{
		// Move old data forward
		uint32_t buff_i;
		for(buff_i=0; buff_i < SER_READ_REQ_BUFF_SIZE-1; buff_i = buff_i + 1)
		{
			serializer_read_request_buffer[buff_i] = serializer_read_request_buffer[buff_i+1];
		}
		// To empty spot at end
		serializer_read_request_buffer[SER_READ_REQ_BUFF_SIZE-1].valid = 0;
	}
	
	// Do functionality to respond to reads based on state
	if(serializer_state == GET_READ_REQ)
	{
		// Have a buffers ready?
		if(have_buffers)
		{
			// Then start serializing
			serializer_curr_read_request = next_read_request;
			serializer_state = SERIALIZE;
		}
	}
	else if(serializer_state == SERIALIZE)
	{
		// Select the word from front of buffer
		uint8_t word[DMA_WORD_SIZE];
		word = serializer_msg_buffer.words[0];
				
		// Put it on the bus
		axi_out.rdata = word;
		axi_out.rvalid = 1;
		
		// Increment pos
		serializer_word_pos = serializer_word_pos + 1;
		serializer_curr_read_request.burst_words = serializer_curr_read_request.burst_words - 1;
		// Shift circular buffer
		uint32_t word_i;
		for(word_i=0; word_i<DMA_MSG_WORDS-1; word_i=word_i+1)
		{
			serializer_msg_buffer.words[word_i] = serializer_msg_buffer.words[word_i+1];
		}
		serializer_msg_buffer.words[DMA_MSG_WORDS-1] = word;
		
		// End this serialization?
		if(serializer_curr_read_request.burst_words==0)
		{
			// End the stream and reset
			axi_out.rlast = 1;
			serializer_curr_read_request.valid = 0;
			serializer_state = GET_READ_REQ;
		}
		
		// Done with the whole DMA message?
		if(serializer_word_pos==DMA_MSG_SIZE)
		{
			serializer_msg_buffer_valid = 0;
			serializer_word_pos = 0;
		}
	}  
  
  return axi_out;
}
