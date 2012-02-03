`timescale 1ns / 1ps
module deb_main(clk, sram_data, addr, ncs, noe, reset, led_sie, irq,
                 PB_1, PB_2, PB_3, PB_4, PB_5, IND1, IND2, IND3, IND4, IND5);
  
    parameter   B = (7);

    input clk, addr, ncs, noe, reset;
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
	 output led_sie, irq;
    inout [B:0] sram_data;
    
    
    // synchronize signals  
   
    reg     [12:0]  buffer_addr; 
    reg     [B:0]	buffer_data;   

    // bram interfaz signals
    wire    [7:0]  data_tecla;
	 wire    led, irq_pin;
    
    // interfaz fpga signals    
    wire    [12:0]  addr;


    reg     [25:0]  counter;
 
        
    // interefaz signals assignments
    wire   T = ~noe | ncs;
    assign sram_data = T?4'bZ:data_tecla;
	 
	 
    // synchronize assignment
    always  @(negedge clk)
    begin
        buffer_data <= sram_data;
        buffer_addr <= addr;
    end

   /* // Peripherals control
    wire     [3:0]   csN;
    wire     [7:0]   data_tecla0, data_tecla1, data_tecla2, data_tecla3;
      
    assign csN = buffer_addr[12]? (buffer_addr[11]? 4'b1000: 4'b0100)
                                : (buffer_addr[11]? 4'b0010: 4'b0001);

    assign data_tecla = buffer_addr[12]? (buffer_addr[11]? data_tecla3: data_tecla2)
                                  : (buffer_addr[11]? data_tecla1: data_tecla0);
*/					      
// Peripheral instantiation
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
    .clk(clk), 
    .reset(reset), 
    .data_tecla(data_tecla), 
    .led(led_sie), 
    .irq_pin(irq)
    );
	 
endmodule

