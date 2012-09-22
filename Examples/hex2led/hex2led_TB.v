`timescale 1ns / 1ps

module hex2led_TB;

   reg  [3:0]HEX;
   wire [6:0]LED;

   hex2led uut ( .HEX(HEX), .LED(LED));

   parameter PERIOD          = 20;
   parameter real DUTY_CYCLE = 0.5;
   parameter OFFSET          = 0;
   parameter TSET            = 3;
   parameter THLD            = 3;
   parameter NWS             = 3;
	 
   integer i;

   initial begin: TEST_CASE
     $dumpfile("hex2led_TB.vcd");
     $dumpvars(-1, uut);
     #10 HEX = 4'h0;
     for(i=0; i<16; i=i+1) begin
        #10 HEX <= i;
     end
   end

endmodule

