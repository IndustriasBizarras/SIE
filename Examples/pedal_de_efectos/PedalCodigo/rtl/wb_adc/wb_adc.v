module wb_adc (
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
	// ADC Output serial wires
	input		   eoc,			//Conexion a eoc del integrado
	output             cs,			//conexion a ~cs del integrado
	output             data_out,		//Conexion a DI del integrado
	input             data_in,		//conexion a DO del integrado
	output       [7:0] data_adc,		//Conversión salida en paralelo
	output              cstart,				//va al integrado y es siempre vcc
	output  	ADC_clk,			//clock del integrado
	output 		data_rdy,		//confirmacion de la conversion
	output 		busy,
	input 		start_tx
);
reg [3:0]control;		//01 start conversion
reg [3:0]channel;
wire  [7:0]status;


adc adc0(
	.clk   (   clk     ),
	.reset	(     reset        ),
	.eoc	(     eoc        ),
	.data_in	(  data_in ),
	.start_tx  (  start_tx ),
	.control(   control  ),
	.channel     (  channel ),
	.data_rdy (  data_rdy ),
	.status		  (    status   ),
	.cs    (   cs  ),
	.data_adc      (   data_adc    ),
	.data_out      (   data_out    ),
	.cstart		(   cstart   ),
	.ADC_clk   (  ADC_clk  ),
	.busy  ( busy  )

);



reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;
//assign start_txp = start_tx;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;	//~we inicia transmision
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;	//we inicia conversion

initial begin
control=0;
channel=0;
//start_tx=0;
//data_rdy=0;
end


always @(posedge clk)
begin

	if (reset) begin
		ack    <= 0;
	end else begin
       		ack    <= wb_stb_i & wb_cyc_i;
		if (wb_rd & ~ack) begin           // we=0     ciclo de transmision
			 ack <= 1;
			 case (wb_adr_i[7:0])
					8'h00:	begin
								wb_dat_o[7:0]  <= status;
								end
					8'h01:	begin
								wb_dat_o[7:0]  <= data_rdy;
								end
					8'h02:	begin
								wb_dat_o[7:0] <= data_adc;
								end
					8'h06:	begin
								wb_dat_o[7:0] <= busy;
								end
								default  wb_dat_o <= 32'hFF;
				endcase


		end else if (wb_wr & ~ack ) begin // we=1 ciclo de conversion
				ack <= 1;
				case (wb_adr_i[7:0])
					8'h03: begin
 						channel <= wb_dat_i[7:0];
						end
					8'h04: begin
						control <= wb_dat_i[7:0];
						end
						default  wb_dat_o <= 32'h0F;
				endcase
		end else wb_dat_o <= 32'b0;
			
	end
end
endmodule





