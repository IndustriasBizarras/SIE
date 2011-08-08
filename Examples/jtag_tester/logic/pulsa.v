`timescale 1ns / 1ps
module pulsa(sram_data, ncs, noe, pb2, pb3);
  parameter     B = (7);

  input            ncs, noe;
  inout [B:0]      sram_data;
  input		   pb2;
  input		   pb3;

  wire   [B:0] rdBus;
  assign rdBus[B:0] = {6'b0, pb3, pb2};
  

  // interefaz signals assignments
  wire   T = ~noe | ncs;
  assign sram_data = T?8'bZ:rdBus;

endmodule
