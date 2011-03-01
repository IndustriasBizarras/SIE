
module lcd_regb (

input clk,
input [23:0] ctrl_in,
input [7:0] status,
input [4:0] sel_in,
input [4:0] sel_out,
output reg [7:0] Address_in,
output reg [7:0] Control_in,
output reg [7:0] Data_in

);

//reg [2:0] sel_in;
//reg [2:0] sel_out;

reg [23:0]control0;
reg [23:0]control1;
reg [23:0]control2;
reg [23:0]control3;
reg [23:0]control4;
reg [23:0]control5;
reg [23:0]control6;
reg [23:0]control7;
reg [23:0]control8;
reg [23:0]control9;
reg [23:0]control10;
reg [23:0]control11;
reg [23:0]control12;
reg [23:0]control13;
reg [23:0]control14;
reg [23:0]control15;
reg [23:0]control16;
reg [23:0]control17;
reg [23:0]control18;
reg [23:0]control19;
reg [23:0]control20;
reg [23:0]control21;
reg [23:0]control22;
reg [23:0]control23;
reg [23:0]control24;
reg [23:0]control25;
reg [23:0]control26;
reg [23:0]control27;
reg [23:0]control28;
reg [23:0]control29;
reg [23:0]control30;
reg [23:0]control31;
reg [23:0]control32;

//
//reg [23:0]E;
//reg [23:0]F;
//reg [7:0]C;
//reg [7:0]D;
//reg flag_in;
//reg flag_out;

initial begin
Address_in=0;
Control_in=0;
Data_in=0;
control0=0;
control1=0;
end


		
always @(posedge clk)
begin

//if (flag_in) begin
//	E<=ctrl_in;
//	flag_in<=~flag_in;
//	end else begin F<=ctrl_in;
//			flag_in<=~flag_in;
//			end
//
//if (~E==F) begin 
//	sel_in<=sel_in+1;
	case (sel_in)
		5'd0: control0 <= ctrl_in;
		5'd1: control1 <= ctrl_in;
		5'd2: control2 <= ctrl_in;
		5'd3: control3 <= ctrl_in;
		5'd4: control4 <= ctrl_in;
		5'd5: control5 <= ctrl_in;
		5'd6: control6 <= ctrl_in;
		5'd7: control7 <= ctrl_in;
		5'd8: control8 <= ctrl_in;
		5'd9: control9 <= ctrl_in;
		5'd10: control10 <= ctrl_in;
		5'd11: control11 <= ctrl_in;
		5'd12: control12 <= ctrl_in;
		5'd13: control13 <= ctrl_in;
		5'd14: control14 <= ctrl_in;
		5'd15: control15 <= ctrl_in;
		5'd16: control16 <= ctrl_in;
		5'd17: control17 <= ctrl_in;
		5'd18: control18 <= ctrl_in;
		5'd19: control19 <= ctrl_in;
		5'd20: control20 <= ctrl_in;
		5'd21: control21 <= ctrl_in;
		5'd22: control22 <= ctrl_in;
		5'd23: control23 <= ctrl_in;
		5'd24: control24 <= ctrl_in;
		5'd25: control25 <= ctrl_in;
		5'd26: control26 <= ctrl_in;
		5'd27: control27 <= ctrl_in;
		5'd28: control28 <= ctrl_in;
		5'd29: control29 <= ctrl_in;
		5'd30: control30 <= ctrl_in;
		5'd31: control31 <= ctrl_in;
	default : begin 
	control0 <= 24'hFFFFFF;
	end
	endcase
