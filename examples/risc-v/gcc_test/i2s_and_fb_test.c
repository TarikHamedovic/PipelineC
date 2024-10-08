#include <stdint.h>
#include <stdlib.h>
#include "mem_map.h"

// FFT algorithm demo code
#include "fft_demo.h"

// Some helper drawing code 
// Rect from Dutra :) (has text console stuff too!?)
void drawRect(int start_x, int start_y, int end_x, int end_y, uint8_t color){
    pixel_t p = {color, color, color, color};
    for (int32_t i = start_x; i < end_x; i++)
    {
        for (int32_t j = start_y; j < end_y; j++)
        {
            frame_buf_write(i,j,p);
        }
    }
}

// Spectrum is rect bins
#define N_BINS (NFFT/2)
void draw_spectrum(int width, int height, float* pwr_bins){
  // Remember the power value from last time to make updates faster
  static int last_height[N_BINS] = {0};
  // How wide is each bin in pixels
  int bin_width = width / N_BINS;
  #if N_BINS > FRAME_WIDTH
  #error "Fix int math for bin width"
  #endif
  // Max FFT value depends on if input is complex tone or not?
  // (Max=nfft/2)(*2 for complex tone input?)
  static float max_pwr = 1.0; // adjusts to fit max seen over time
  for (size_t b = 0; b < N_BINS; b++)
  {
    int x_start = b * bin_width;
    int x_end = (b+1) * bin_width;
    if(pwr_bins[b] > max_pwr) max_pwr = pwr_bins[b];
    int bin_height = (pwr_bins[b]/max_pwr) * height;
    uint8_t color = 0;
    int y_start = 0;
    int y_end = 0;
    // Calculate bounds for this bin
    // (recall 0,0 is top left)
    // Increase rect height or shorten?
    if(bin_height > last_height[b]){
      // Increase height, draw white
      y_start = height - bin_height;
      y_end = height - last_height[b];
      color = 255;
    }else{
      // Decrease height, draw black
      y_start = height - last_height[b];
      y_end =  height - bin_height;
      color = 0;
    }

    // Rect with proper y bounds
    drawRect(x_start, y_start, x_end, y_end, color);

    // Store power for next time
    last_height[b] = bin_height;
  }
}
// Waveform is n pixel wide rects to form line
void draw_waveform(int width, int height, int line_width, fft_in_t* input_samples){
  // line_width used in y height direction
  // How wide is each point forming line
  int point_width = width / NFFT;
  if(point_width <= 0) point_width = 1;
  int half_height = height / 2;
  int y_mid = half_height;
  // Remember the amplitude value from last time to make updates faster
  static int last_y_value[NFFT] = {0};
  for (size_t i = 0; i < NFFT; i++)
  {
    // Calc x position, gone too far?
    int x_start = i * point_width;
    int x_end = (i+1) * point_width;
    if(x_end>FRAME_WIDTH) break;
    // Calc line current y pos
    #ifdef FFT_TYPE_IS_FLOAT
    int ampl = (int)(half_height * input_samples[i].real);
    #endif
    #ifdef FFT_TYPE_IS_FIXED
    int ampl = (half_height * input_samples[i].real)/INT16_MAX;
    #endif
    ampl = ampl * 2; // Scale x2 since rarely near max vol (TODO auto adjust ampl scale?)
    int y_val = y_mid - ampl; // y inverted 0,0 top left
    if(y_val < 0) y_val = 0;
    if(y_val > height) y_val = height;
    // Erase old line portion to black
    drawRect(x_start, last_y_value[i], x_end, last_y_value[i]+line_width, 0);
    // Calc new line position and draw white
    drawRect(x_start, y_val, x_end, y_val+line_width, 255);
    // Save y value for next time
    last_y_value[i] = y_val;
  }
}

void main() {
  //int count = 0;
  // Clear screen to black
  drawRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT, 0);
  while(1){
    *LED = 0; //mm_status_regs->i2s_rx_out_desc_overflow;
    
    // Read i2s samples (in DDR3 off chip)
    i2s_sample_in_mem_t* samples = NULL;
    int n_samples = 0;
    i2s_read(&samples, &n_samples);

    *LED = (1<<0);

    // Copy samples into buffer and convert to input type as needed (in BRAM)
    fft_in_t fft_input_samples[NFFT] = {0};
    for (size_t i = 0; i < NFFT; i++)
    {
      #ifdef FFT_TYPE_IS_FLOAT
      fft_input_samples[i].real = (float)samples[i].l/(float)(1<<24);
      fft_input_samples[i].imag = 0;
      #endif
      #ifdef FFT_TYPE_IS_FIXED
      fft_input_samples[i].real = samples[i].l >> (24-16);
      fft_input_samples[i].imag = 0;
      #endif
    }

    *LED = (1<<1);

    // Compute FFT
    fft_out_t fft_output[NFFT] = {0};
    compute_fft_cc(fft_input_samples, fft_output, NFFT);
    
    *LED = (1<<2);

    // Compute power
    float fft_output_pwr[NFFT] = {0};
    for (uint32_t i = 0; i < NFFT; i++)
    {
        #ifdef FFT_TYPE_IS_FIXED
        float re = (float)fft_output[i].real / (float)INT16_MAX;
        float im = (float)fft_output[i].imag / (float)INT16_MAX;
        #endif
        #ifdef FFT_TYPE_IS_FLOAT
        float re = fft_output[i].real;
        float im = fft_output[i].imag;
        #endif
        float pwr2 = (re*re) + (im*im);
        float pwr = sqrtf(pwr2);
        //printf("i,re,im,p,%d,%f,%f,%f\n", i, re, im, pwr);
        fft_output_pwr[i] = pwr;
    }

    *LED = (1<<3);
    
    // Screen coloring result
    // Only use positive freq power in first half of array
    draw_spectrum(FRAME_WIDTH, FRAME_HEIGHT, fft_output_pwr);
    // Time domain waveform across top half of display
    draw_waveform(FRAME_WIDTH, FRAME_HEIGHT/2, 2, fft_input_samples);
    //count += 1;
  }
}