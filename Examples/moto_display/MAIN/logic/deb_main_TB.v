`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   21:52:59 10/17/2011
// Design Name:   main
// Module Name:   /home/lipeandres/Desktop/ise_prueba/ise_prueba/main_TB.v
// Project Name:  ise_prueba
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: main
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module deb_main_TB_v;
parameter   B = (3);

	// Inputs
	reg clk, addr, ncs, noe, reset;
	reg PB_1;
    	reg PB_2;
    	reg PB_3;
    	reg PB_4;
    	reg PB_5;
    	reg IND1;
    	reg IND2;
    	reg IND3;
    	reg IND4;
    	reg IND5;
    	reg IND6;

	// Outputs
	wire led_sie, irq;
	wire [B:0] sram_data;


	// Instantiate the Unit Under Test (UUT)
	deb_main deb_main_v 
			(
			.clk(clk), 
			.sram_data(sram_data), 
			.addr(addr), 
			.ncs(ncs), 
			.noe(noe), 
			.reset(reset), 	
			.led_sie(led_sie), 
			.irq(irq),
			.PB_1(PB_1),
			.PB_2(PB_2),
			.PB_3(PB_3),
			.PB_4(PB_4),
			.PB_5(PB_5),
			.IND1(IND1),
			.IND2(IND2),
			.IND3(IND3),
			.IND4(IND4),
			.IND5(IND5),
			.IND6(IND6)
			);
	initial 
	begin
		clk=0;
		reset=1;
		ncs=1;
		noe=0;
		addr=1;
		PB_1=1;
	    	PB_2=1;
	    	PB_3=1;
	    	PB_4=1;
	    	PB_5=1;
	    	IND1=1;
	    	IND2=1;
	    	IND3=1;
	    	IND4=1;
	    	IND5=1;
	    	IND6=1;
	#100 
		reset=0;
	#100 
		reset=1;
		noe=1;
		ncs=0;
		PB_1=0;
	#20
		PB_1=1;
	#15
		PB_1=0;
	#15000000
		PB_1=1;	 
	end

//Reloj de 50MHz - 20ns
always #10 clk=~clk;
      
endmodule

