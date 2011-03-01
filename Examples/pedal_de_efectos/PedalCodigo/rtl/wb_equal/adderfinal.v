`timescale 1ns / 1ps
module adderfinal(

input clk,
input [19:0] inBass, 
input [22:0] inHIGH,
input RDYctrlbass,
input RDYctrlhigh,

output reg RDYeq,
output reg [23:0]eqbass 

);

reg [22:0]rtem;
reg rdy1;
 

initial begin
RDYeq <=0;
eqbass <= 0;
rdy1 <= 0;
rtem <= 0;
end

always @(posedge clk) begin
		
	if (RDYctrlbass && RDYctrlhigh) begin
		
			if(inHIGH[22]) begin
				rtem <= (~inHIGH)+1;
				eqbass <= inBass - rtem;
				rdy1 <= 1;
				end
				else begin 
					rtem <= inHIGH;
					eqbass <= inBass + rtem;
					rdy1 <= 1;
					end	
			if (rdy1) RDYeq <= 1;
			else RDYeq <= 0;
		end else if (rdy1) begin
							RDYeq <= 1;
							rdy1 <= 0;
							end else begin
									RDYeq <= 0;
									rdy1 <= 0;
									eqbass <= 0;
									rtem <= 0;
									end
							
	end 

endmodule
