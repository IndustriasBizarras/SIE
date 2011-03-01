
module wb_gpio (
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
	//
	output             intr,		//interrupcion
	// IO Wires
	input       [3:0] gpio_in,
	output [2:0] gpio_out,
	output 		prueba
	
	//output reg  [31:0] gpio_oe		//Define la direccion del registro
);

gpio gpio0(
		.clk (  clk   ),
		.reset ( reset  ),
		.inuser(  gpio_in ),
		.outuser ( gpio_out ),
		.gpio_en (intr ),
		.prueba (prueba)
    );


initial begin

wb_dat_o=0;
end

//wire [31:0] gpiocr = 32'b0;

// Wishbone
reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;


wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

always @(posedge clk)
begin
	if (reset) begin
		ack      <= 0;
	end else begin
		// Handle WISHBONE access
		ack    <= 0;

		if (wb_rd & ~ack) begin           // read cycle
			ack <= 1;

			case (wb_adr_i[7:0])
			8'h00: 
			begin 
			wb_dat_o [7:0]<= gpio_out;
			wb_dat_o [31:8]<= 0;
			end
			8'h04: 
			begin
			wb_dat_o <= gpio_out;
			wb_dat_o [31:8]<= 0;
			end
			default: wb_dat_o <= 32'b0;
			endcase
		end else if (wb_wr & ~ack ) begin // write cycle
			ack <= 1;

			/*case (wb_adr_i[7:0])
			'h00: begin
			end
			'h04: gpio_out <= wb_dat_i;
			//'h18: gpio_oe  <= wb_dat_i;
			endcase*/
		end
	end
end


endmodule
