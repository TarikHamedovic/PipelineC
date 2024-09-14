// pipelinec_top.v
module pipelinec_top(
  input clk,
  output led
);

  wire blink_output;


  blink_0clk_a5a1cd4e blink_inst (
    .clk(clk),
    .clock_enable(1'b1),
    .return_output(blink_output)
  );

  assign led = blink_output;

endmodule
