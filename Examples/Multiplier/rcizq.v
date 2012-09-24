module rcizq(in_A, clk, load, shift, A);
  input [7:0]in_A;
  input clk;
  input load;
  input shift;
  output [15:0]A;
  reg [15:0]tmp;

always @(posedge clk or posedge load)
  if (load)
    tmp={8'h00,in_A};     
  else 
   begin
     if (shift)
       tmp = {tmp[14:0],1'b0};
     else 
       tmp = tmp;
    end
 assign A = tmp;
endmodule       
