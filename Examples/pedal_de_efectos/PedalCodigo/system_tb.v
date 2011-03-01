//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
`timescale 1 ns / 100 ps

module system_tb;

//----------------------------------------------------------------------------
// Parameter (may differ for physical synthesis)
//----------------------------------------------------------------------------
parameter tck              = 20;       // clock period in ns
parameter uart_baud_rate   = 1152000;  // uart baud rate for simulation 

parameter clk_freq = 1000000000 / tck; // Frequenzy in HZ
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
reg        clk;
reg        rst;
wire       led;

//----------------------------------------------------------------------------
// UART STUFF (testbench uart, simulating a comm. partner)
//----------------------------------------------------------------------------
wire         uart_rxd;
wire         uart_txd;

//----------------------------------------------------------------------------
//ADC 
//----------------------------------------------------------------------------
wire [7:0] data_adc;
reg  eoc;
wire cs;
wire data_out;
reg data_in;

//----------------------------------------------------------------------------
//	PWM
//----------------------------------------------------------------------------

//wire [7:0] cs;
wire [7:0] status;

reg [3:0]gpio_in;
reg [7:0]data_in_eff;
reg data_rdy_in_eff;
//----------------------------------------------------------------------------
// Device Under Test 
//----------------------------------------------------------------------------
system #(
	.clk_freq(           clk_freq         ),
	.uart_baud_rate(     uart_baud_rate   )
) dut  (
	.clk(          clk    ),
	// Debug
	.rst(          rst    ),
	.led(          led    ),
	// Uart
	.uart_rxd(  uart_rxd  ),
	.uart_txd(  uart_txd  ),
	//ADC
//	.data_adc(  data_adc  ),
	.eoc(   eoc           ),
	.cs(    cs            ),
	.data_out_adc( data_out   ),
	.data_in_adc(  data_in    ),
	.cstart ( cstart      ),
	.ADC_clk (ADC_clk    ),
	.busy (    busy     ),
	//PWM
	.pwmout  (pwmout      ),
	//.pwmin   (pwmin       )
					//GPIO	
	.gpio_in ( gpio_in )
					//Equal
//	.data_rdy_in_eff(data_rdy_in_eff),
//	.data_in_eff(data_in_eff),
//	.data_out_eff0(data_out_eff0)


);
/* Clocking device */
initial         clk <= 0;
always #(tck/2) clk <= ~clk;

/* Simulation setup */
initial begin
	$dumpfile("system_tb.vcd");
	$dumpvars(-1, dut);

	// reset
	#0  rst <= 0;
	#0      gpio_in  <=0;
	#80 rst <= 1;

	//simulacion del ADC
	#0	eoc <=1;
	#0	data_in <=0;
	#50	rst <=1;	
	#18130	rst 	<=1;
	#20000	rst 	<=1;		//38260
	#126030 data_in = 0;
	#2040 data_in <= 0;
	#2040 data_in <= 0;
	#2040 data_in <= 0;
	#2040 data_in <= 1;
	#2040 data_in <= 0;
	#2040 data_in <= 1;
	#2040 data_in <= 1;
	#2040 data_in <= 0;
	#2040 data_in <= 1;		//182650
	#10   	eoc <= 0;
	#8160	eoc <= 1;		//190810

	#223520 data_in = 0;
	#2040 data_in <= 0;
	#2040 data_in <= 1;
	#2040 data_in <= 0;
	#2040 data_in <= 1;
	#2040 data_in <= 0;
	#2040 data_in <= 1;
	#2040 data_in <= 1;
	#2040 data_in <= 0;
	#2040 data_in <= 1;		//414550
	#10	eoc <=0;
	#8160	eoc <=1;
/*
	#223520 data_in = 0;
	#2040 data_in <= 0;
	#2040 data_in <= 0;
	#2040 data_in <= 1;
	#2040 data_in <= 0;
	#2040 data_in <= 1;
	#2040 data_in <= 1;
	#2040 data_in <= 0;
	#2040 data_in <= 0;
	#2040 data_in <= 0;		//414550
	#10	eoc <=0;
	#8160	eoc <=1;

	#223520 data_in = 0;
	#2040 data_in <= 1;
	#2040 data_in <= 0;
	#2040 data_in <= 0;
	#2040 data_in <= 1;
	#2040 data_in <= 1;
	#2040 data_in <= 1;
	#2040 data_in <= 1;
	#2040 data_in <= 0;
	#2040 data_in <= 1;		//414550
	#10	eoc <=0;
	#8160	eoc <=1;

*/
	//Simulacion GPIO
	#1000000 gpio_in <=1;
	#10000  gpio_in <=0;


	#50000 gpio_in <=2;
	#10000  gpio_in <=0;

	#50000 gpio_in <=4;
	#10000  gpio_in <=0;

	#50000 gpio_in <=4;
	#10000  gpio_in <=0;

	#(tck*10000) $finish;
end



endmodule
