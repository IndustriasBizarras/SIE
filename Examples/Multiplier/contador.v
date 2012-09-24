module contador(clk, rst, inc, out_count);
  input clk; 
  input rst;
  input inc;
  output [3:0] out_count;
  reg [3:0] temporal;
 always @(posedge clk or posedge rst)
     if (rst) temporal = 4'b0000;
      else 
        if (inc)
          temporal = temporal + 1'b1;
      else
          temporal = temporal;
  assign out_count = temporal;
endmodule
