`timescale 1ns / 1ps

module fsm2_TB;

  reg  clock;
  reg  reset;
  reg  req_0;
  reg  req_1;
  wire  gnt_0;
  wire  gnt_1; 


   fsm2 uut ( .clock(clock), .reset(reset), .req_0(req_0), .req_1(req_1), .gnt_0(gnt_0), .gnt_1(gnt_1));

   parameter PERIOD          = 20;
   parameter real DUTY_CYCLE = 0.5;
   parameter OFFSET          = 0;
   parameter TSET            = 3;
   parameter THLD            = 3;
   parameter NWS             = 3;
	 
   event reset_trigger;


   initial begin  // Initialize Inputs
      clock = 0; reset = 1;
      req_0 =0; req_1 =1;
   end

   initial  begin  // Process for clock
     #OFFSET;
     forever
       begin
         clock = 1'b0;
         #(PERIOD-(PERIOD*DUTY_CYCLE)) clock = 1'b1;
         #(PERIOD*DUTY_CYCLE);
       end
   end

   initial begin // Reset the system, Start the image capture process
      forever begin 
        @ (reset_trigger);
        @ (negedge clock);
        reset = 1;
        @ (negedge clock);
        reset = 0;
      end
   end
	 

   initial begin: TEST_CASE
     $dumpfile("fsm2_TB.vcd");
     $dumpvars(-1, uut);
	
     #10 -> reset_trigger;
     #((PERIOD*DUTY_CYCLE)*1000) $finish;
   end

endmodule

