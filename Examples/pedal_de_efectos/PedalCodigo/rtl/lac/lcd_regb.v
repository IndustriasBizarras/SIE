
module lcd_regb (

input clk,
input [23:0] ctrl_in,
input [7:0] status,
input [2:0] sel_in,
input [2:0] sel_out,
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
/*reg [23:0]control8;
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
*/
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
		3'd0: control0 <= ctrl_in;
		3'd1: control1 <= ctrl_in;
		3'd2: control2 <= ctrl_in;
		3'd3: control3 <= ctrl_in;
		3'd4: control4 <= ctrl_in;
		3'd5: control5 <= ctrl_in;
		3'd6: control6 <= ctrl_in;
		3'd7: control7 <= ctrl_in;
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
			3'd0: begin
				Address_in <= control0[23:16];
				Control_in <= control0[15:8];
				Data_in <= control0[7:0];
				end
			3'd1: begin
				Address_in <= control1[23:16];
				Control_in <= control1[15:8];
				Data_in    <= control1[7:0];
				end
			3'd2: begin
				Address_in <= control2[23:16];
				Control_in <= control2[15:8];
				Data_in    <= control2[7:0];
				end
			3'd3: begin
				Address_in <= control3[23:16];
				Control_in <= control3[15:8];
				Data_in    <= control3[7:0];
				end
			3'd4: begin
				Address_in <= control4[23:16];
				Control_in <= control4[15:8];
				Data_in    <= control4[7:0];
				end
			3'd5: begin
				Address_in <= control5[23:16];
				Control_in <= control5[15:8];
				Data_in    <= control5[7:0];
				end
			3'd6: begin
				Address_in <= control6[23:16];
				Control_in <= control6[15:8];
				Data_in    <= control6[7:0];
				end
			3'd7: begin
				Address_in <= control7[23:16];
				Control_in <= control7[15:8];
				Data_in    <= control7[7:0];
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
