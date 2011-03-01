//---------------------------------------------------------------------------
// LatticeMico32 System On A Chip
//
// Top Level Design for the Xilinx Spartan 3-200 Starter Kit
//---------------------------------------------------------------------------

module system
#(
	parameter   bootram_file     = "../firmware/all_one/image.ram",
	parameter   lcdram_file     = "../firmware/all_one/image_lcd.ram",
	parameter   clk_freq         = 50000000,
	parameter   uart_baud_rate   = 57600
) (
	input             clk, 
	// Debug 
	output            led,
	input             rst,
	// UART
	input             uart_rxd, 
	output            uart_txd,
        // CPU Interface
        input             [12:0] addr,
        input             [7:0]  sram_data,
        input             nwe,
        input             noe,
        input             ncs,
	//LCD
	output            E,
	output            RS,
	output            RW,
	output      [7:0] data_out_lcd,
	//ADC
	input		   eoc,	
	input             data_in_adc,		
	output             cs,			
	output             data_out_adc,			
//	output       [7:0] data_adc,
	output		   cstart,
	output		ADC_clk,
	output		   busy,
	//Test Signals for effecst
//	output 		[7:0] realt,
	//output 		[7:0] delay1,
	//output		[7:0] delay2
	//PWM
	output             pwmout,
	//GPIO
	input		[3:0] gpio_in,
	output [3:0] gpio_out
	//Equal input for simulation
//	input [7:0] data_in_eff,
//	input data_rdy_in_eff,
//	output [7:0] data_out_eff0


);

assign gpio_out = gpio_in;

//------------------------------------------------------------------
// Whishbone Wires
//------------------------------------------------------------------
wire         gnd   =  1'b0;
wire   [3:0] gnd4  =  4'h0;
wire  [31:0] gnd32 = 32'h00000000;

 
wire [31:0]  lm32i_adr,
             lm32d_adr,
             uart0_adr,
             effects0_adr,
             gpio0_adr,
             bram0_adr,
             sram0_adr,
             lcd0_adr,
	     adc0_adr,
	     pwm0_adr,
	     equal0_adr;


wire [31:0]  lm32i_dat_r,
             lm32i_dat_w,
             lm32d_dat_r,
             lm32d_dat_w,
             uart0_dat_r,
             uart0_dat_w,
             effects0_dat_r,
             effects0_dat_w,
             gpio0_dat_r,
             gpio0_dat_w,
             bram0_dat_r,
             bram0_dat_w,
             sram0_dat_w,
             sram0_dat_r,
             lcd0_dat_w,
             lcd0_dat_r,
             adc0_dat_w,
             adc0_dat_r,
	     pwm0_dat_w,
	     pwm0_dat_r,
	     equal0_dat_w,
	     equal0_dat_r; 

wire [3:0]   lm32i_sel,
             lm32d_sel,
             uart0_sel,
             effects0_sel,
             gpio0_sel,
             bram0_sel,
             sram0_sel,
             lcd0_sel,
             adc0_sel,
	     pwm0_sel,
	     equal0_sel;

wire         lm32i_we,
             lm32d_we,
             uart0_we,
             effects0_we,
             gpio0_we,
             bram0_we,
             sram0_we,
             lcd0_we,
             adc0_we,
	     pwm0_we,
	     equal0_we;

wire         lm32i_cyc,
             lm32d_cyc,
             uart0_cyc,
             effects0_cyc,
             gpio0_cyc,
             bram0_cyc,
             sram0_cyc,
             lcd0_cyc,
             adc0_cyc,
	     pwm0_cyc,
	     equal0_cyc;

wire         lm32i_stb,
             lm32d_stb,
             uart0_stb,
             effects0_stb,
             gpio0_stb,
             bram0_stb,
             sram0_stb,
             lcd0_stb,
             adc0_stb,	     
	     pwm0_stb,
	     equal0_stb;

