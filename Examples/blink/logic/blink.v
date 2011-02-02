`timescale 1ns / 1ps
module blink(clk, reset, led);
  input            clk, reset;
  output           led;

  reg [24:0]  counter;
  always @(posedge clk) begin
    if (~reset)
      counter <= {25{1'b0}};
    else
      counter <= counter + 1;
  end 
  assign led = counter[24];

endmodule

