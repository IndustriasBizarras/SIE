module control(clk, lsb_B, start, reset, out_comp, load_rst, shift_inc, acc);


 input clk;
 input lsb_B;
 input start; 
 input reset;
 input out_comp;

 output load_rst;
 output shift_inc;
 output acc;

 reg [1:0]state;
 reg load_rst;
 reg shift_inc;
 reg acc;


 parameter S0  = 2'b00;
 parameter S1  = 2'b01;
 parameter S2  = 2'b10;
 parameter S3  = 2'b11;

always @(posedge clk) begin
  if (reset)
       state = S0;
  else 
    case(state)
     S0:
      if(start)
        state = S1;
      else
        state = S0;
     S1:
      if(out_comp)
        state = S1;
      else
       if(lsb_B)
        state = S2;
       else
        state = S3;
     S2: state = S3;
     
     S3: state = S1;
     default: state = S0;
   endcase
 end

always @(state) begin
  case(state)
    S0:begin
          load_rst=1'b1;
          shift_inc=1'b0;
          acc=1'b0; 
       end
    S1:begin
          load_rst=1'b0;
          shift_inc=1'b0;
          acc=1'b0; 
       end
    S2:begin
          load_rst=1'b0;
          shift_inc=1'b0;
          acc=1'b1; 
       end
    S3:begin
          load_rst=1'b0;
          shift_inc=1'b1;
          acc=1'b0; 
       end
    default:
      begin
          load_rst=1'b1;
          shift_inc=1'b0;
          acc=1'b0; 
       end
  endcase
end

endmodule
