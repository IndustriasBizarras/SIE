`timescale 1ns / 1ps

module RPM	(
			input pulse,
			input clk,
			input reset,
			output reg[7:0] data_RPM
			);
			

reg[2:0]	pulse_in_rsync;
wire		pulse_in_rise;

parameter B = (12);
parameter T = (25);
parameter C = (50000000);

reg [B:0] counter	= 0;
reg [T:0] timer_reg = 0;
reg timer;

wire pulse_in;

assign pulse_in = ~pulse;
// Buscar flanco de subida en el pulso de entrada pulse_in
assign	pulse_in_rise = ~pulse_in_rsync[1] & pulse_in_rsync[0];

// Syncronizacion del pulso de entrada con el reloj de referencia
always @(posedge clk)
	pulse_in_rsync <= {pulse_in_rsync[1:0],pulse_in};


//Temporizador configurado a 1 Seg 
always@(posedge clk or negedge reset)
   if (~reset) 
	begin
		timer_reg <= 0;
		timer <= 0;
	end
	else
	begin
		if (timer_reg <= C-1) 
		begin
			timer_reg <= timer_reg + 1;
			timer <= 1;
		end 	
		else 
		begin
			timer_reg <= 0;
			timer <= 0;
		end
	end

reg [B:0] temp;

//Contador de pulsos de la bobina de encedido del motor (revoluciones del motor)
always@(posedge clk) 
	if(~timer || ~reset)
	begin
		temp <= (counter/32);
		counter <= 0;
		end
	else
		if(pulse_in_rise)
		counter<=counter+1;
		
//Sincronizacion del dato de salida
always@(posedge clk)
      if (~reset)
           data_RPM <= 0;
      else
      if(~timer)
           data_RPM <= temp[7:0];

endmodule
