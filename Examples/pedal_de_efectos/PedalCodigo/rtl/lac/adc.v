module adc (

    input clk,
    input reset,
    input eoc,
    input data_in,
    input start_tx,
    input [3:0]control,		//01 start conversion
    input [3:0]channel,

    output reg  data_rdy,
    output reg  [7:0]status,		//00 para idle - 02 converting - 03 command sent - 04 awaiting conversion - 05 conv done
    output reg cs,
    output reg [7:0] data_adc,
    output reg data_out,
    output reg cstart,
    output reg ADC_clk 
);

reg [7:0 ]in_buffer;
reg [24:0 ]cont;
reg [3:0] A;
reg buffer_rdy;
reg [3:0] command;
reg start;
reg clk_adc;

//assign ADC_clk = clk_adc;

initial begin
command=0;
in_buffer=0;
cont=0;
A=0;
buffer_rdy=0;
data_rdy=0;
status=0;
cs=1;
data_adc=0;
data_out=0;
start=0;
clk_adc=0;
cstart=1;

end


always @ (posedge clk)begin

//clk division  Frecuencia de muestreo de la señal de entrada
	if(cont<25'd125000)  			//4KHz    125000
		cont<=cont+1;
	else begin
		cont<=0;
		clk_adc<=~clk_adc;
		ADC_clk <= clk_adc;
		end
end

always @ (posedge clk_adc) begin

//-------------------Conversión --------------------------// Hay que cambiar control cuando cambie status a 02
if (~start && status==8'h00) begin			//inicialización del ADC
		A<=1;
		command<=4'h9;
		start<=1;
		cstart<=1;
		end else if (reset) begin		//reset del periferico
				A<=0;
				in_buffer<=0;
				cs<=1;
				data_rdy<=0;
				data_adc<=0;
				data_out<=0;
				end else if (status==8'h00 && control==8'h01) begin
						A<=1;
						command<=channel;
						end else command<=command;
	case (A)		
	    4'd0: begin
			status<=8'h00;		//Idle
		  end
	    4'd1: begin
			A<=2;
			cs<=0;
			status<=8'h02;		//Converting
		  end
	    4'd2: begin
			data_out<=command[3];
			in_buffer[7]<=data_in;
			A<=3;
		  end
	    4'd3: begin
			data_out<=command[2];
			in_buffer[6]<=data_in;
			A<=4;
		  end
	    4'd4: begin
			data_out<=command[1];
			in_buffer[5]<=data_in;
			A<=5;
		  end
	    4'd5: begin
			data_out<=command[0];
			in_buffer[4]<=data_in;
			buffer_rdy<=0;
			A<=6;
		  end
	    4'd6: begin
			in_buffer[3]<=data_in;
			status<=8'h03;				//Command Sent
			A<=7;
		  end
	    4'd7: begin
			in_buffer[2]<=data_in;
			A<=8;
		  end
	    4'd8: begin
			in_buffer[1]<=data_in;
			A<=9;
		  end
	    4'd9: begin
			in_buffer[0]<=data_in;
			A<=10;
		  end
	    4'd10: begin
			if (~eoc)
				A<=11;
					else A<=10;
		  end
	    4'd11: begin
			if (eoc) begin
				A<=12;
				status<=8'h05;			//Conversion done
				buffer_rdy<=1;
				end else status<=8'h04;		//Waiting for conversion	
		  end
	    4'd12: begin
			cs<=1;
			A<=0;
			status<=8'h00;
		  end
	endcase
// --------------- Data Transmission ------------


if (buffer_rdy) data_rdy<=1;
	else data_rdy<=0;

if (data_rdy && start_tx) begin
	data_adc<=in_buffer;
	buffer_rdy<=0;
		end else data_adc<=0;
end

 	
endmodule
