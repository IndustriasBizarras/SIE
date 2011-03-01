module gpio(
		input clk,
		input reset,
		input [3:0]inuser,
		
		output reg[2:0] outuser, //p1 01 ; p2 02; p3 03; p4 04
		output reg gpio_en,
		output reg prueba
    );
reg [15:0]cont; 
reg clk_gpio;
reg gpio_en_temp;
reg flag;

initial begin
cont=0;
outuser=0;
gpio_en_temp=0;
gpio_en=0;
clk_gpio=0;
flag=0;
prueba=0;
end 

//assign prueba=outuser[0];

always @ (posedge clk)begin
			if (reset) begin
			cont<=0;
			flag<=0;
			gpio_en<=0;
			end else begin
					if(cont<25'd50000) begin 			//2ms para evitar el rebote 50000
						cont<=cont+1;
					end else begin
						cont<=0;
						clk_gpio<=~clk_gpio;
					end
					if(~flag && gpio_en_temp) begin
							gpio_en<=1;
							flag<=1;
							end else begin 
									gpio_en<=0;
									if (~gpio_en_temp)
										flag<=0;
									end
				end
end

always @ (posedge clk_gpio) begin

if (reset)begin
			outuser<=0;
			gpio_en_temp<=0;
		end else begin
				case (inuser)
				
				4'b0001: begin
								outuser<=1;
								gpio_en_temp<=1;
								prueba<=1;
							end
				4'b0010: begin
								outuser<=2;
								gpio_en_temp<=1;
								prueba<=1;
							end
				4'b0100: begin
								outuser<=3;
								gpio_en_temp<=1;
								prueba<=1;
							end
				4'b1000: begin 
								outuser<=4;
								gpio_en_temp<=1;
								prueba<=1;
							end
					default: begin 
									gpio_en_temp<=0;
									outuser<=outuser;
									prueba<=0;
								end
				endcase
			end
end
endmodule 
