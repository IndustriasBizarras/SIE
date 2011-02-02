`timescale 1ns / 1ps
module ADC(clk, sram_data, addr, nwe, ncs, noe, reset, led, ADC_EOC,
                ADC_SCLK, ADC_SDIN, ADC_SDOUT, ADC_CS, ADC_CSTART, irq_pin, OD1, OD2, OD3);
  
    parameter   B = (7);

    input       clk, addr, nwe, ncs, noe, reset, ADC_EOC;
    inout [B:0] sram_data;
    output      led, ADC_CS, ADC_CSTART, ADC_SCLK;
    output      OD1, OD2, OD3;
    inout 	ADC_SDIN, ADC_SDOUT;
    input       irq_pin;


    // Internal conection
    reg    led;
    reg    OD1, OD2, OD3;

    // synchronize signals                               
    reg    		    sncs, snwe;
    reg     [12:0]  buffer_addr; 
    reg     [B:0]	buffer_data;   

    // bram interfaz signals
    reg    		    we;
    reg    		    w_st=0;
    reg     [B:0]   wrBus;
    wire    [B:0]   rdBus;
    
    // interfaz fpga signals    
    wire    [12:0]  addr;


    reg     [25:0]  counter;
 
     // Test : LED blinking
    always @(posedge clk) begin
        if (~reset)
            counter <= {25{1'b0}};
        else
            counter <= counter + 1;
            led <= counter[25];
            OD1 <= counter[25];
            OD2 <= counter[16];
            OD3 <= counter[15];

    end 
    
    // interefaz signals assignments
    wire   T = ~noe | ncs;
    assign sram_data = T?8'bZ:rdBus;

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

    // Peripherals control
    wire     [3:0]   csN;
    wire     [7:0]   rdBus0, rdBus1, rdBus2, rdBus3;
      
    assign csN = buffer_addr[12]? (buffer_addr[11]? 4'b1000: 
                                                    4'b0100)
                                : (buffer_addr[11]? 4'b0010: 
                                                    4'b0001);

    assign rdBus = buffer_addr[12]? (buffer_addr[11]? rdBus3: 
                                                      rdBus2)
                                  : (buffer_addr[11]? rdBus1: 
                                                      rdBus0);
					      
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
endmodule

