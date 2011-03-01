module wb_effects(
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
	//Effects Signal
	input 	     [7:0] data_adc,
	output   	   start_tx_out,
	input   	   data_rdy_in,
	output   	   data_rdy_out,
	//Temporary Outputs
	output [7:0] effects_out

);

//
wire [7:0]realt;
wire [7:0]delay1;
wire [7:0]delay2;

//Control and Status
reg	[2:0] effects_sel;
wire    [7:0]      status;
//Echo signals
wire           we_a_echo;
wire	[7:0] dat_a_echo;
wire	[12:0]adr_a_echo;
wire	[12:0]adr_b_echo;
wire 	[7:0] dat_b_echo;
//Flanger signals
wire           we_a_flanger;
wire	[7:0] dat_a_flanger;
wire	[12:0]adr_a_flanger;
wire	[12:0]adr_b_flanger;
wire 	[7:0] dat_b_flanger;
//Flanger Settings
reg [31:0]offset_uplimit;
reg [31:0]offset_lowlimit;
//Delay Parameters
reg 	[31:0] par_delay1;
reg 	[31:0] par_delay2;
//RAM Signals
wire           we_a;
wire	[7:0] dat_a;
wire	[7:0] dat_a_out;
wire 	[7:0] dat_b;
wire	[12:0]adr_a;
wire	[12:0]adr_b;
//Mixer Signals
wire [7:0] realt_echo;
wire [7:0] delay1_echo;
wire [7:0] realt_flanger;
wire [7:0] delay1_flanger;

echo echo_m(
	.clk            (clk),
	.reset          (reset),
	.enable         (enable_echo),
	.start_tx       (start_tx_out_echo),
	.par_delay1     (par_delay1),
	.par_delay2     (par_delay2),
	.data_rdy         (data_rdy_in),
	//RAM Interface
	.we_a          (we_a_echo),
	.dat_a         (dat_a_echo),
	.dat_b         (dat_b_echo),
	.adr_a         (adr_a_echo),
	.adr_b         (adr_b_echo),
	//Signal Input/Outputs
	.data_adc      (data_adc),
	.realt         (realt_echo),
	.delay1        (delay1_echo),
	.delay2        (delay2)
);

flanger flanger_m(
	.clk            (clk),
	.reset          (reset),
	.enable         (enable_flanger),
	.start_tx       (start_tx_out_flanger),
	.par_delay1     (par_delay1),
	.par_delay2     (par_delay2),
	.data_rdy         (data_rdy_in),
	//RAM Interface
	.we_a          (we_a_flanger),
	.dat_a         (dat_a_flanger),
	.dat_b         (dat_b_flanger),
	.adr_a         (adr_a_flanger),
	.adr_b         (adr_b_flanger),
	//Flanger Settings
	.offset_lowlimit (offset_lowlimit),
	.offset_uplimit (offset_uplimit),
	//Signal Input/Outputs
	.data_adc      (data_adc),
	.realt         (realt_flanger),
	.delay1        (delay1_flanger),
	.delay2        (delay2_flanger)
);


ram_arbiter ram_arb_m(
	.clk          (clk),
	.rst          (reset),
	//Echo RAM Signals
	.we_a_echo          (we_a_echo),
	.dat_a_echo         (dat_a_echo),
	.dat_b_echo         (dat_b_echo),
	.adr_a_echo         (adr_a_echo),
	.adr_b_echo         (adr_b_echo),
	//Echo Flanger
	.we_a_flanger          (we_a_flanger),
	.dat_a_flanger         (dat_a_flanger),
	.dat_b_flanger         (dat_b_flanger),
	.adr_a_flanger         (adr_a_flanger),
	.adr_b_flanger         (adr_b_flanger),
	//RAM Interface
	.we_a          	   (we_a),
	.dat_a      	   (dat_a),
	.dat_b             (dat_b),
	.adr_a       	   (adr_a),
	.adr_b        	   (adr_b),
	//Control and Status Signals
	.status        	   (status),
	.effects_sel       (effects_sel)
);

dp_ram dp_ram_m(
	.clk_a         (clk),
	.clk_b         (clk),
	.en_a          (enable_ram),
	.en_b          (enable_ram),
	.we_a          (we_a),
	.dat_a         (dat_a),
	.dat_a_out     (dat_a_out),
	.dat_b         (dat_b),
	.adr_a         (adr_a),
	.adr_b         (adr_b)
);

mixer mixer_m(
	.clk (clk),
	.realt_echo         (realt_echo),
	.delay1_echo        (delay1_echo),
	.realt_flanger         (realt_flanger),
	.delay1_flanger        (delay1_flanger),
	.effects_out        (effects_out),
	.effects_sel       (effects_sel)
);

initial begin
effects_sel=0;
par_delay1=0;
par_delay2=0;
end


assign start_tx_out = start_tx_out_flanger | start_tx_out_echo;
assign enable_ram = enable_echo | enable_flanger;
assign enable_echo = effects_sel[0];
assign enable_flanger = effects_sel[1];
assign en_a=enable_echo;


reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

always @ (posedge clk) 
begin
	if (reset) begin
		wb_dat_o<=0;	
		ack<= 0;
	end else begin
       		ack <= wb_stb_i & wb_cyc_i;
		if (wb_rd & ~ack) begin           // read cycle
			
			case (wb_adr_i[7:0]) 
				8'h00:  begin
					wb_dat_o[2:0] <= effects_sel;
					wb_dat_o[31:3] <= 29'd0;
					end 
				8'h04:  begin
					wb_dat_o <= par_delay1;
//					wb_dat_o[31:16] <= 16'd0;
					end 
				8'h08:  begin
					wb_dat_o <= par_delay2;
//					wb_dat_o[31:16] <= 16'd0;
					end 
				8'h0C:  begin
					wb_dat_o <= offset_uplimit;
//					wb_dat_o[31:16] <= 16'd0;
					end 
				8'h10:  begin
					wb_dat_o <= offset_lowlimit;
//					wb_dat_o[31:16] <= 16'd0;
					end 
				8'h14:  begin
					wb_dat_o <= status;
					end
				default: wb_dat_o <= 32'hFF;				//FF read cycle address incorrect
			endcase

		end else if (wb_wr & ~ack ) begin // write cycle
				
				 case (wb_adr_i[7:0]) 
						8'h00: begin 				//Address 00: Effect Select
							effects_sel<=wb_dat_i[2:0];
						end
						8'h04: begin 				//Address 01: delay parameters
							par_delay1<=wb_dat_i;
						end
						8'h08: begin 				//Address 01: delay parameters
							par_delay2<=wb_dat_i;
						end
						8'h0C: begin 
							offset_uplimit<=wb_dat_i;
						end
						8'h10: begin 
							offset_lowlimit<=wb_dat_i;
						end

						default: wb_dat_o<= 32'h0F;		//0F write cycle address incorrect
				endcase
		end else wb_dat_o <= 32'hDF;
		
	end
end



endmodule

