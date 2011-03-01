`timescale 1ns / 1ps

module adderhigh(

input clk, 

input [16:0]inHIGH0,
input [16:0]inHIGH1,
input [16:0]inHIGH2,
input [16:0]inHIGH3,
input [16:0]inHIGH4,
input [16:0]inHIGH5,
input [16:0]inHIGH6,
input [16:0]inHIGH7,
input [16:0]inHIGH8,
input [16:0]inHIGH9,
input [16:0]inHIGH10,
input [16:0]inHIGH11,
input [16:0]inHIGH12,
input [16:0]inHIGH13,
input [16:0]inHIGH14,
input [16:0]inHIGH15,
input RDYcoeHigh,

output reg [22:0] outHIGH,    
output reg RDYaddHigh	 
	 );

initial begin 
	outHIGH <= 0;
	RDYaddHigh <= 0;
	end
	
always @(posedge clk) begin
	
	if (RDYcoeHigh)begin
		outHIGH <= inHIGH4-inHIGH0-inHIGH1-inHIGH2-inHIGH3-inHIGH5-inHIGH6+
					  inHIGH7+inHIGH8-inHIGH9-inHIGH10+inHIGH11-inHIGH12-inHIGH13-
					  inHIGH14-inHIGH15;
		RDYaddHigh <= 1;	
		end else begin
					RDYaddHigh <= 0; 
					outHIGH <= 0;
					end
end 

endmodule



