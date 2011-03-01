`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:22:40 10/07/2010 
// Design Name: 
// Module Name:    kb_ps2 
// Project Name: keyboard
// Target Devices: 
// Tool versions: 
// Description: controlador de teclado
//
// Dependencies: ps2_rx, ps2_tx
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module kb_ps2(
    input wire clk, reset,
    input wire we_ps2,
    inout wire ps2_data, ps2_clk,
    input wire [7:0] din,
    output wire rx_done, tx_done,
    output wire [7:0] dout
    );
    
   // signal declaration
   wire tx_idle;

   // instantiate ps2 receiver
   ps2_rx ps2_rx_1
      (.clk(clk), .reset(reset), .rx_en(tx_idle),
       .ps2_data(ps2_data), .ps2_clk(ps2_clk),
       .rx_done(rx_done), .dout(dout));
   // instantiate ps2 transmitter
   ps2_tx ps2_tx_1
      (.clk(clk), .reset(reset), .we_ps2(we_ps2),
       .din(din), .ps2_data(ps2_data), .ps2_clk(ps2_clk),
       .tx_idle(tx_idle), .tx_done(tx_done));


endmodule
