module wb_pwm (
	input              clk,
	input              reset,
	// Wishbone interface
	input              wb_stb_i,
	input              wb_cyc_i,
	output             wb_ack_o,
	input              wb_we_i,
	input       [31:0] wb_adr_i,
	input        [3:0] wb_sel_i,
	input       [31:0] wb_dat_i,	//Recibe el valor del Chip select
	output reg  [31:0] wb_dat_o,   //manda el status al procesador
	// PWM output serial wires
	input	        [7:0] pwmin,
	input		start_tx_in,
	input   	   data_rdy,
	output               pwmout	
);

//Enable Register
reg cspwm;
//Freq Config Registers
reg [31:0] time_add;
reg [31:0] cycle_adder;
reg [31:0] freq_div;

reg [31:0] cont_pwm;


wire [7:0] status;

pwm_8bit_var pwm8bit0(
	.clk  (  clk       ),
	.pwmin (   pwmin   ),
	.cspwm    (    cspwm     ),
	.reset  (  reset   ),
//	.data_rdy  (  data_rdy   ),
	.start_tx_in (start_tx_in),
	.pwmout (  pwmout  ),
	.status	( status   ),
	//Freq Config
	.time_add (time_add),	
	.cycle_adder(cycle_adder),
	.freq_div(freq_div)
);

assign start_tx=cspwm && data_rdy;

reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;	//~we inicia transmision
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;	//we inicia conversion

always @(posedge clk)
begin

	if (reset) 
		ack    <= 0;
		else begin
       		ack    <= 0;
		if (wb_rd & ~ack) begin           // we=0     lectura del estado del periferico
			ack <= 1;
			 if (wb_adr_i[7:0] == 8'h00) begin
				wb_dat_o[7:0]  <= status;
					end else wb_dat_o <= 32'hFF;


		end else if (wb_wr & ~ack ) begin // we=1  control de comienzo o finalizacion
				ack <= 1;
				 case (wb_adr_i[7:0]) 
					8'h00: begin
  					       cspwm <= wb_dat_i[7:0];
					       end
					8'h04: begin
  					       freq_div <= wb_dat_i;
					       end
					8'h08: begin
  					       time_add <= wb_dat_i;
					       end
					8'h0C: begin
  					       cycle_adder <= wb_dat_i;
					       end
					default : wb_dat_o <= 32'h0F;					//Invalid Address
				endcase

		end else wb_dat_o <= 32'b0;
			
	end
end
endmodule

