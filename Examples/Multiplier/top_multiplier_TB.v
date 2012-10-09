`timescale 1ns / 1ps

`define SIMULATION


module top_multiplier_TB;

   reg  clk;
   reg  reset;
   reg  start;
   reg  [7:0]in_A;
   reg  [7:0]in_B;
   wire [15:0] pp;

   top_multiplier uut ( .clk(clk), .reset(reset), .start(start), .in_A(in_A), .in_B(in_B), .pp(pp) );

   parameter PERIOD          = 20;
   parameter real DUTY_CYCLE = 0.5;
   parameter OFFSET          = 0;
   reg [20:0] i;
   event reset_trigger;




   initial begin  // Initialize Inputs
      clk = 0; reset = 1; start = 0; in_A = 8'h0A; in_B = 8'h20;
   end

   initial  begin  // Process for clk
     #OFFSET;
     forever
       begin
         clk = 1'b0;
         #(PERIOD-(PERIOD*DUTY_CYCLE)) clk = 1'b1;
         #(PERIOD*DUTY_CYCLE);
       end
   end

   initial begin // Reset the system, Start the image capture process
      forever begin 
        start = 1;
        @ (reset_trigger);
        @ (posedge clk);
        reset = 1;
        @ (posedge clk);
        reset = 0;

       for(i=0; i<20; i=i+1) begin
         @ (posedge clk);
       end
          reset = 1;
      end
   end
	 

   initial begin: TEST_CASE
     $dumpfile("top_multiplier_TB.vcd");
     $dumpvars(-1, uut);
	
     #10 -> reset_trigger;
     #((PERIOD*DUTY_CYCLE)*60) $finish;
   end

endmodule

