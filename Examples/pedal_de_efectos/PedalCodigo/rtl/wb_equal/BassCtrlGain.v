`timescale 1ns / 1ps
module BassCtrlGain(
    
input [19:0] inBass,
input clk,
input [2:0] gainB,
input RDYaddbass,

output reg RDYctrlbass,	 
output reg [19:0] outBass

	 );

reg [19:0] rgain1;
reg rtem;


initial begin

outBass <= 0;
rgain1 <= 0;
RDYctrlbass <= 0;
rtem <= 0;


end

always @(posedge clk) begin
	
	if(RDYaddbass) begin 
		case(gainB)
			 
			3'b000: 	begin 
					rgain1[12:0] <= inBass[19:7];
					outBass <= rgain1;
					rtem <= 1;		
					end
							

			3'b001: begin
					rgain1[13:0] <= inBass[19:6];
					outBass <= rgain1;
					rtem <= 1;	
					end
				
			3'b010:begin 
					rgain1[14:0] <= inBass[19:5];
					outBass <= rgain1;
					rtem <= 1;	
					end
					 	
				
			3'b011:	begin 
					rgain1[15:0] <= inBass[19:4]; 
					outBass <= rgain1;
					rtem <= 1; 
					end		
 						
			3'b100:begin	
					rgain1[16:0] <= inBass[19:3]; 
					outBass <= rgain1;
					RDYctrlbass <= 1;
					end 		
			
			3'b101:begin 
					rgain1[17:0] <= inBass[19:2]; 
					outBass <= rgain1;
					rtem <= 1;
					end
					 	 
			3'b110:begin
					rgain1[18:0] <= inBass[19:1]; 
					outBass <= rgain1;
					rtem <= 1;
					end
					 	 
			
			3'b111: begin
					rgain1 <= inBass; 
					outBass <= rgain1;
					rtem <= 1;
					end
					 				
			endcase
			
			if (rtem)RDYctrlbass <= 1;
			else RDYctrlbass <= 0;
			
		end else begin
					if (rtem) begin
						RDYctrlbass <= 1;
						rtem <= 0;
						end else begin 
									RDYctrlbass <= 0;
									outBass <= 0;
									rgain1 <= 0;
									end
								end
	end 
	

endmodule
