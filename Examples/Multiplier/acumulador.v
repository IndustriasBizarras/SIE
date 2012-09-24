module acumulador(A, clk, acc, rst, pp);
  input [15:0] A;
  input clk;
  input acc;
  input rst; 
  output [15:0] pp;
  reg [15:0] temporal;

always @(posedge clk or posedge rst)
  if (rst) 
   temporal = 16'h0000;
  else
     begin
      if (acc)
       temporal = temporal + A;
      else
       temporal = temporal;
     end
assign pp = temporal;
endmodule
