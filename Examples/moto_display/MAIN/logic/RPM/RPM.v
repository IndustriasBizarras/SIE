`timescale 1ns / 1ps


module RPM(pulse_in, clk, reset, data_RPM);

parameter B = (7);
parameter T = (25);
parameter C = (50000000);

input pulse_in;
input clk;
input reset;
output reg [B:0] data_RPM;


reg [B:0] counter	= 0;
reg [T:0] timer_reg = 0;
reg timer; 


//Temporizador configurado a 1 Seg 
always@(posedge clk or negedge reset)
   if (~reset) 
	 begin timer_reg <= 0; timer <= 0;	end
	else begin
	     if (timer_reg <= C-1) 
	        begin timer_reg <= timer_reg + 1; timer <= 1; end 	
	     else 
           begin timer_reg <= 0; timer <= 0;	end    	
	     end

//Contador de pulsos de la bobina de encedido del motor (revoluciones del motor)
always@(posedge pulse_in)  
     if(timer)
         counter <= counter + 1;
     else
	      counter <= 0;
	  				  

//Sincronizacion del dato de salida
always@(posedge clk)
      if (~reset)
           data_RPM = 0;
      else
           data_RPM = counter;		
	  
endmodule
