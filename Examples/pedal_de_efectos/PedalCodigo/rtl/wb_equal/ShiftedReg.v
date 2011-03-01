`timescale 1ns / 1ps

module ShiftedReg(

input [7:0] adcin,
input clk,
input RDYadc,



output reg [7:0]outshift0,
output reg [7:0]outshift1,
output reg [7:0]outshift2,
output reg [7:0]outshift3,
output reg [7:0]outshift4,
output reg [7:0]outshift5,
output reg [7:0]outshift6,
output reg [7:0]outshift7,
output reg [7:0]outshift8,
output reg [7:0]outshift9,
output reg [7:0]outshift10,
output reg [7:0]outshift11,
output reg [7:0]outshift12,
output reg [7:0]outshift13,
output reg [7:0]outshift14,
output reg [7:0]outshift15,
output reg RDYshift

    );
	 
reg [7:0]reg0,reg1,reg2,reg3,reg4,reg5,reg6,reg7,reg8,reg9,reg10,reg11,reg12,
			 reg13,reg14,reg15;
reg rdyreg, reset;


initial begin
reg0 <= 0;
reg1 <= 0;
reg2 <= 0;
reg3 <= 0;
reg4 <= 0;
reg5 <= 0;
reg6 <= 0;
reg7 <= 0;
reg8 <= 0;
reg9 <= 0;
reg10 <= 0;
reg11 <= 0;
reg12 <= 0; 
reg13 <= 0;
reg14 <= 0;
reg15 <= 0; 
RDYshift <= 0;
rdyreg <= 0;
reset<=0;

outshift0 <= 0;
outshift1 <= 0;
outshift2 <= 0;
outshift3 <= 0;
outshift4 <= 0;
outshift5 <= 0;
outshift6 <= 0;
outshift7 <= 0;
outshift8 <= 0;
outshift9 <= 0;
outshift10 <= 0;
outshift11 <= 0;
outshift12 <= 0;
outshift13 <= 0;
outshift14 <= 0;
outshift15 <= 0;
end
	 
always @(posedge clk) begin
		
		if(reset) begin
			outshift0 <= 0;
			outshift1 <= 0;
			outshift2 <= 0;
			outshift3 <= 0;
			outshift4 <= 0;
			outshift5 <= 0;
			outshift6 <= 0;
			outshift7 <= 0;
			outshift8 <= 0;
			outshift9 <= 0;
			outshift10 <= 0;
			outshift11 <= 0;
			outshift12 <= 0;
			outshift13 <= 0;
			outshift14 <= 0;
			outshift15 <= 0;
			end else reset <=0;

		if (RDYadc)begin
			if(reg0 == adcin) RDYshift <= 1;
			else begin	
				reg15 <= reg14;
				reg14 <= reg13;
				reg13 <= reg12;
				reg12 <= reg11;
				reg11 <= reg10;
				reg10 <= reg9;
				reg9 <= reg8;
				reg8 <= reg7;
				reg7 <= reg6;
				reg6 <= reg5;
				reg5 <= reg4;
				reg4 <= reg3;
				reg3 <= reg2;
				reg2 <= reg1;
				reg1 <= reg0;
				reg0 <= adcin;
				rdyreg <= 1'b1;
				end
			end else rdyreg <= 0;
			
		if(rdyreg)begin
		outshift0 <= reg0;
		outshift1 <= reg1;
		outshift2 <= reg2;
		outshift3 <= reg3;
		outshift4 <= reg4;
		outshift5 <= reg5;
		outshift6 <= reg6;
		outshift7 <= reg7;
		outshift8 <= reg8;
		outshift9 <= reg9;
		outshift10 <= reg10;
		outshift11 <= reg11;
		outshift12 <= reg12;
		outshift13 <= reg13;
		outshift14 <= reg14;
		outshift15 <= reg15;
		RDYshift <= 1;
		end else begin 
						RDYshift <= 0;   
						reset <= 1;
						end
		
		end
	
endmodule
