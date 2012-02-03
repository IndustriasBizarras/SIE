`timescale 1ns / 1ps
module deb_main(clk, sram_data, ncs, noe, reset, led_sie, irq,
                 PB_1, PB_2, PB_3, PB_4, PB_5, IND1, IND2, IND3, IND4, IND5, IND6);
  
    parameter   B = (3);

    input clk, ncs, noe, reset;
	 input PB_1;
    input PB_2;
    input PB_3;
    input PB_4;
    input PB_5;
    input IND1;
    input IND2;
    input IND3;
    input IND4;
    input IND5;
    input IND6;
	 output led_sie, irq;
    inout [B:0] sram_data;
  
    // bram interfaz signals
    wire    [3:0]  data_tecla;

   // interefaz signals assignments
    wire   T = ~noe | ncs;
    assign sram_data = T?4'bZ:data_tecla;
	 
	   
   deb deb (
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
    .IND6(IND6), 
    .clk(clk), 
    .reset(reset), 
    .data_tecla(data_tecla), 
    .led(led_sie), 
    .irq_pin(irq)
    );
	 
endmodule

