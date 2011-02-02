`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:   U.N
// Engineer:    Ari Andrés Bejarano H. 
// 
// Create Date:    07:19:56 10/15/2010 
// Design Name: 
// Module Name:    pulse_expander 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: expande pulse_out = (pulse_in) + (num * pulses of clk)
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module pulse_expander(
    input clk,
    input reset,
    input pulse_in,
    output reg pulse_out
    );
    
    parameter num = 5000;

    reg [24:0] cnt;
    reg flag;
    
    always@(posedge clk)begin
    
      if(reset)
        begin
        cnt <= 0;
        pulse_out <= 0;
        flag <= 0;
        end
      else
        if(pulse_in || flag)
          if(cnt < num) 
            begin
            cnt <= cnt+1;
            pulse_out <= 1;
            flag <= 1;
            end
          else 
            begin                 
            cnt <= 0;                    
            pulse_out <= 0;
            flag <= 0;
            end        
    end

endmodule
