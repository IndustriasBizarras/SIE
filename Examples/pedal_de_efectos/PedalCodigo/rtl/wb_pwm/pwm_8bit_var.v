module pwm_8bit_var(
	input clk,
	input [7:0] pwmin,
	input  cspwm,
	input reset,
	input start_tx_in,
//	input data_rdy,
	output reg pwmout,		//Salida al filtro analogo
	output reg [7:0] status,		//1 pwm=1 0 pwm=0	

	// Freq Config Parameters
	input [31:0]time_add,	
	input [31:0]cycle_adder,	
	input [31:0]freq_div
	);
reg [31:0] cont_pwm;
reg [31:0] cont_add;
reg cycle_reset;
reg [7:0] cycle;
reg [7:0] pwmin_temp;
reg start;

initial begin
start=0;
cycle=0;
cont_pwm=0;
cont_add=0;
pwmin_temp=0;
end


always @ (posedge start_tx_in) begin
start<=1;
pwmin_temp<=pwmin;
end


always @ (posedge clk) begin 

if (cycle_reset)
	cycle<=0;
		else 
		cycle<=cycle;


if (cont_pwm==freq_div || cont_pwm==0)					//Cycle_reset logic
	cycle_reset<=1;
		else 
			cycle_reset<=0;


if (cspwm && start) begin

		if (cont_pwm<freq_div)			//12000 -> 240uS =4Khz  ---- 6250 -> 125uS = 8kHz
				begin			
				cont_pwm<=cont_pwm+1;
				end else begin
				cont_pwm<=0;
				end

if (reset) begin
	pwmout<=0;
	cycle<=0;
	end else begin					//PWM Output logic

		if (cont_add<time_add)				
			begin	
			cont_add<=cont_add+1;
			end else begin	
				cont_add<=0;
				if (cycle<pwmin_temp)
					begin
					cycle<=cycle+cycle_adder;				
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
