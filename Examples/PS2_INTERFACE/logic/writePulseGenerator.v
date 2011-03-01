`timescale 1ns / 1ps

module writePulseGenerator      (input  clk, 
											input  snwe, 
											input  sncs, 
											input  reset, 
											output reg we);
  
  reg              w_st;

  // write access cpu to bram
  always @(posedge clk)
    if(~reset) {w_st, we} <= 0;
      else begin
        
        case (w_st)
          0: begin
                we <= 0;
                if(sncs | snwe) 
				    w_st <= 1;
              end
          1: begin
               if(~(sncs | snwe)) 
					  begin
                 we    <= 1;
                 w_st  <= 0;
                 end	
               else we <= 0;
             end
          endcase
        end

endmodule
