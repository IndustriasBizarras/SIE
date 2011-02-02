`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:22:07 04/12/2010
// Design Name:   ADC_peripheral
// Module Name:   /home/juan64bits/ebd/ECB/nn-usb-fpga/Examples/ADC/logicISE/ADC_peripheral_tb.v
// Project Name:  logicISE
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: ADC_peripheral
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module ADC_peripheral_tb;

	// Inputs
	reg clk;
	reg reset;
	reg cs;
	reg ADC_EOC;
	reg [10:0] addr;
	reg [7:0] wrBus;
	reg we;

	// Outputs
	wire ADC_CS;
	wire ADC_CSTART;
	wire ADC_SCLK;
	wire [7:0] rdBus;

	// Bidirs
	wire ADC_SDIN;
	wire ADC_SDOUT;

	// Instantiate the Unit Under Test (UUT)
	ADC_peripheral uut (
		.clk(clk), 
		.reset(reset), 
		.cs(cs), 
		.ADC_EOC(ADC_EOC), 
		.ADC_CS(ADC_CS), 
		.ADC_CSTART(ADC_CSTART), 
		.ADC_SCLK(ADC_SCLK), 
		.ADC_SDIN(ADC_SDIN), 
		.ADC_SDOUT(ADC_SDOUT), 
		.addr(addr), 
		.rdBus(rdBus), 
		.wrBus(wrBus), 
		.we(we)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		reset = 0;
		cs = 0;
		ADC_EOC = 1;
		addr = 0;
		wrBus = 0;
		we = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		addr = 0;
		wrBus = 1;
		we = 1;
		cs = 1;
		#20;
		addr = 0;
		wrBus = 0;
		we = 0;
		cs = 0;
		#20;

		addr = 1;
		wrBus = 8;
		we = 1;
		cs = 1;
		#20;
		addr = 0;
		wrBus = 0;
		we = 0;
		cs = 0;
		#20;

		addr = 2;
		wrBus = 0;
		we = 1;
		cs = 1;
		#20;
		addr = 0;
		wrBus = 0;
		we = 0;
		cs = 0;
		#20;
		
		addr = 3;
		wrBus = 0;
		we = 1;
		cs = 1;
		#20;
		addr = 3;
		wrBus = 0;
		we = 0;
		cs = 0;
		#20;		
		
		addr = 3;
		wrBus = 8'h39;
		we = 1;
		cs = 1;
		#20;
		addr = 3;
		wrBus = 0;
		we = 0;
		cs = 1;
		#20;		

    while(rdBus[5])
    begin
      #20;
    end	
		#100;
		addr = 3;
		wrBus = 8'h39;
		we = 1;
		cs = 1;
		#20;
		addr = 3;
		wrBus = 0;
		we = 0;
		cs = 1;
		#20;		

    while(rdBus[5])
    begin
      #20;
    end
		#100;
		addr = 0;
		wrBus = 2;
		we = 1;
		cs = 1;
		#20;
		addr = 0;
		wrBus = 0;
		we = 0;
		cs = 0;
		#20;

		addr = 1;
		wrBus = 10;
		we = 1;
		cs = 1;
		#20;
		addr = 0;
		wrBus = 0;
		we = 0;
		cs = 0;
		#20;

		addr = 2;
		wrBus = 0;
		we = 1;
		cs = 1;
		#20;
		addr = 0;
		wrBus = 0;
		we = 0;
		cs = 0;
		#20;
		
		addr = 3;
		wrBus = 8'h2B;
		we = 1;
		cs = 1;
		#20;
		addr = 3;
		wrBus = 0;
		we = 0;
		cs = 1;
		#20;		

    while(rdBus[5])
    begin
      #20;
    end		
		#100;

		addr = 1;
		wrBus = 15;
		we = 1;
		cs = 1;
		#20;
		addr = 0;
		wrBus = 0;
		we = 0;
		cs = 0;
		#20;
		
		addr = 3;
		wrBus = 8'h2C;
		we = 1;
		cs = 1;
		#20;
		addr = 3;
		wrBus = 0;
		we = 0;
		cs = 1;
		#20;		

    while(rdBus[5])
    begin
      #20;
    end		
		#100;

		addr = 1;
		wrBus = 20;
		we = 1;
		cs = 1;
		#20;
		addr = 0;
		wrBus = 0;
		we = 0;
		cs = 0;
		#20;
		
		addr = 3;
		wrBus = 8'h2D;
		we = 1;
		cs = 1;
		#20;
		addr = 3;
		wrBus = 0;
		we = 0;
		cs = 1;
		#20;		

    while(rdBus[5])
    begin
      #20;
    end	
		#100;
	end

// Match Xport 2.0 50 MHz clock on FPGA (20ns period)
always begin clk = ~clk; #10; end
      
endmodule

