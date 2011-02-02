`timescale 1ns / 1ps
module sram_bus(clk, sram_data, addr, nwe, ncs, noe, reset, led, irq_pin);
  parameter     B = (7);

  input            clk, nwe, ncs, noe, reset;
  input [12:0]     addr;
  inout [B:0]      sram_data;
  output           led;
  input            irq_pin;

  // synchronize signals                               
  reg    sncs, snwe;
  reg    [12:0] buffer_addr;
  reg    [B:0] buffer_data;  

  // interfaz fpga signals
//  wire   [12:0] addr;
	
  // bram interfaz signals
  reg    we;
  reg    w_st;

  reg    [B:0] wdBus;
  wire   [B:0] rdBus;

  // interefaz signals assignments
  wire   T = ~noe | ncs;
  assign sram_data = T?8'bZ:rdBus;
  
  //--------------------------------------------------------------------------

  // synchronize assignment
  always  @(negedge clk)
  begin
    sncs   <= ncs;
    snwe   <= nwe;
    buffer_data <= sram_data;
    buffer_addr <= addr;
  end

  // write access cpu to bram
  always @(posedge clk)
    if(~reset) {w_st, we, wdBus} <= 0;
      else begin
        wdBus <= buffer_data;
        case (w_st)
          0: begin
              we <= 0;
              if(sncs | snwe) w_st <= 1;
          end
          1: begin
            if(~(sncs | snwe)) begin
              we    <= 1;
              w_st  <= 0;
            end	
            else we <= 0;
          end
        endcase
      end

RAMB16_S2 ba0( .CLK(~clk), .EN(1'b1),   .SSR(1'b0), .ADDR(buffer_addr),
               .WE(we),   .DI(wdBus[1:0]), .DO(rdBus[1:0]) );

RAMB16_S2 ba1( .CLK(~clk), .EN(1'b1),   .SSR(1'b0), .ADDR(buffer_addr),
               .WE(we),   .DI(wdBus[3:2]), .DO(rdBus[3:2]) );

RAMB16_S2 ba2( .CLK(~clk), .EN(1'b1),   .SSR(1'b0), .ADDR(buffer_addr),
               .WE(we),   .DI(wdBus[5:4]), .DO(rdBus[5:4]) );

RAMB16_S2 ba3( .CLK(~clk), .EN(1'b1),   .SSR(1'b0), .ADDR(buffer_addr),
               .WE(we),   .DI(wdBus[7:6]), .DO(rdBus[7:6]) );

  reg [24:0]  counter;
  always @(posedge clk) begin
    if (~reset)
      counter <= {25{1'b0}};
    else
      counter <= counter + 1;
  end 
  assign led = counter[24];

endmodule