//end else sel_in<=sel_in;
//if (flag_out) begin
//	C<=status;
//	flag_out<=~flag_out;
//	end else begin 
//				D<=status;
//				flag_out<=~flag_out;
//				end
//
//if (~C==D) begin 
//	sel_out<=sel_out+1;
	case (sel_out)
			5'd0: begin
				Address_in <= control0[23:16];
				Control_in <= control0[15:8];
				Data_in <= control0[7:0];
				end
			5'd1: begin
				Address_in <= control1[23:16];
				Control_in <= control1[15:8];
				Data_in    <= control1[7:0];
				end
			5'd2: begin
				Address_in <= control2[23:16];
				Control_in <= control2[15:8];
				Data_in    <= control2[7:0];
				end
			5'd3: begin
				Address_in <= control3[23:16];
				Control_in <= control3[15:8];
				Data_in    <= control3[7:0];
				end
			5'd4: begin
				Address_in <= control4[23:16];
				Control_in <= control4[15:8];
				Data_in    <= control4[7:0];
				end
			5'd5: begin
				Address_in <= control5[23:16];
				Control_in <= control5[15:8];
				Data_in    <= control5[7:0];
				end
			5'd6: begin
				Address_in <= control6[23:16];
				Control_in <= control6[15:8];
				Data_in    <= control6[7:0];
				end
			5'd7: begin
				Address_in <= control7[23:16];
				Control_in <= control7[15:8];
				Data_in    <= control7[7:0];
				end
			5'd8: begin
				Address_in <= control8[23:16];
				Control_in <= control8[15:8];
				Data_in    <= control8[7:0];
				end
			5'd9: begin
				Address_in <= control9[23:16];
				Control_in <= control9[15:8];
				Data_in    <= control9[7:0];
				end
			5'd10: begin
				Address_in <= control10[23:16];
				Control_in <= control10[15:8];
				Data_in    <= control10[7:0];
				end
			5'd11: begin
				Address_in <= control11[23:16];
				Control_in <= control11[15:8];
				Data_in    <= control11[7:0];
				end
			5'd12: begin
				Address_in <= control12[23:16];
				Control_in <= control12[15:8];
				Data_in    <= control12[7:0];
				end
			5'd13: begin
				Address_in <= control13[23:16];
				Control_in <= control13[15:8];
				Data_in    <= control13[7:0];
				end
			5'd14: begin
				Address_in <= control14[23:16];
				Control_in <= control14[15:8];
				Data_in    <= control14[7:0];
				end
			5'd15: begin
				Address_in <= control15[23:16];
				Control_in <= control15[15:8];
				Data_in    <= control15[7:0];
				end
			5'd16: begin
				Address_in <= control16[23:16];
				Control_in <= control16[15:8];
				Data_in    <= control16[7:0];
				end
			5'd17: begin
				Address_in <= control17[23:16];
				Control_in <= control17[15:8];
				Data_in    <= control17[7:0];
				end
			5'd18: begin
				Address_in <= control18[23:16];
				Control_in <= control18[15:8];
				Data_in    <= control18[7:0];
				end
			5'd19: begin
				Address_in <= control19[23:16];
				Control_in <= control19[15:8];
				Data_in    <= control19[7:0];
				end
			5'd20: begin
				Address_in <= control20[23:16];
				Control_in <= control20[15:8];
				Data_in    <= control20[7:0];
				end
			5'd21: begin
				Address_in <= control21[23:16];
				Control_in <= control21[15:8];
				Data_in    <= control21[7:0];
				end		
			5'd22: begin
				Address_in <= control22[23:16];
				Control_in <= control22[15:8];
				Data_in    <= control22[7:0];
				end
			5'd23: begin
				Address_in <= control23[23:16];
				Control_in <= control23[15:8];
				Data_in    <= control23[7:0];
				end
			5'd24: begin
				Address_in <= control24[23:16];
				Control_in <= control24[15:8];
				Data_in    <= control24[7:0];
				end
			5'd25: begin
				Address_in <= control25[23:16];
				Control_in <= control25[15:8];
				Data_in    <= control25[7:0];
				end
			5'd26: begin
				Address_in <= control26[23:16];
				Control_in <= control26[15:8];
				Data_in    <= control26[7:0];
				end
			5'd27: begin
				Address_in <= control27[23:16];
				Control_in <= control27[15:8];
				Data_in    <= control27[7:0];
				end
			5'd28: begin
				Address_in <= control28[23:16];
				Control_in <= control28[15:8];
				Data_in    <= control28[7:0];
				end
			5'd29: begin
				Address_in <= control29[23:16];
				Control_in <= control29[15:8];
				Data_in    <= control29[7:0];
				end
			5'd30: begin
				Address_in <= control30[23:16];
				Control_in <= control30[15:8];
				Data_in    <= control30[7:0];
				end
			5'd31: begin
				Address_in <= control31[23:16];
				Control_in <= control31[15:8];
				Data_in    <= control31[7:0];
				end
	
			default: begin
				Address_in <= 8'hFF;
				Control_in <= 8'hFF;
				Data_in    <= 8'hFF;
				end
		endcase
//end else sel_out<=sel_out;
end
endmodule
