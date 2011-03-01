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
    output reg ADC_clk,
    output   busy
);

reg [9:0]in_buffer;
reg [15:0 ]cont;
reg [3:0] A;
reg buffer_rdy;
reg [3:0] command;
reg [3:0] comd_buffer;
reg clk_en;
reg [7:0] contadc;
reg [3:0] out_buffer;
reg [11:0] contpulse; 
reg start;
reg [7:0] data_out_temp;
reg [3:0] idle;

initial begin
command=0;
comd_buffer=0;
in_buffer=0;
cont=0;
A=0;
buffer_rdy=0;
data_rdy=0;
status=0;
cs=1;
data_adc=0;
data_out=0;
cstart=1;
clk_en=0;
ADC_clk=0;
contadc=0;
contpulse=0;
start=1;
idle=0;
//busy=0;
end

assign busy=control[0];
//Divisor del clk enable con la frecuencia en la que es requerido los datos para el pedal
always @ (posedge clk) begin

	if (control==8'h01) begin		//inicia la conversion, dato enviado por el procesador
		//busy<=clk_en;		
		if(cont<25'd6250)  			//4KHz   6250
			cont<=cont+1;
		else begin
			cont<=0;
			clk_en<=~clk_en;
			contpulse<=0;
		end
	end else begin 
		{cont, clk_en} <=0;    //mientras no se inicie la conversion, el clock que habilita la transmision y recepcion es cero
	end  

//Divisor del clock para la transmision de datos del integrado
	if (clk_en) begin
						if (contadc<8'd50) begin	//500KHz   50
								contadc<=contadc+1;
						end else begin 
									if(~ADC_clk)contpulse<=contpulse +1;	 //contpulse, det el numero de pulsos
									contadc<=0;
									ADC_clk<=~ADC_clk;		//clock que se le envia al integrado
							end
					end else
						{contadc, ADC_clk, contpulse} <= 0;

//Maquina de control para el envio y res
if (reset)begin
	{contadc, cont, A, in_buffer, data_rdy, data_adc, data_out, status, ADC_clk,clk_en, contpulse} <=0;
	cs<=1;
end else begin
if (status==8'h00 && control==8'h01 && clk_en && contpulse<10) begin
	A<=1;
	if (start) begin
	command <= 8'h09;
	end else begin
		command<=channel;
		end
	end else command <= command;
end

	case (A)		
	    4'd0: begin
			status<=8'h00;		//Idle
		  end
	    4'd1: begin
				A<=2;
				cs<=0;
				status<=8'h02;		//Converting
				start<=0;
				buffer_rdy<=0;
		  end
	    4'd2: begin
			if (status==8'h02) begin
				out_buffer<=command[3:0];
				in_buffer<=0;
				end
			if(~ADC_clk && contadc>8'd25) begin	//ojo es 25 para frecuencia de 4KHz
				status<=8'h03;			//sending data				
				data_out<=out_buffer[3];	//transmision de datos al integrado
				in_buffer[0]<=data_in;		//recibe los datos del integrado
				end else if (contadc==8'd50 && contpulse<10)begin	//hacer el cambio en el limite del contador50
				in_buffer <=  in_buffer <<1;
				out_buffer <= out_buffer <<1;	
				end
			if(contpulse>10) A<=3;
			end
	    4'd3: begin
			if (~eoc)begin
				//busy<=~eoc;
				A<=4; end
					else A<=3;
		  end
	    4'd4: begin
			if (eoc) begin
				A<=5;
				status<=8'h05;			//Conversion done
				buffer_rdy<=1;
				data_out_temp<=in_buffer[9:2];
				
				end else status<=8'h04;		//Waiting for conversion	
		  end
	    4'd5: begin
			cs<=1;
			A<=0;
			status<=8'h00;
		  end
	endcase
// --------------- Data Transmission ------------

if (buffer_rdy) 
	data_rdy<=1;
		else data_rdy<=0;


if (buffer_rdy && start_tx) begin
//	idle<=idle+1;
	data_adc<=data_out_temp;
	data_rdy<=1;				//Aca con esta linea hay un loop, en echo start_tx=1 cuando data_rdy=1	
		end else begin
			idle<=0;
		end


end
endmodule
