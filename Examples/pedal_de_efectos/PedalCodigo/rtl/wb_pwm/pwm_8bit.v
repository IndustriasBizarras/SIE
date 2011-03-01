module pwm_8bit(
	input clk,
	input [7:0] pwmin,
	input  cspwm,
	input reset,
	input start_tx_in,
//	input data_rdy,
	output reg pwmout,		//Salida al filtro analogo
	output reg [7:0] status		//1 pwm=1 0 pwm=0		
	);

reg [23:0] cont_pwm;
reg [23:0] cont_add;
reg cycle_reset;
reg [7:0] cycle;
reg [23:0] pwmin_temp;
reg start;

initial begin
cont_pwm=0;
cont_add=0;
start=0;
cycle=0;
end

always @ (posedge start_tx_in) begin
start<=1;
end


always @ (posedge clk) begin 


if (cspwm && start) begin

if (reset) begin
	cont_pwm<=0;
	cycle_reset<=0;
	cont_add<=0;
	pwmout<=0;
	cycle<=0;
	end else begin

		if (cont_pwm<12000)			//12000 -> 240uS =4Khz  ---- 6250 -> 125uS = 8kHz
				begin			
				cont_pwm<=cont_pwm+1;
				cycle_reset<=0;		
				end else begin
				cont_pwm<=0;
				cycle_reset<=1;
				end

		if (cycle_reset)
			cycle<=0;
				else 
				cycle<=cycle;

		if (cont_add<46)				
			begin	
			cont_add<=cont_add+1;
			end else begin	
				cont_add<=0;
				if (cycle<pwmin)
					begin
					cycle<=cycle+1;				
					pwmout<=1;
					status<=8'h01;
					end else begin
					pwmout<=0;
					status<=8'h03;	
					end
		end
	end

end

end

endmodule
