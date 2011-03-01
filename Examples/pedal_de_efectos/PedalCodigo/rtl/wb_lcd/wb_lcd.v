
module wb_lcd #(
	parameter lcdram_file = ( "none" )
)
(
	input              clk,
	input              reset,
	// Wishbone interface
	input              wb_stb_i,
	input              wb_cyc_i,
	output             wb_ack_o,
	input              wb_we_i,
	input       [31:0] wb_adr_i,
	input        [3:0] wb_sel_i,
	input       [31:0] wb_dat_i,
	output reg  [31:0] wb_dat_o,
	// LCD Output
	output             E,
	output             RS,
	output             RW,
	output       [7:0] Data_out
);

reg [7:0] Data_in;
reg [7:0] Control_in;
reg [7:0] Address_in;
wire [7:0] status;
wire [23:0] dat_b;
reg [23:0] dat_a;
wire [23:0] dat_a_out;

reg [23:0]ctrl_in;
reg [23:0]ctrl_in_temp;
reg [9:0]sel_in;
wire [9:0]sel_out;
reg [31:0]cont_lcd;
reg clk_lcd;
reg we_a;

assign enable_ram=1;
assign en_b=1;
assign en_a=1;

initial begin
ctrl_in=0;
ctrl_in_temp=0;
sel_in=10'h14;			//=10'h3FE
clk_lcd=0;
we_a=0;
end

lcd lcd_m(
	.clk   (   clk_lcd     ),
	.reset	(     reset        ),
	.Data_in	(  Data_in ),
	.Address_in  (  Address_in ),
	.Control_in(   Control_in  ),
	.RS		     (  RS ),
	.RW		     (  RW ),
	.E		  (    E   ),
	.Data_out    (   Data_out  ),
	.status      (   status    ),
	.sel_out    ( sel_out   )
);

dp_ram_lcd #(
	.mem_file_name( lcdram_file )
)
dp_ram_lcd_m(
	.clk_a         (clk),
	.clk_b         (clk),
	.en_a          (en_a),
	.en_b          (en_b),
	.we_a          (we_a),
	.dat_a         (dat_a),
	.dat_a_out     (dat_a_out),
	.dat_b         (dat_b),
	.adr_a         (sel_in),
	.adr_b         (sel_out)
);



reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;
//assign ack = wb_stb_i & wb_cyc_i;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

always @(posedge clk)
begin

 Address_in <=   dat_b[23:16];
 Control_in <=   dat_b[15:8];
 Data_in    <=   dat_b[7:0];

if (cont_lcd<1000)			//100000 to see process --- default:1000
	cont_lcd<=cont_lcd+1;
		else begin
		cont_lcd<=0;
		clk_lcd<=~clk_lcd;
		end

	if (reset) begin
		wb_dat_o<=0;	
		sel_in<=10'h14;
	end else begin
		ack    <= 0;
		if (wb_rd & ~ack) begin           // read cycle
			ack <= 1;
			 case (wb_adr_i[7:0]) 
				8'h02: begin

				wb_dat_o[7:0] <= status;
				wb_dat_o[31:8] <= 24'd0;

				  end 
				8'h04: begin
				wb_dat_o[23:0] <= dat_b;
				wb_dat_o[31:24] <= 8'd0;
				end
				default: wb_dat_o <= 32'hFF;				//FF read cycle address incorrect
			endcase

		end else if (wb_wr & ~ack ) begin // write cycle
				ack <= 1;
				 case (wb_adr_i[7:0]) 
						8'h00: begin 
							ctrl_in_temp[23:16]<=wb_dat_i[7:0];
							we_a<=0;
						end
						8'h01: begin 
							ctrl_in_temp[7:0]<=wb_dat_i[7:0];
							we_a<=0;
						end
						8'h03: begin 
							dat_a <= {ctrl_in_temp[23:16],wb_dat_i[7:0],ctrl_in_temp[7:0]};
							we_a<=1;
/*							dat_a [7:0]<= ctrl_in_temp[7:0];
							dat_a [23:16]<= ctrl_in_temp[23:16];
							dat_a [15:8]<= wb_dat_i[7:0];	*/
							sel_in<=sel_in+1;			
						end
						default: wb_dat_o<= 32'h0F;			//0F write cycle address incorrect
				endcase
		end else wb_dat_o <= 32'hDF;
		
	end
end
endmodule
