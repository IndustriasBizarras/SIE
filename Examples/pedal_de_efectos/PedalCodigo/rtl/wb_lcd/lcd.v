
module lcd (

    input clk,
    input reset,
    input [7:0] Data_in,
    input [7:0] Address_in,
    input [7:0] Control_in,		//0 for Instruction
//Lcd Interface
    output reg RS,
    output RW,
    output reg E,
    output reg [7:0] Data_out,
//status
    output reg [7:0] status,
    output reg [9:0] sel_out
);
	 
	 reg [2:0] A;
	 reg [3:0] B;
	 reg [7:0] cont;
	reg clk_lcd;
	reg [7:0]cont_lcd;
	 
	 assign RW = 0;
	 
	 initial begin
	 RS=0;
	 E=0;
	 A=0;
	 B=0;
	 cont=0;
	 Data_out=0;
	 status=0;
	 sel_out=0;
	 clk_lcd=0;
	 end


/*always @ (clk) begin
if (cont_lcd<10)
	cont_lcd<=cont_lcd+1;
		else begin
		cont_lcd<=0;
		clk_lcd<=~clk_lcd;
		end
end
*/
always @(posedge clk) begin		

  if (reset)	begin
  
	A<=0;
	B<=0;
	Data_out<=0;
	RS<=0;
	E<=0;
	status<=0;
	sel_out<=0;

  end else begin
	
	if (Control_in == 8'h05) begin				//Instruction Cycle
	
		case (A)		
	    	  3'd0: begin
				RS<=0;
				A<=1;
				status<=8'h08;		//08 inst cycle							
		          end
		    3'd1: begin
				E<=1;
				A<=2;									
		          end
		    3'd2: begin
				Data_out <= Data_in;
				A<=3;
		            end
		    3'd3: begin  
				if(cont<8'd22)			//Enable High level width tpw
					cont<=cont+1;		
					else begin
						cont<=0;
						A<=4;
					end
			  end
		    3'd4: begin
				E<=0;
				A<=5;									
		           end
		    3'd5: begin
				if(cont<8'd95)			//Data Hold and Enable Cycle delay
					cont<=cont+1;		
					else begin
						cont<=0;
						A<=6;
					end			  
			  end
	    	    3'd6: begin
				RS<=0;
				A<=0;
				status<=8'h01;					//Finished instr cycle				
				sel_out<=sel_out+1;
		          end
			default : A<=0;
	    endcase


	end else if (Control_in == 8'h06) begin				//Data Cycle
		
		case (B)		
		    4'd0: begin
				RS<=0;			//0
				B<=1;
				status<=8'h04;				//04 for data cycle					
		          end
		    4'd1: begin
				E<=1;
				B<=2;									
		          end
		    4'd2: begin
				Data_out <= Address_in;
				B<=3;
		            end
		    4'd3: begin  
				if(cont<8'd22)			//Enable High level width tpw
					cont<=cont+1;		
					else begin
						cont<=0;
						B<=4;
					end
			  end
		    4'd4: begin
				E<=0;
				B<=5;									
		           end
		    4'd5: begin
				if(cont<8'd95)			//Data Hold and Enable Cycle delay
					cont<=cont+1;		
					else begin
						cont<=0;
						B<=6;
					end			  
			  end
	    	    4'd6: begin
				RS<=1;
				B<=7;
		          end
		    4'd7: begin
				E<=1;
				B<=8;									
		          end
		    4'd8: begin
				Data_out <= Data_in;
				B<=9;
		            end
		    4'd9: begin  
				if(cont<8'd22)			//Enable High level width tpw
					cont<=cont+1;		
					else begin
						cont<=0;
						B<=10;
					end
			  end
		    4'd10: begin
				E<=0;
				B<=11;									
		           end
		    4'd11: begin
				if(cont<8'd95)			//Data Hold and Enable Cycle delay
					cont<=cont+1;		
					else begin
						cont<=0;
						B<=12;
					end			  
			  end
	    	  4'd12: begin
				RS<=1;
				B<=0;
				status<=8'h02;
				sel_out<=sel_out+1;			//data cycle complete
		          end
	    endcase

	end else if (Control_in == 8'h00) status<=8'h00;		//Ready for input
		else status<=8'hE0;		//Return Control_Invalid
	end
end
endmodule
