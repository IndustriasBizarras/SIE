module pwm(
	input clk,
	input [23:0] pwmin,
	input  cspwm,
	input reset,
	input start_tx,
	output reg pwmout,		//Salida al filtro analogo
	output reg [7:0] status		//1 transmite   0 standby		
	);

reg [24:0] pwmaccumulator;
reg 	S;
reg 	load;


initial begin
status=0;
pwmout=0;
pwmaccumulator=0;
S=0;
load=0;
end

always @ (posedge clk) begin

	if (reset) begin
		pwmout<=0;
		pwmaccumulator<=0;
		status<=0;
		S=0;
		load<=0;
	 end else begin
			if (cspwm && start_tx) begin       //1 Transmite
				case (S)
				4'd0: begin
					if (~load) S=1;
						else S=0;
					end
				4'd1: begin
					S=0;					
					pwmaccumulator <= pwmaccumulator[23:0] + pwmin;
					status<=1;
					pwmout <= pwmaccumulator[8];   //bit transmitido
					load<=1;
					end
				default S=0;

				endcase

				end else begin
					status<=0;
					load<=0;
					end
		end
end 
endmodule 
