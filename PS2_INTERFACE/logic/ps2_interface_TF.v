`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:48:20 10/15/2010
// Design Name:   ps2_interface
// Module Name:   /home/ari/Xilinx_Projects/ps2_interface/ps2_interface_TF.v
// Project Name:  ps2_interface
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: ps2_interface
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module ps2_interface_TF;

	// Inputs
	reg clk;
	reg [12:0] addr;
	reg nwe;
	reg ncs;
	reg noe;
	reg reset;

	// Outputs
	wire irq_kb;
  wire led;

	// Bidirs
	wire [7:0] data;
	wire ps2_data;
	wire ps2_clk;

	reg ps2_datar;
	reg ps2_clkr;
  reg [7:0] datar;

	// Instantiate the Unit Under Test (UUT)
	ps2_interface uut (
		.clk(clk), 
		.data(data), 
		.addr(addr), 
		.nwe(nwe), 
		.ncs(ncs), 
		.noe(noe), 
		.reset(reset), 
		.ps2_data(ps2_data), 
		.ps2_clk(ps2_clk), 
		.irq_kb(irq_kb),
    .led(led)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		addr = 0;
		nwe = 1;
		ncs = 0;
		noe = 1;
		reset = 1;
    ps2_datar = 1;
    ps2_clkr  = 1;
    datar = 8'bz;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
    reset = 0;
		#100;
    reset = 1;
    #100;
    
    //start
    #25000;
    ps2_datar=0;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //data1
    #25000;
    ps2_datar=0;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //data2
    #25000;
    ps2_datar=0;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //data3
    #25000;
    ps2_datar=1;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //data4
    #25000;
    ps2_datar=1;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //data5
    #25000;
    ps2_datar=1;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //data6
    #25000;
    ps2_datar=0;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //data7
    #25000;
    ps2_datar=0;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //data8
    #25000;
    ps2_datar=0;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //parity
    #25000;
    ps2_datar=0;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    //stop
    #25000;
    ps2_datar=1;
    #25000;
    ps2_clkr=0;
    #50000;
    ps2_clkr=1;
    
    #50000;
    datar=8'b01011010;
    noe = 0;
    nwe = 0;
    ps2_datar=1'bz;
    ps2_clkr=1'bz;
    
    #400
    nwe = 1;
    
    #80000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;
    #50000
    ps2_clkr=0;
    #50000
    ps2_clkr=1;

	end
  
  always
    #10 clk=!clk;
  
  initial  begin
    $dumpfile ("ps2_interface_TF.vcd"); 
    $dumpvars; 
  end
  
  initial  begin
    $display("\t\ttime,\tclk,\tdata,\taddr,\tnwe,\tncs,\tnoe,\treset,\tps2_data,\tps2_clk,\tirq_kb"); 
    $monitor("%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d",
             $time,clk,data,addr,nwe,ncs,noe,reset,ps2_data,ps2_clk,irq_kb); 
  end
  
  initial 
   #3000000  $finish;
   
  assign ps2_clk=ps2_clkr;
  assign ps2_data=ps2_datar;
  assign data=datar;
      
endmodule

