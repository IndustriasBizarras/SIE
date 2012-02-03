`timescale 1ns / 1ps

/*Módulo periférico encargado de contar pulsos por minuto*/
module RPM(pulse_in, clk, reset, data_RPM);

parameter B = (7);

input wire pulse_in;
input clk;
input reset;
output wire [B:0] data_RPM;
reg pulse_aux;
wire rising_pulse;
reg [15:0] treg, tnext; 
reg [9:0] preg, pnext; 
reg [1:0] state;
reg [1:0] state_next;
localparam  COUNT_MS = 50000;

//rising pulse detector
always@ (posedge clk) 
    if  (~reset) begin
      pulse_aux <= 0; 
	state <= 0;
	treg  <=  0; 
      preg  <=  0; 
		end
    else begin
      pulse_aux <= pulse_in; 
      state <= state_next;
      treg  <=  tnext; 
      preg  <=  pnext; 
		end
 
assign  rising_pulse = ~pulse_aux & pulse_in;

//counter and timer
always @* 
     begin 
         state_next = state; 
         pnext  =  preg; 
         tnext  =  treg; 
case (state) 
   0:     state_next  =  1; 
   1:  
      if  (rising_pulse) 
        begin 
         state_next  =  2; 
         tnext  =  0; 
         pnext  =  0; 
        end 
   2: 
      if  (rising_pulse)   
        state_next  =  3; 
      else  
      if  (treg == COUNT_MS-1) 
        begin 
         tnext  =  0; 
         pnext  =  preg  +  1; 
        end 
      else 
         tnext  =  treg  +  1; 
   3: 
         state_next  =  0; 
       
default: 
         state_next  =  0; 

endcase
end

assign  data_RPM = preg; 
  
endmodule
