`timescale 1ns / 1ps
module RPM_main(clk, sram_data, ncs, noe, reset, pulse_in);
  
    parameter   B = (7);

    input clk, ncs, noe, reset;
	 input pulse_in;
    inout [B:0] sram_data;
  
    // bram interfaz signals
    wire    [B:0]  data_RPM;
    
   // interefaz signals assignments
    wire   T = ~noe | ncs;
    assign sram_data = T?8'bZ:data_RPM;
	 
	   
 RPM RPM (
    .pulse_in(pulse_in), 
    .clk(clk), 
    .reset(reset), 
    .data_RPM(data_RPM)
    );
	 
endmodule

