`timescale 1ns / 1ps

module blink_TB;

   reg  clk;
   reg  reset;
   wire led;

   blink uut ( .clk(clk), .reset(reset), .led(led));

   parameter PERIOD          = 20;
   parameter real DUTY_CYCLE = 0.5;
   parameter OFFSET          = 0;
   parameter TSET            = 3;
   parameter THLD            = 3;
   parameter NWS             = 3;
	 
   event reset_trigger;


   initial begin  // Initialize Inputs
      clk = 0; reset = 0;
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
        @ (reset_trigger);
        @ (negedge clk);
        reset = 1;
        @ (negedge clk);
        reset = 0;
      end
   end
	 

   initial begin: TEST_CASE
     $dumpfile("blink_TB.vcd");
     $dumpvars(-1, uut);
	
     #10 -> reset_trigger;
     #((PERIOD*DUTY_CYCLE)*100) $finish;
   end

endmodule

