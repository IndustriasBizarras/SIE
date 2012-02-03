`timescale 1ns / 1ps
module Moto(
//Senales de proposito general
clk, 
sram_data, 
addr, 
nwe, 
ncs,
noe,
reset, 
led, 
//OD1,OD2,OD3,

//Senales del ADC
ADC_EOC,
ADC_SCLK, 
ADC_SDIN, 
ADC_SDOUT,
ADC_CS,
ADC_CSTART,
irq_pin,

//Senales para teclas
PB_1,PB_2,PB_3,PB_4,PB_5,
IND1,IND2,IND3,IND4,IND5,IND6

);
  
    parameter   B = (7);
	//output reg  OD1,OD2,OD3;
    input       clk, addr, nwe, ncs, noe, reset, ADC_EOC;
    inout [B:0] sram_data;
    output      led, ADC_CS, ADC_CSTART, ADC_SCLK;
    inout 	ADC_SDIN, ADC_SDOUT;
    output       irq_pin;

	//Senales nuestras
	input PB_1,PB_2,PB_3,PB_4,PB_5,IND1,IND2,IND3,IND4,IND5,IND6;


    // Internal conection
    //reg    led;

    // synchronize signals                               
    reg    		sncs, snwe;
    reg     [12:0]  	buffer_addr; 
    reg     [B:0]	buffer_data;   

    // bram interfaz signals
    reg    	    		we;
    reg    				w_st=0;
    reg     [B:0]   	wrBus;
    wire    [B:0]   	rdBus;
    
    // interfaz fpga signals    
    wire    [12:0]  addr;
    reg     [25:0]  counter;


    // Peripherals control
    wire     [3:0]   csN;
    wire     [7:0]   rdBus0, rdBus1, rdBus2, rdBus3;
    //wire irq_tmp;
     
    assign csN = buffer_addr[12]? (buffer_addr[11]? 4'b1000: 4'b0100)
                                : (buffer_addr[11]? 4'b0010: 4'b0001);

    assign rdBus = buffer_addr[12]? (buffer_addr[11]? rdBus3://Direccion 0x2600
                                                      rdBus2)//Direccion 0x1800
                                  : (buffer_addr[11]? rdBus1://Direccion 0x1000 
                                                      rdBus0);//Direccion 0x0000
    // interefaz signals assignments
    wire   T = ~noe | ncs;
    assign sram_data = T?8'bZ:rdBus;
    //assign irq_pin=irq_tmp;
 
     // Test : LED blinking
    /*always @(posedge clk)
    begin
        if (~reset)
			begin
            counter <= {25{1'b0}};
			led <=0;
			//OD1<=0;
			//OD2<=0;
			//OD3<=0;			
			end
        else
		case(csN)
		4'b0001: 
			begin
			counter <= counter + 1;
            led <= counter[25];
			OD1<=counter[25];
			OD2<=counter[16];
			OD3<=counter[15];		
			end
		4'b0010:
			begin
			led<= ~PB_1|~PB_2|~PB_3|~PB_4|~PB_5;
			//|IND1|IND2|IND3|IND4|IND5;
			end
		4'b0100:
			begin
			led<=IND6;
			end
		4'b1000: 
			begin
			led<=0;
			end
		default:
			begin
            counter <= {25{1'b0}};
			led <=0;
			//OD1<=0;
			//OD2<=0;
			//OD3<=0;
			end
		endcase
    end */
    
	

    // synchronize assignment
    always  @(negedge clk)
    begin
        sncs   <= ncs;
        snwe   <= nwe;
        buffer_data <= sram_data;
        buffer_addr <= addr;
    end

    // write access cpu to bram
    always @(posedge clk)
    if(~reset) {w_st, we, wrBus} <= 0;
      else begin
        wrBus <= buffer_data;
        case (w_st)
          0: begin
              we <= 0;
              if(sncs | snwe) w_st <= 1;
          end
          1: begin
            if(~(sncs | snwe)) begin
              we    <= 1;
              w_st  <= 0;
            end	
            else we <= 0;
          end
        endcase
      end


					      
    // Peripheral instantiation
    ADC_peripheral  P1( 
                        .clk(clk), 
                        .reset(~reset), 
                        .cs(csN[0]),
                        .ADC_EOC(ADC_EOC), 
                        .ADC_CS(ADC_CS), 
                        .ADC_CSTART(ADC_CSTART),
				        .ADC_SCLK(ADC_SCLK), 
				        .ADC_SDIN(ADC_SDIN), 
				        .ADC_SDOUT(ADC_SDOUT), 
				        .addr(buffer_addr[10:0]),
				        .rdBus(rdBus0), 
				        .wrBus(wrBus), 
				        .we(we));	

// Instanciamiento Teclas
   deb deb 
	(
   		.PB_1(PB_1), 
   	 	.PB_2(PB_2), 
    	.PB_3(PB_3), 
    	.PB_4(PB_4), 
    	.PB_5(PB_5), 
    	.IND1(IND1), 
    	.IND2(IND2), 
    	.IND3(IND3), 
    	.IND4(IND4), 
    	.IND5(IND5), 
    	.nCS(csN[1]),
    	.clk(clk), 
    	.reset(reset), 
    	.data_tecla(rdBus1), 
    	.led(led), 
    	.irq_pin(irq_pin)
    );

//Instanciamiento RPM

 RPM RPM (
    .pulse(IND6), 
    .clk(clk), 
    .reset(reset), 
    .data_RPM(rdBus2)
    );

       
endmodule

