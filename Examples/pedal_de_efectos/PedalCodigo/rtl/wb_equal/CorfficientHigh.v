`timescale 1ns / 1ps
module CoefficientHigh(
    
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

output reg [17:0] dataouth0,
output reg [17:0] dataouth1,
output reg [17:0] dataouth2,
output reg [17:0] dataouth3,
output reg [17:0] dataouth4,
output reg [17:0] dataouth5,
output reg [17:0] dataouth6,
output reg [17:0] dataouth7,
output reg [17:0] dataouth8,
output reg [17:0] dataouth9,
output reg [17:0] dataouth10,
output reg [17:0] dataouth11,
output reg [17:0] dataouth12,
output reg [17:0] dataouth13,
output reg [17:0] dataouth14,
output reg [17:0] dataouth15,
output reg RDYcoehigh
	
	 );

parameter h0 = 6;
parameter h1 = 3;
parameter h2 = 8;
parameter h3 = 55;
parameter h4 = 2;
parameter h5 = 109;
parameter h6 = 165;
parameter h7 = 492;

initial begin
dataouth0 <= 0;
dataouth1 <= 0;
dataouth2 <= 0;
dataouth3 <= 0;
dataouth4 <= 0;
dataouth5 <= 0;
dataouth6 <= 0;
dataouth7 <= 0;
dataouth8 <= 0;
dataouth9 <= 0;
dataouth10 <= 0;
dataouth11 <= 0;
dataouth12 <= 0;
dataouth13 <= 0;
dataouth14 <= 0;
dataouth15 <= 0;
RDYcoehigh <= 0;
end

always @(posedge clk) begin
	
	if(RDYshift)begin 
		dataouth0 <= h0*datain0;
		dataouth1 <= h1*datain1;
		dataouth2 <= h2*datain2;
		dataouth3 <= h3*datain3;
		dataouth4 <= h4*datain4;
		dataouth5 <= h5*datain5;
		dataouth6 <= h6*datain6;
		dataouth7 <= h7*datain7;
		dataouth8 <= h7*datain8;
		dataouth9 <= h6*datain9;
		dataouth10 <= h5*datain10;
		dataouth11 <= h4*datain11;
		dataouth12 <= h3*datain12;
		dataouth13 <= h2*datain13;
		dataouth14 <= h1*datain14;
		dataouth15 <= h0*datain15;
		RDYcoehigh <= 1;
		end else begin
					dataouth0 <= 0;
					dataouth1 <= 0;
					dataouth2 <= 0;
					dataouth3 <= 0;
					dataouth4 <= 0;
					dataouth5 <= 0;
					dataouth6 <= 0;
					dataouth7 <= 0;
					dataouth8 <= 0;
					dataouth9 <= 0;
					dataouth10 <= 0;
					dataouth11 <= 0;
					dataouth12 <= 0;
					dataouth13 <= 0;
					dataouth14 <= 0;
					dataouth15 <= 0;
					RDYcoehigh <= 0;
				end
	end


endmodule