wire         lm32i_ack,
             lm32d_ack,
             uart0_ack,
             effects0_ack,
             gpio0_ack,
             bram0_ack,
             sram0_ack,
             lcd0_ack,
             adc0_ack,
	     pwm0_ack,
	     equal0_ack;

wire         lm32i_rty,
             lm32d_rty;

wire         lm32i_err,
             lm32d_err;

wire         lm32i_lock,
             lm32d_lock;

wire [2:0]   lm32i_cti,
             lm32d_cti;

wire [1:0]   lm32i_bte,
             lm32d_bte;

//---------------------------------------------------------------------------
// Interrupts
//---------------------------------------------------------------------------
wire [31:0]  intr_n;
wire         uart0_intr = 0;
wire   [1:0] effects0_intr;
wire         gpio0_intr;

wire [7:0] effects_out0;

//Wires Equalizador
wire [7:0] data_eq_in0;
wire [23:0] data_eq_out0;

//Wires Effects
wire [7:0]data_out_eff0;

wire [23:0] pwmin0;


assign gpio_intr = gpio0_intr;
assign intr_n = { 30'h3FFFFFFF, ~gpio_intr,~uart0_intr }; //vector de interrupciones
//---------------------------------------------------------------------------
// Wishbone Interconnect
//---------------------------------------------------------------------------
wb_conbus_top #(
	.s0_addr_w ( 15 ),
	.s0_addr   ( 15'h7F06 ),    // Ecualizador
	.s1_addr_w ( 15 ),
	.s1_addr   ( 15'h7F05 ),    //   pwm  
	.s27_addr_w( 15 ),
	.s2_addr   ( 15'h0000 ),    // bram0 
	.s3_addr   ( 15'h7000 ),    // uart0
	.s4_addr   ( 15'h7F01 ),    // efectos
	.s5_addr   ( 15'h7F02 ),    // gpio
	.s6_addr   ( 15'h7F03 ),    // adc
	.s7_addr   ( 15'h7F04 )	    // lcd

) conmax0 (
	.clk_i( clk ),
	.rst_i( ~rst ),
	// Master0
	.m0_dat_i(  lm32i_dat_w  ),
	.m0_dat_o(  lm32i_dat_r  ),
	.m0_adr_i(  lm32i_adr    ),
	.m0_we_i (  lm32i_we     ),
	.m0_sel_i(  lm32i_sel    ),
	.m0_cyc_i(  lm32i_cyc    ),
	.m0_stb_i(  lm32i_stb    ),
	.m0_ack_o(  lm32i_ack    ),
	.m0_rty_o(  lm32i_rty    ),
	.m0_err_o(  lm32i_err    ),
	// Master1
	.m1_dat_i(  lm32d_dat_w  ),
	.m1_dat_o(  lm32d_dat_r  ),
	.m1_adr_i(  lm32d_adr    ),
	.m1_we_i (  lm32d_we     ),
	.m1_sel_i(  lm32d_sel    ),
	.m1_cyc_i(  lm32d_cyc    ),
	.m1_stb_i(  lm32d_stb    ),
	.m1_ack_o(  lm32d_ack    ),
	.m1_rty_o(  lm32d_rty    ),
	.m1_err_o(  lm32d_err    ),
	// Master2
	.m2_dat_i(  gnd32  ),
	.m2_adr_i(  gnd32  ),
	.m2_sel_i(  gnd4   ),
	.m2_cyc_i(  gnd    ),
	.m2_stb_i(  gnd    ),
	// Master3
	.m3_dat_i(  gnd32  ),
	.m3_adr_i(  gnd32  ),
	.m3_sel_i(  gnd4   ),
	.m3_cyc_i(  gnd    ),
	.m3_stb_i(  gnd    ),
	// Master4
	.m4_dat_i(  gnd32  ),
	.m4_adr_i(  gnd32  ),
	.m4_sel_i(  gnd4   ),
	.m4_cyc_i(  gnd    ),
	.m4_stb_i(  gnd    ),
	// Master5
	.m5_dat_i(  gnd32  ),
	.m5_adr_i(  gnd32  ),
	.m5_sel_i(  gnd4   ),
	.m5_cyc_i(  gnd    ),
	.m5_stb_i(  gnd    ),
	// Master6
	.m6_dat_i(  gnd32  ),
	.m6_adr_i(  gnd32  ),
	.m6_sel_i(  gnd4   ),
	.m6_cyc_i(  gnd    ),
	.m6_stb_i(  gnd    ),
	// Master7
	.m7_dat_i(  gnd32  ),
	.m7_adr_i(  gnd32  ),
	.m7_sel_i(  gnd4   ),
	.m7_cyc_i(  gnd    ),
	.m7_stb_i(  gnd    ),

	// Slave0
	.s0_dat_i(  equal0_dat_r   ),
	.s0_dat_o(  equal0_dat_w   ),
	.s0_adr_o(  equal0_adr     ),
	.s0_sel_o(  equal0_sel     ),
	.s0_we_o(   equal0_we      ),
	.s0_cyc_o(  equal0_cyc     ),
	.s0_stb_o(  equal0_stb     ),
	.s0_ack_i(  equal0_ack     ),
	.s0_err_i(  gnd    ),
	.s0_rty_i(  gnd    ),
	// Slave1      			  PWM
	.s1_dat_i(  pwm0_dat_r  ),
	.s1_dat_o(  pwm0_dat_w  ),
	.s1_adr_o(  pwm0_adr    ),
	.s1_sel_o(  pwm0_sel    ),
	.s1_we_o(   pwm0_we     ),
	.s1_cyc_o(  pwm0_cyc    ),
	.s1_stb_o(  pwm0_stb    ),
	.s1_ack_i(  pwm0_ack    ),
	.s1_err_i(  gnd          ),
	.s1_rty_i(  gnd          ),
	// Slave2
	.s2_dat_i(  bram0_dat_r ),
	.s2_dat_o(  bram0_dat_w ),
	.s2_adr_o(  bram0_adr   ),
	.s2_sel_o(  bram0_sel   ),
	.s2_we_o(   bram0_we    ),
	.s2_cyc_o(  bram0_cyc   ),
	.s2_stb_o(  bram0_stb   ),
	.s2_ack_i(  bram0_ack   ),
	.s2_err_i(  gnd         ),
	.s2_rty_i(  gnd         ),
	// Slave3
	.s3_dat_i(  uart0_dat_r ),
	.s3_dat_o(  uart0_dat_w ),
	.s3_adr_o(  uart0_adr   ),
	.s3_sel_o(  uart0_sel   ),
	.s3_we_o(   uart0_we    ),
	.s3_cyc_o(  uart0_cyc   ),
	.s3_stb_o(  uart0_stb   ),
	.s3_ack_i(  uart0_ack   ),
	.s3_err_i(  gnd         ),
	.s3_rty_i(  gnd         ),
	// Slave4
	.s4_dat_i(  effects0_dat_r ),
	.s4_dat_o(  effects0_dat_w ),
	.s4_adr_o(  effects0_adr   ),
	.s4_sel_o(  effects0_sel   ),
	.s4_we_o(   effects0_we    ),
	.s4_cyc_o(  effects0_cyc   ),
	.s4_stb_o(  effects0_stb   ),
	.s4_ack_i(  effects0_ack   ),
	.s4_err_i(  gnd          ),
	.s4_rty_i(  gnd          ),
	// Slave5
	.s5_dat_i(  gpio0_dat_r  ),
	.s5_dat_o(  gpio0_dat_w  ),
	.s5_adr_o(  gpio0_adr    ),
	.s5_sel_o(  gpio0_sel    ),
	.s5_we_o(   gpio0_we     ),
	.s5_cyc_o(  gpio0_cyc    ),
	.s5_stb_o(  gpio0_stb    ),
	.s5_ack_i(  gpio0_ack    ),
	.s5_err_i(  gnd          ),
	.s5_rty_i(  gnd          ),
	// Slave6		--ADC--
	.s6_dat_i(  adc0_dat_r  ),
	.s6_dat_o(  adc0_dat_w  ),
	.s6_adr_o(  adc0_adr    ),
	.s6_sel_o(  adc0_sel    ),
	.s6_we_o(   adc0_we     ),
	.s6_cyc_o(  adc0_cyc    ),
	.s6_stb_o(  adc0_stb    ),
	.s6_ack_i(  adc0_ack    ),
	.s6_err_i(  gnd          ),
	.s6_rty_i(  gnd          ),
	// Slave7    			--LCD --
	.s7_dat_i(  lcd0_dat_r ),
	.s7_dat_o(  lcd0_dat_w ),
	.s7_adr_o(  lcd0_adr   ),
	.s7_sel_o(  lcd0_sel   ),
	.s7_we_o(   lcd0_we    ),
	.s7_cyc_o(  lcd0_cyc   ),
	.s7_stb_o(  lcd0_stb   ),
	.s7_ack_i(  lcd0_ack   ),
	.s7_err_i(  gnd          ),
	.s7_rty_i(  gnd          )
);

//---------------------------------------------------------------------------
// LM32 CPU 
//---------------------------------------------------------------------------
lm32_cpu lm0 (
	.clk_i(  clk  ),
	.rst_i(  ~rst  ),
	.interrupt_n(  intr_n  ),
	//
	.I_ADR_O(  lm32i_adr    ),
	.I_DAT_I(  lm32i_dat_r  ),
	.I_DAT_O(  lm32i_dat_w  ),
	.I_SEL_O(  lm32i_sel    ),
	.I_CYC_O(  lm32i_cyc    ),
	.I_STB_O(  lm32i_stb    ),
	.I_ACK_I(  lm32i_ack    ),
	.I_WE_O (  lm32i_we     ),
	.I_CTI_O(  lm32i_cti    ),
	.I_LOCK_O( lm32i_lock   ),
	.I_BTE_O(  lm32i_bte    ),
	.I_ERR_I(  lm32i_err    ),
	.I_RTY_I(  lm32i_rty    ),
	//
	.D_ADR_O(  lm32d_adr    ),
	.D_DAT_I(  lm32d_dat_r  ),
	.D_DAT_O(  lm32d_dat_w  ),
	.D_SEL_O(  lm32d_sel    ),
	.D_CYC_O(  lm32d_cyc    ),
	.D_STB_O(  lm32d_stb    ),
	.D_ACK_I(  lm32d_ack    ),
	.D_WE_O (  lm32d_we     ),
	.D_CTI_O(  lm32d_cti    ),
	.D_LOCK_O( lm32d_lock   ),
	.D_BTE_O(  lm32d_bte    ),
	.D_ERR_I(  lm32d_err    ),
	.D_RTY_I(  lm32d_rty    )
);
	
//---------------------------------------------------------------------------
// Block RAM
//---------------------------------------------------------------------------
wb_bram #(
	.adr_width( 14 ),
	.mem_file_name( bootram_file )
) bram0 (
	.clk_i(  clk  ),
	.rst_i(  ~rst  ),
	//
	.wb_adr_i(  bram0_adr    ),
	.wb_dat_o(  bram0_dat_r  ),
	.wb_dat_i(  bram0_dat_w  ),
	.wb_sel_i(  bram0_sel    ),
	.wb_stb_i(  bram0_stb    ),
	.wb_cyc_i(  bram0_cyc    ),
	.wb_ack_o(  bram0_ack    ),
	.wb_we_i(   bram0_we     )
);

//---------------------------------------------------------------------------
// uart0
//---------------------------------------------------------------------------
wire uart0_rxd;
wire uart0_txd;

wb_uart #(
	.clk_freq( clk_freq        ),
	.baud(     uart_baud_rate  )
) uart0 (
	.clk( clk ),
	.reset( ~rst ),
	//
	.wb_adr_i( uart0_adr ),
	.wb_dat_i( uart0_dat_w ),
	.wb_dat_o( uart0_dat_r ),
	.wb_stb_i( uart0_stb ),
	.wb_cyc_i( uart0_cyc ),
	.wb_we_i(  uart0_we ),
	.wb_sel_i( uart0_sel ),
	.wb_ack_o( uart0_ack ), 
//	.intr(       uart0_intr ),
	.uart_rxd( uart0_rxd ),
	.uart_txd( uart0_txd )
);
//------------------------------------------------------------------------------------------------------------------
// 				Perifericos
//--------------------------------------------------------------------------------------------------------------------
//Wires ADC
//wire start_tx0;
wire data_rdy0;
wire [7:0] data_adc0;
wire eoc0;
wire cs0;

wire cstart0;		
wire ADC0_clk;
wire busy0;


//---------------------------------------------------------------------------
// 				Effects0
//---------------------------------------------------------------------------


//Wires Efectos
wire [7:0] data_in_eff0;

//Wires pruebas effects
wire [7:0] realt0;
wire [7:0] delay10;
wire [7:0] delay20;

wb_effects effects0 (
	.clk(      clk          ),
	.reset(    ~rst          ),
	//
	.wb_adr_i	( effects0_adr   ),
	.wb_dat_i	( effects0_dat_w ),
	.wb_dat_o	( effects0_dat_r ),
	.wb_stb_i	( effects0_stb   ),
	.wb_cyc_i	( effects0_cyc   ),
	.wb_we_i	(  effects0_we    ),
	.wb_sel_i	( effects0_sel   ),
	.wb_ack_o	( effects0_ack   ), 
	.data_adc     	(data_adc0) ,
//	.start_tx_in   	(start_tx_eff_in),
	.start_tx_out  	(start_tx_eff_out),
	.data_rdy_in  	(data_rdy_adc),
	.data_rdy_out  	(data_rdy_out_eff),
	.effects_out	(data_out_eff0)
);

//---------------------------------------------------------------------------
// General Purpose IO
//---------------------------------------------------------------------------

//Wires GPIO
wire [3:0] gpio0_in;
wire [2:0] gpio0_out;

wb_gpio gpio0 (
	.clk(      clk          ),
	.reset(    ~rst          ),
	//
	.wb_adr_i( gpio0_adr    ),
	.wb_dat_i( gpio0_dat_w  ),
	.wb_dat_o( gpio0_dat_r  ),
	.wb_stb_i( gpio0_stb    ),
	.wb_cyc_i( gpio0_cyc    ),
	.wb_we_i(  gpio0_we     ),
	.wb_sel_i( gpio0_sel    ),
	.wb_ack_o( gpio0_ack    ), 
	.intr(     gpio0_intr   ),
	// GPIO
	.gpio_in(  gpio0_in     ),
	.gpio_out( gpio0_out    )
);


//-----------------------------------------
//        			ADC	
//-----------------------------------------



wb_adc adc0 (
	.clk (      clk          ),
	.reset (    ~rst          ),
	//
	.wb_adr_i	( adc0_adr   ),
	.wb_dat_i	( adc0_dat_w ),
	.wb_dat_o	( adc0_dat_r ),
	.wb_stb_i	( adc0_stb   ),
	.wb_cyc_i	( adc0_cyc   ),
	.wb_we_i	(  adc0_we    ),
	.wb_sel_i	( adc0_sel   ),
	.wb_ack_o	( adc0_ack   ),
	.eoc		( eoc0   ),
	.cs		( cs0   ),
	.data_out 	( data_out_adc0  ),
	.data_in	( data_in_adc  ),
	.data_adc 	( data_adc0 ),
	.cstart   	( cstart0  ),
	.ADC_clk   	(  ADC0_clk  ),
	.data_rdy	(  data_rdy_adc     ),
	.busy 		( busy0 ),
	.start_tx   	(start_tx_eff_out)
);

//-----------------------------------------
//        			LCD0	
//-----------------------------------------

wb_lcd #(
	.lcdram_file( lcdram_file )
)lcd0 (
	.clk (      clk          ),
	.reset (    ~rst          ),
	//
	.wb_adr_i( lcd0_adr   ),
	.wb_dat_i( lcd0_dat_w ),
	.wb_dat_o( lcd0_dat_r ),
	.wb_stb_i( lcd0_stb   ),
	.wb_cyc_i( lcd0_cyc   ),
	.wb_we_i(  lcd0_we    ),
	.wb_sel_i( lcd0_sel   ),
	.wb_ack_o( lcd0_ack   ),
	.E( E   ),
	.RW( RW   ),
	.RS( RS  ),
	.Data_out( data_out_lcd  )
);

//-----------------------------------------
//        			PWM0	
//-----------------------------------------	
wire pwmout0;

wb_pwm pwm0 (
	.clk (      clk          ),
	.reset (    ~rst          ),
	//
	.wb_adr_i( pwm0_adr   ),
	.wb_dat_i( pwm0_dat_w ),
	.wb_dat_o( pwm0_dat_r ),
	.wb_stb_i( pwm0_stb   ),
	.wb_cyc_i( pwm0_cyc   ),
	.wb_we_i(  pwm0_we    ),
	.wb_sel_i( pwm0_sel   ),
	.wb_ack_o( pwm0_ack   ),
	.pwmout  ( pwmout0     ),
	.pwmin   ( data_out_eff0     ),
	.start_tx_in (start_tx_eff_out),
	.data_rdy (data_rdy_pwm)
);




//-----------------------------------------
//        			Equal0	
//-----------------------------------------

wb_equal equal0 (
	.clk (      clk          ),
	.reset (    ~rst          ),
	//
	.wb_adr_i( equal0_adr   ),
	.wb_dat_i( equal0_dat_w ),
	.wb_dat_o( equal0_dat_r ),
	.wb_stb_i( equal0_stb   ),
	.wb_cyc_i( equal0_cyc   ),
	.wb_we_i (  equal0_we    ),
	.wb_sel_i( equal0_sel   ),
	.wb_ack_o( equal0_ack   ),
	.datain  ( data_in_eq   ),
	.RDYin   (   start_tx_in_eq  ),
//	.RDYout   (   data_rdy_out_eq   ),
	.eqbass (data_eq_out0 )

);
//----------------------------------------------------------------------------
// Mux UART wires according to sw[0]
//----------------------------------------------------------------------------

assign uart_txd  = uart0_txd;
assign uart0_rxd = uart_rxd;
assign led       = gpio_in[0];


//ADC Wires			input	signal0	= signal
assign eoc0      = eoc;
assign cs        = cs0;
assign cstart	 = cstart0;
assign ADC_clk   = ADC0_clk;
assign busy = busy0;
assign realt = realt0;
assign data_adc=data_adc0;		//Datapath
assign data_in_adc0  = data_in_adc;
assign data_out_adc  = data_out_adc0;
assign data_rdy_adc0  = data_rdy_adc;
assign start_tx_adc_in = start_tx_eff_out;

//PWM wires
assign pwmout    = pwmout0;
assign pwmin0    = data_eq_out0; 
assign start_tx_in_pwm = start_tx_eff_out;
//assign data_rdy_pwm = data_rdy_eff0;


//GPIO wires
assign gpio0_in  = gpio_in;

// Effects Wires
assign data_in_eff = data_adc; //
assign data_out_eff = data_out_eff0;
assign data_rdy_in_eff = data_rdy_adc;

//Equal0 Wires
//assign data_in_eq = data_out_eff0;
//assign data_out_eq = effects_out0;
//assign data_rdy_in_eq = start_tx_eff_out;
//assign data_rdy_out_eq = data_rdy_eff0;
//assign start_tx_eq_in = start_tx_eff_out;
//assign start_tx_eq_out = start_tx_eff_out;

endmodule 
