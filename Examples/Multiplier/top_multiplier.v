module top_multiplier(clk, reset, start, in_A, in_B, pp);

  input clk;
  input reset;
  input start;
  input [7:0]in_A;
  input [7:0]in_B;
  output [15:0]pp;

  wire w_load_rst;
  wire w_shift_inc;
  wire w_acc;
  wire w_lsb_B;
  wire w_out_comp; 
  wire [3:0]w_in_tmp;
  wire [15:0]w_A;
  
  acumulador   acu  (.A(w_A), .clk(clk), .acc(w_acc), .rst(w_load_rst), .pp(pp));
  comp         com  (.in_tmp(w_in_tmp), .out_comp(w_out_comp));
  contador     con  (.clk(clk), .rst(w_load_rst), .inc(w_shift_inc), .out_count(w_in_tmp));
  control      ctrl (.clk(clk), .lsb_B(w_lsb_B), .start(start), .reset(reset), .out_comp(w_out_comp), .load_rst(w_load_rst), .shift_inc(w_shift_inc), .acc(w_acc));
  rcder        rcd  (.in_B(in_B), .clk(clk), .shift(w_shift_inc), .load(w_load_rst), .lsb_B(w_lsb_B));
  rcizq        rci  (.in_A(in_A), .clk(clk), .load(w_load_rst), .shift(w_shift_inc), .A(w_A));

endmodule


