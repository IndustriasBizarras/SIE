`timescale 1ns / 1ps
module uart_peripheral(clk, sram_data, addr, nwe, ncs, noe, reset, led, RxD,TxD,irq_pin,RxD2,TxD2);
  parameter     B = (7);

  input            clk, nwe, ncs, noe, reset,RxD,RxD2;
  input [2:0]     addr;
  inout [B:0]      sram_data;
  output           led,TxD,TxD2;
  output            irq_pin;
	wire [6:0] ISRC_LP;
  // synchronize signals                               
  reg    sncs, snwe;
  reg    [12:0] buffer_addr;
  reg    [B:0] buffer_data;  
  reg [23:0]  counter;  
  // interfaz fpga signals
//  wire   [12:0] addr;
	
  // bram interfaz signals
  reg    we;
  reg    w_st;
  wire [7:0] RD;
  reg    [B:0] wdBus;
  wire   [B:0] rdBus;
  // interefaz signals assignments
  wire   T = ~noe | ncs;
  assign sram_data = T?8'bZ:rdBus;
  assign out=irq_pin;
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



//the UART Module
UART UART(
        .CLK(clk),
        .reset(~reset),
        .CS(~sncs),
        .nRW(we),
        .data_in(wdBus),
        .data_out(rdBus),
        .RxD(RxD),
        .TxD(TxD),
        .add(buffer_addr),
	.nIRQ(irq_pin)
);

  always @(posedge clk) begin
    if (~reset)
      counter <= {24{1'b0}};
    else
      counter <= counter + 1;
  end 
  assign led = counter[23];


endmodule 
