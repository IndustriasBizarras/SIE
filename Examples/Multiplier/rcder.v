module rcder(in_B, clk, shift, load, lsb_B);
  input [7:0]in_B;
  input clk;
  input load;
  input shift;
  output lsb_B;
  reg [7:0] tmp;

always @(posedge clk or posedge load)
  if(load)
    tmp=in_B;     
  else
   begin
    if(shift)
      tmp = {1'b0,tmp[7:1]};
    else 
      tmp = tmp;
    end
  assign lsb_B = tmp[0];
endmodule
