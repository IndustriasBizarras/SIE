module mixer#(
parameter zero_off = 8'h10,
parameter fade = 32'h00000000
)
(
input clk,
input [7:0]realt_echo,
input [7:0]delay1_echo,
input [7:0]realt_flanger,
input [7:0]delay1_flanger,
input [2:0] effects_sel,

output [7:0] effects_out
);

reg [8:0]eff_out;


assign effects_out = eff_out [8:1];

always @ (posedge clk)
begin
	case (effects_sel)
		3'b001: eff_out <= realt_echo + delay1_echo;
		3'b010: eff_out <= realt_flanger + delay1_flanger;
		default: eff_out <= 0;
	endcase
end

endmodule


