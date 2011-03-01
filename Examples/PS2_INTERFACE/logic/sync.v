`timescale 1ns / 1ps

module sync # (parameter N = 13, M = 8)
                 (input clk,
                  inout [M-1:0] data, 
						input [N-1:0] addr, 
						input nwe, 
						input ncs, 
						input noe, 
						input [M-1:0] rdBus, 
                  output reg sncs, 
						output reg snwe, 
						output reg [N-1:0] buffer_addr, 
						output [M-1:0] buffer_data);
  

  // interefaz signals assignments
  wire   T = ~noe | ncs;
  assign data = T?8'bZ:rdBus;
  assign buffer_data = data;
  
  // synchronize assignment
  always  @(negedge clk)
  begin
    sncs   <= ncs;
    snwe   <= nwe;
    buffer_addr <= addr;
  end


endmodule
