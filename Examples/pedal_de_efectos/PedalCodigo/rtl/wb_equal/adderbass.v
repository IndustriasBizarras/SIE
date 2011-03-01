`timescale 1ns / 1ps

module adderbass(

input clk, 

input [16:0]inBass0,
input [16:0]inBass1,
input [16:0]inBass2,
input [16:0]inBass3,
input [16:0]inBass4,
input [16:0]inBass5,
input [16:0]inBass6,
input [16:0]inBass7,
input [16:0]inBass8,
input [16:0]inBass9,
input [16:0]inBass10,
input [16:0]inBass11,
input [16:0]inBass12,
input [16:0]inBass13,
input [16:0]inBass14,
input [16:0]inBass15,
input RDYcoeBass,

output reg [19:0] outBASS,    
output reg RDYaddBass	 
	 );

initial begin 

outBASS <= 0;
RDYaddBass <=0;
end
	
always @(posedge clk) begin
	
		if (RDYcoeBass)begin
			outBASS <= inBass0+inBass1+inBass2+inBass3+inBass4+inBass5+inBass6+
						  inBass7+inBass8+inBass9+inBass10+inBass11+inBass12+inBass13+
						  inBass14+inBass15;
		RDYaddBass <= 1;		
			
	end else begin
			RDYaddBass <= 1;
			outBASS <= 0;
			end

end 
endmodule

