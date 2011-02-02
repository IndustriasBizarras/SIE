`timescale 1ns / 1ps

module ps2_rx(
    input wire  clk, reset,
    input wire ps2_data, ps2_clk, rx_en,
    output reg rx_done,
    output wire [7:0] dout
    );

  //signal declaration
  reg [1:0] state_reg, state_next;
  reg [7:0] filter_reg;
  wire [7:0] filter_next;
  reg f_ps2c_reg;
  wire f_ps2c_next;
  reg [3:0] n_reg, n_next;
  reg [10:0] b_reg, b_next;
  wire fall_edge;
  
  //====================================================
  // falling - edge generation for ps2_clk
  //====================================================
   always @(posedge clk, posedge reset)
   if (reset)
      begin
         filter_reg <= 0;
         f_ps2c_reg <= 0;
      end
   else
      begin
         filter_reg <= filter_next;
         f_ps2c_reg <= f_ps2c_next;
      end

   assign filter_next = {ps2_clk, filter_reg[7:1]};
   assign f_ps2c_next = (filter_reg==8'b11111111) ? 1'b1 :
                        (filter_reg==8'b00000000) ? 1'b0 :
                         f_ps2c_reg;
   assign fall_edge = f_ps2c_reg & ~f_ps2c_next;

  //==============================================================
  // FSM
  //==============================================================
  // state & data registers
  always @(posedge clk, posedge reset)
    if(reset)
	    begin
		  state_reg <= 1;
		  n_reg <= 0;
		  b_reg <= 0;
		  end
    else
	    begin
		  state_reg <= state_next;
		  n_reg <= n_next;
		  b_reg <= b_next;
		  end
  // next state logic 
  always @(*)
    begin
	  state_next = state_reg;
		n_next = n_reg;
		b_next = b_reg;
    rx_done = 1'b0;
		case(state_reg)
		  1:
		       if(fall_edge & rx_en)
				   begin
					  //shift in start bit
					  b_next = {ps2_data, b_reg[10:1]};
					  n_next = 4'b1001;
					  state_next = 2;
					end
		  2:  // 8 data + 1 parity + 1 stop
      begin
		      if(fall_edge)
				  begin
				    b_next = {ps2_data, b_reg[10:1]};
            
					 if(n_reg==0)
					   state_next = 3;
					 else
					   n_next = n_reg-1;
				  end
      end
		  3:  // 1 extra clock to complete the last shift
		       begin
				   state_next = 1;
           rx_done = 1'b1;
				   end
      default: state_next = 1;
		endcase
	 end
	 
	 //output
	 assign dout = b_reg[8:1]; //data bits

endmodule
