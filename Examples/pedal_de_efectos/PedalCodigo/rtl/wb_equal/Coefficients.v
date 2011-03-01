`timescale 1ns / 1ps
module CoefficientBass(
    
input [7:0] datain0,	 
input [7:0] datain1,
input [7:0] datain2,
input [7:0] datain3,
input [7:0] datain4,
input [7:0] datain5,
input [7:0] datain6,
input [7:0] datain7,
input [7:0] datain8,
input [7:0] datain9,
input [7:0] datain10,
input [7:0] datain11,
input [7:0] datain12,
input [7:0] datain13,
input [7:0] datain14,
input [7:0] datain15,
input clk,
input RDYshift,

output reg [16:0] dataoutb0,
output reg [16:0] dataoutb1,
output reg [16:0] dataoutb2,
output reg [16:0] dataoutb3,
output reg [16:0] dataoutb4,
output reg [16:0] dataoutb5,
output reg [16:0] dataoutb6,
output reg [16:0] dataoutb7,
output reg [16:0] dataoutb8,
output reg [16:0] dataoutb9,
output reg [16:0] dataoutb10,
output reg [16:0] dataoutb11,
output reg [16:0] dataoutb12,
output reg [16:0] dataoutb13,
output reg [16:0] dataoutb14,
output reg [16:0] dataoutb15,
output reg RDYcoeBass
	
	 );

parameter b0 = 3;
parameter b1 = 8;
parameter b2 = 19;
parameter b3 = 40;
parameter b4 = 69;
parameter b5 = 101;
parameter b6 = 128;
parameter b7 = 143;

initial begin

dataoutb0 <= 0;
dataoutb1 <= 0;
dataoutb2 <= 0;
dataoutb3 <= 0;
dataoutb4 <= 0;
dataoutb5 <= 0;
dataoutb6 <= 0;
dataoutb7 <= 0;
dataoutb8 <= 0;
dataoutb9 <= 0;
dataoutb10 <= 0;
dataoutb11 <= 0;
dataoutb12 <= 0;
dataoutb13 <= 0;
dataoutb14 <= 0;
dataoutb15 <= 0;
RDYcoeBass <= 0;

end


always @(posedge clk) begin
	
	if(RDYshift) begin
			dataoutb0 <= b0*datain0;
			dataoutb1 <= b1*datain1;
			dataoutb2 <= b2*datain2;
			dataoutb3 <= b3*datain3;
			dataoutb4 <= b4*datain4;
			dataoutb5 <= b5*datain5;
			dataoutb6 <= b6*datain6;
			dataoutb7 <= b7*datain7;
			dataoutb8 <= b7*datain8;
			dataoutb9 <= b6*datain9;
			dataoutb10 <= b5*datain10;
			dataoutb11 <= b4*datain11;
			dataoutb12 <= b3*datain12;
			dataoutb13 <= b2*datain13;
			dataoutb14 <= b1*datain14;
			dataoutb15 <= b0*datain15;
			RDYcoeBass <= 1;
			end else begin
						RDYcoeBass <= 0;
						dataoutb0 <= 0;
						dataoutb1 <= 0;
						dataoutb2 <= 0;
						dataoutb3 <= 0;
						dataoutb4 <= 0;
						dataoutb5 <= 0;
						dataoutb6 <= 0;
						dataoutb7 <= 0;
						dataoutb8 <= 0;
						dataoutb9 <= 0;
						dataoutb10 <= 0;
						dataoutb11 <= 0;
						dataoutb12 <= 0;
						dataoutb13 <= 0;
						dataoutb14 <= 0;
						dataoutb15 <= 0;
						end
		end	
endmodule
