`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   08:01:22 10/15/2010
// Design Name:   pulse_expander
// Module Name:   /home/ari/Xilinx_Projects/keyboard/pulse_expander_TF.v
// Project Name:  keyboard
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: pulse_expander
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module pulse_expander_TF;

	// Inputs
	reg clk;
	reg reset;
	reg pulse_in;

	// Outputs
	wire pulse_out;

	// Instantiate the Unit Under Test (UUT)
	pulse_expander uut (
		.clk(clk), 
		.reset(reset), 
		.pulse_in(pulse_in), 
		.pulse_out(pulse_out)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		reset = 0;
		pulse_in = 0;

		// Wait 100 ns for global reset to finish
		#100;
		// Add stimulus here
    reset = 1;
		#100;
    reset = 0;
    #100;
    pulse_in = 1;
    #20;
    pulse_in = 0;
    #400;
    pulse_in = 1;
    #20;
    pulse_in = 0;
	end
  
  always
  #10 clk=!clk;
  
  initial  begin
    $dumpfile ("pulse_expander_TF.vcd"); 
    $dumpvars; 
  end
  
  initial  begin
    $display("\t\ttime,\tclk,\treset,\tpulse_in,\tpulse_out"); 
    $monitor("%d,\t%b,\t%b,\t%b,\t%d",$time, clk,reset,pulse_in,pulse_out); 
  end
  
  initial 
   #2000  $finish;
      
endmodule

