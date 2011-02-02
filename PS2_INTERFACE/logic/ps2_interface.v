`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: UNAL
// Engineer: Ari Bejarano
// 
// Create Date:    16:28:50 09/30/2010 
// Design Name:    ps2_interface
// Module Name:    ps2_interface 
// Project Name:   ps2_interface
// Target Devices: 
// Tool versions:  2.0
// Description: ¬¬
//
// Dependencies: sync.v, writePulseGenerator.v, kb_ps2
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//  
//////////////////////////////////////////////////////////////////////////////////
module ps2_interface(clk, data, addr, nwe, ncs, noe, reset, ps2_data, ps2_clk, irq_kb, led);
  
  parameter N = 13, M = 8;// M # de lineas de datos, N # de lineas de dirección

  input            clk, nwe, ncs, noe, reset;
  input [N-1:0]    addr;
  inout [M-1:0]    data;
  inout            ps2_clk;
  inout            ps2_data;
  output           irq_kb;
  output           led;
  
  wire  sncs;
  wire  snwe;
  wire  [N-1:0] buffer_addr;
  wire  [M-1:0]      rdBus;
  wire  [M-1:0] wdBus;
  wire  we;
  wire rx_done;
  
  assign led    = ps2_clk;
  
  sync # (.N(13), .M(8))// M # de lineas de datos, N # de lineas de dirección
  sync_U1(.clk(clk),              
         .data(data),
		     .addr(addr), 
		     .nwe(nwe), 
		     .ncs(ncs), 
		     .noe(noe), 
		     .rdBus(rdBus), 
         .sncs(sncs), 
		     .snwe(snwe), 
		     .buffer_addr(buffer_addr), 
		     .buffer_data(wdBus));
										 
  writePulseGenerator writePulseGenerator_U2 (.clk(clk), 
								                              .snwe(snwe), 
								                              .sncs(sncs), 
								                              .reset(reset), 
								                              .we(we));

  kb_ps2 kb_ps2_U3(.clk(~clk), 
                  .reset(~reset),
                  .we_ps2(we),
                  .ps2_data(ps2_data), 
                  .ps2_clk(ps2_clk),
                  .din(wdBus),
                  .rx_done(rx_done), 
                  .tx_done(),
                  .dout(rdBus));
                  
  pulse_expander pulse_expander_U4(
    .clk(clk),
    .reset(~reset),
    .pulse_in(rx_done),
    .pulse_out(irq_kb)
  );


endmodule
