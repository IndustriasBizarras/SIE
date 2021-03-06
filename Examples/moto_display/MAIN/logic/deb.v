`timescale 1ns / 1ps

/*
M�dulo encargado de la eliminaci�n del rebote en los contactos de los pulsadores
*/
module deb(
	input nCS,
    input PB_1,
    input PB_2,
    input PB_3,
    input PB_4,
    input PB_5,
    input IND1,
    input IND2,
    input IND3,
    input IND4,
    input IND5,
    input clk, reset,
    output [7:0] data_tecla,
    output led,
    output irq_pin
    );

//Definici�n del retardo para el circuito antirebote
    parameter NDELAY = 650000;
//definici�n del registro Nbits
    parameter NBITS = 20;

//Registros de salida de la se�al filtrada por el circuito antirebote 
    reg in_1=0;
    reg in_2=0;
    reg in_3=0;
    reg in_4=0;
    reg in_5=0;
    reg in_d1=0;
    reg in_d2=0;
    reg in_d3=0;
    reg in_d4=0;
    reg in_d5=0;
    
//Pulsador 1 (UP)
   reg [NBITS-1:0] count1;
   reg xnew1;

   always @(posedge clk)
     if (~reset) 
	    begin 
	     xnew1 <= ~PB_1; 
	     in_1 <= in_1; 
	     count1 <= 0; 
	    end
     else if (~PB_1 != xnew1) 
	    begin 
	     xnew1 <= ~PB_1; 
	     count1 <= 0; 
	    end
     else if (count1 == NDELAY) 
	     in_1 <= xnew1;
	  else 
	     count1 <= count1+1;

//Pulsador 2 (DOWN)
   reg [NBITS-1:0] count2;
   reg xnew2;

   always @(posedge clk)
     if (~reset) 
            begin 
             xnew2 <= ~PB_2; 
             in_2 <= in_2; 
             count2 <= 0; 
            end
     else if (~PB_2 != xnew2) 
            begin 
             xnew2 <= ~PB_2; 
             count2 <= 0; 
            end
     else if (count2 == NDELAY) 
            in_2 <= xnew2;
          else 
            count2 <= count2+1;
	  
//Pulsador 3 (LEFT)
   reg [NBITS-1:0] count3;
   reg xnew3;

   always @(posedge clk)
     if (~reset)  
            begin 
             xnew3 <= ~PB_3; 
             in_3 <= in_3; count3 <= 0; 
            end
     else if (~PB_3 != xnew3) 
            begin 
             xnew3 <= ~PB_3; 
             count3 <= 0; 
            end
     else if (count3 == NDELAY) 
            in_3 <= xnew3;
          else 
            count3 <= count3+1;
	  
//Pulsador 4 (RIGHT)
   reg [NBITS-1:0] count4;
   reg xnew4;

   always @(posedge clk)
     if (~reset) 
            begin 
             xnew4 <= ~PB_4; 
             in_4 <= in_4; 
             count4 <= 0; 
            end
     else if (~PB_4 != xnew4) 
            begin 
             xnew4 <= ~PB_4; 
             count4 <= 0; end
     else if (count4 == NDELAY) 
             in_4 <= xnew4;
          else 
             count4 <= count4+1;
	  
//Pulsador 5 (ENTER)
   reg [NBITS-1:0] count5;
   reg xnew5;

   always @(posedge clk)
     if (~reset) 
            begin 
             xnew5 <= ~PB_5; 
             in_5 <= in_5; 
             count5 <= 0; 
            end
     else if (~PB_5 != xnew5) 
            begin 
             xnew5 <= ~PB_5; 
             count5 <= 0; 
            end
     else if (count5 == NDELAY) 
             in_5 <= xnew5;
          else 
             count5 <= count5+1;
	  
//Entradas digitales que no requieren de un tratamiento antirebote
   always@(posedge clk)
     if (~reset)
	    begin
             in_d1 <= 0; 
             in_d2 <= 0;
	          in_d3 <= 0;
	          in_d4 <= 0;
             in_d5 <= 0;
           
   	    end
     else
            begin
             in_d1 <= ~IND1;
             in_d2 <= ~IND2;
             in_d3 <= ~IND3;
             in_d4 <= ~IND4;
             in_d5 <= ~IND5;
            end

//registro en el cual se almacena el pulsador accionado
reg [7:0] aux_reg;
//reg [2:0] state;

//Seg�n la tecla activada, se almacena un n�mero en el registro aux_reg
   always@(posedge clk) 
     if (~reset) 
     //begin
	     aux_reg <= 0;
	 //    state<=0;
     //end
     else 
     
     		if (in_1)                //UP
        	      aux_reg<=202;
	  		else if (in_2)   //DOWN	
			   aux_reg<=182;
	  		else if (in_3)   //RIGHT
	    	       aux_reg<=232;
	  		else if (in_4)   //LEFT
	    	       aux_reg<=75;
	  		else if (in_5)   //ENTER
			   aux_reg<=86;
     		else if (in_d1)         //Direccional derecha
	    	       aux_reg<=1;     
	  		else if (in_d2) //Direccional izquierda
		       aux_reg<=2;
	  		else if (in_d3) //Se�al disponible
	    	       aux_reg<=3;
	  		else if (in_d4) //Se�al disponible
	    	       aux_reg<=4;
	  		else if (in_d5) //Se�al disponible
	               aux_reg<=5;
	  		
	 
assign data_tecla = aux_reg;
//se asignan las respectivas salidas

//Led de la sie, se�al utilizada para Debug
assign led = in_1 | in_2 | in_3 | in_4 | in_5 | in_d1 | in_d2 | in_d3 | in_d4 | in_d5;

//si alguna tecla es presionada se activa la interrupci�n
assign irq_pin = in_1 | in_2 | in_3 | in_4 | in_5 | in_d1 | in_d2 | in_d3 | in_d4 | in_d5;

endmodule
