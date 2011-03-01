module ram_arbiter(
	input 		       clk,
	input 		       rst,
	//Echo signals
	input 		       we_a_echo,
	input		[7:0] dat_a_echo,
	input		[12:0]adr_a_echo,
	input		[12:0]adr_b_echo,
	input		[2:0]effects_sel,
	output reg 	[7:0] dat_b_echo,
	//Flanger signals
	input 		       we_a_flanger,
	input		[7:0] dat_a_flanger,
	input		[12:0]adr_a_flanger,
	input		[12:0]adr_b_flanger,
	output reg 	[7:0] dat_b_flanger,
	output reg 	[7:0]     status,		//0 for Idle - 1 for Echo

	//RAM Signals
	output  reg [12:0] adr_a,
	output  reg [7:0]  dat_a,
	output  reg        we_a,
	output  reg [12:0] adr_b,
	input  [7:0]  dat_b
);


always @ (posedge clk)
begin

if (rst) begin
		we_a<=0;
		dat_a<=0;
		dat_b_echo<=0;
		dat_b_flanger<=0;
		adr_a<=0;
		adr_b<=0;	
	end else begin
		case (effects_sel) 
			3'd0: begin
			status <=0; 		//Standby
			end
			3'd1: begin		//Echo has ram
			status <=8'h02;
			we_a<=we_a_echo;
			dat_a<=dat_a_echo;
			dat_b_echo<=dat_b;
			adr_a<=adr_a_echo;
			adr_b<=adr_b_echo;
			end
			3'd2: begin		//Flanger has ram
			status <=8'h04;
			we_a<=we_a_flanger;
			dat_a<=dat_a_flanger;
			dat_b_flanger<=dat_b;
			adr_a<=adr_a_flanger;
			adr_b<=adr_b_flanger;
			end
			default: begin
				status<=8'hD0;		//F0 invalid effects_sel
	
			end
		endcase
	end
end

endmodule

