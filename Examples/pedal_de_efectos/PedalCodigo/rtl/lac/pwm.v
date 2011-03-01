module pwm(
	input clk,
	input [7:0] pwmin,
	input [7:0] cspwm,
	input reset,
	output reg pwmout,		//Salida al filtro analogo
	output reg [7:0] status		//1 transmite   0 standby	
	);

reg [8:0] pwmaccumulator;
reg clkpwm;
reg [16:0] cont;


initial begin
status=0;
pwmout=0;
pwmaccumulator=0;
clkpwm=0;
cont=0;
end


//Generador del clock de 4K
always @ (posedge clk)begin

	if(cont<25'd125000)
		cont<=cont+1;
	else begin
		cont<=0;
		clkpwm<=~clkpwm;
		end
end
always @(posedge clkpwm) begin

	if (reset) begin
		pwmout<=0;
		pwmaccumulator<=0;
		status<=0;
		  end else begin
			if (cspwm[0]) begin       //1 Transmite
				pwmaccumulator <= pwmaccumulator[7:0] + pwmin;
				status<=1;
				pwmout <= pwmaccumulator[8];   //bit transmitido
				end else status<=0;
			end
end
endmodule 
