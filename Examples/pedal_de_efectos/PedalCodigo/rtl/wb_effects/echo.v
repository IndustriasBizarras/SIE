
module echo(
	input clk,
	input reset,
	input enable,
	output start_tx,
	input [31:0]par_delay1,			//Delay before starting 2nd stream - number of samples
	input [31:0]par_delay2,
	input [7:0]data_adc,
	input data_rdy,

	//RAM interface
	output  reg       we_a,
	output  reg[7:0]  dat_a,
	input  	    [7:0] dat_b,
	output  reg[12:0] adr_a,
	output  reg[12:0] adr_b,

	//Audio outputs
	output reg [7:0]realt,
	output reg [7:0]delay1,
	output reg [7:0]delay2
    );

reg [15:0] cont1;
reg [7:0] delay1_reg0;		


initial begin
cont1=0;
adr_a=0;
adr_b=0;
end

reg flag;
assign start_tx=enable && data_rdy;

always @ (posedge start_tx) 
begin
			//Positive edge at new sample	
delay2<=0;


//		if (start_tx)			//Write realtime to ram and output
//		begin
			we_a<=1;
			realt<=data_adc;
			dat_a<=data_adc;
			adr_a<=adr_a+1;	
			cont1<=cont1+1;
//		end else 
//			we_a<=0;
		

	if (cont1<par_delay1) 			//Read delay1 from ram
	begin
		adr_b<=0;
			end else 
			begin
				if (enable) 
				begin
					delay1<=dat_b;
					adr_b<=adr_b+1;	
				end else begin
					 adr_b<=adr_b;		//whatever
					 end
			end
end


endmodule
