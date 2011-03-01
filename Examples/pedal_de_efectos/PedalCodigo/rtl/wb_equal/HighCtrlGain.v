`timescale 1ns / 1ps
module HighCtrlGain(
    
input [22:0] inHigh,
input clk,
input [2:0] gainH,
input RDYaddhigh,

output reg RDYctrlhigh,	 
output reg [22:0] outHigh

	 );

reg [22:0] rgain1;
reg [22:0] rgain2;
reg rtem;

initial begin

outHigh <= 0;
rgain1 <= 0;
rgain2 <= 0;
RDYctrlhigh <= 0;
rtem <= 0;

end

always @(posedge clk) begin
	
	if(RDYaddhigh) begin 
		case(gainH)
			 
			3'b000: begin 
					if (inHigh[22]) begin
					rgain1 <= (~inHigh+1);
					outHigh <= (~rgain1+1)/128;
					rtem <= 1;
					end else	begin 
							rgain1 <= inHigh[22:7];
							outHigh <= rgain1;
							rtem <= 1;		
							end
					end		

			3'b001: begin 
					if (inHigh[22]) begin
					rgain1 <= (~inHigh+1);
					outHigh <= (~rgain1+1)/64;
					rtem <= 1;
					end else	begin
							rgain1[16:0] <= inHigh[22:6];
							outHigh <= rgain1;
							rtem <= 1;	
							end
					end 	
				
			3'b010:	begin 
					if (inHigh[22]) begin
					rgain1 <= (~inHigh+1);
					outHigh <= (~rgain1+1)/32;
					rtem <= 1;
					end else	begin 
							rgain1[17:0] <= inHigh[22:5];
							outHigh <= rgain1;
							rtem <= 1;	
							end
					end 	
				
			3'b011:	begin 
					if (inHigh[22]) begin
					rgain1 <= (~inHigh+1);
					outHigh <= (~rgain1+1)/16;
					rtem <= 1;
					end else	begin 
						rgain1[18:0] <= inHigh[22:4]; 
						outHigh <= rgain1;
                  rtem <= 1; 
						end		
 					end 	
				
			3'b100:begin 
					if (inHigh[22]) begin
					rgain1 <= (~inHigh+1);
					outHigh <= (~rgain1+1)/8;
					rtem <= 1;
					end else begin	
						rgain1[19:0] <= inHigh[22:3]; 
						outHigh <= rgain1;
					   RDYctrlhigh <= 1;
						end
					end 		
			
			3'b101:begin 
					if (inHigh[22]) begin
					rgain1 <= (~inHigh+1);
					outHigh <= (~rgain1+1)/4;
					rtem <= 1;
					end else	begin 
						rgain1[20:0] <= inHigh[22:2]; 
						outHigh <= rgain1;
					   rtem <= 1;
						end
					end 	 
			
			3'b110:begin 
					if (inHigh[22]) begin
					rgain1 <= (~inHigh+1);
					outHigh <= (~rgain1+1)/2;
					rtem <= 1;
					end else	begin
						rgain1[21:0] <= inHigh[22:1]; 
						outHigh <= rgain1;
					   rtem <= 1;
						end
					end 	 
			
			3'b111: 	begin 
					if (inHigh[22]) begin
					rgain1 <= inHigh;
					outHigh <= rgain1;
					rtem <= 1;
					end else	begin
						rgain1 <= inHigh; 
						outHigh <= rgain1;
						rtem <= 1;
						end
					end 				
			endcase
			
			if (rtem)RDYctrlhigh <= 1;
			else RDYctrlhigh <= 0;
			
		end else begin
					if (rtem) begin
						RDYctrlhigh <= 1;
						rtem <= 0;
						end else begin 
									RDYctrlhigh <= 0;
									outHigh <= 0;
									rgain1 <= 0;
									end
								end
	end 
	

endmodule