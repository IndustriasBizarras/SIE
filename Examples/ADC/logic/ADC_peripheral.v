`timescale 1ns / 1ps
module ADC_peripheral(  clk, reset, cs, ADC_EOC, ADC_CS, ADC_CSTART,
                        ADC_SCLK,  ADC_SDIN, ADC_SDOUT, 
                        addr, rdBus, wrBus, we);
                                    
    input   clk, reset, ADC_EOC, cs, we;
    input   [10:0] addr;
    input   [7:0] wrBus;
    output  ADC_CS, ADC_CSTART, ADC_SCLK;
    output  [7:0] rdBus;
    inout   ADC_SDIN, ADC_SDOUT; 

    reg  ADC_CS=1;
    
    //RAMB registers
    reg  [7:0]   rdBus;
    wire [7:0]   rdBus1;    
    reg  [7:0]   wrBus2;
    reg  [10:0]  addr2;
    reg  we1=0, we2=0;
    wire we;
       
    //Control registers
    reg  loadB=0;
    reg  initB=0;
    reg  fullB=0;
    reg  rstStart=0;
    reg  [2:0]   w_st0=0;
    reg  [2:0]   w_st1=0;
    reg  [2:0]   w_st2=0;
      
    // Confiuration registers
    reg [1:0]  CMD_SW=0;      // Channel offset selection
    reg        CMD_START=0;   // START sampling data
    reg        CMD_TYP=0;     // Command type
    reg [3:0]  CMD_ADC=0;     // ADC command    
    reg [7:0]  CLKDIV = 0;    // Clock divisor for SPI
    reg [9:0]  SIZEB=0;       // Buffer size (sampling data len.)
        //TEMPS
    reg [9:0]  SIZEB1=0;      // Temporal for buffer size
    reg [9:0]  SIZEB2=0;      // Temporal for buffer size
        wire[9:0] subSIZEB;       // Temporal for subtraction SIZEB1-SIZEB2
    reg [2:0]  CMD_OFFSET=0;  // Channel offset counter MOD8
    wire[2:0]  CMD_OFFSETt;   // Channel offset to use
    wire[3:0]  CMD_ADCt;      // Temporal for channel offset  
     
    assign ADC_CSTART = 1'b1;
    
    // Dual-port RAM instatiation
    RAMB16_S9_S9 ba0(
            .DOA(rdBus1),         // Port A 8-bit Data Output
            .DOB(),               // Port B 8-bit Data Output
            .DOPA(),              // Port A 1-bit Parity Output
            .DOPB(),              // Port B 1-bit Parity Output
            .ADDRA(addr[10:0]),   // Port A 11-bit Address Input
            .ADDRB(addr2[10:0]),  // Port B 11-bit Address Input
            .CLKA(~clk),          // Port A Clock
            .CLKB(~clk),          // Port B Clock
            .DIA(wrBus[7:0]),     // Port A 8-bit Data Input
            .DIB(wrBus2[7:0]),    // Port B 8-bit Data Input
            .DIPA(1'b0),          // Port A 1-bit parity Input
            .DIPB(1'b0),          // Port-B 1-bit parity Input
            .ENA(1'b1),           // Port A RAM Enable Input
            .ENB(1'b1),           // Port B RAM Enable Input
            .SSRA(1'b0),          // Port A Synchronous Set/Reset Input
            .SSRB(1'b0),          // Port B Synchronous Set/Reset Input
            .WEA(we1),            // Port A Write Enable Input
            .WEB(we2) );          // Port B Write Enable Input 

    //SPI registers
    reg SPI_wr = 0;
    reg ADC_SCLK_buffer = 0;
    reg ADC_SDIN_buffer = 0;
    reg busy = 0, load_in = 0;
    reg pulse = 0, clkdiv_en  = 0;
    wire fallingSCLK;

    reg [3:0] in_buffer=0;
    reg [9:0] out_buffer;
    reg [7:0] clkcount = 0;
    reg [5:0] pulsecount = 0;
    
    assign fallingSCLK = pulsecount[0];

    // SPI Control
    always @(posedge clk)
    if(reset) begin
        {w_st1, pulsecount, clkdiv_en, busy} <= 0;
    end else begin
        case (w_st1)
             0: begin  
                    if(SPI_wr) begin
                        clkdiv_en  <= 1;
                        load_in <= 1;
                        w_st1 <= 1; busy <= 1;
                    end
                end
             1: begin
                     load_in <= 0;
                     if(pulse)  
                         pulsecount <= pulsecount + 1;   
                     else if (pulsecount > 55) begin 
                          clkdiv_en  <= 0; busy <= 0; 
                          w_st1 <= 0; pulsecount <= 0; 
                     end
                end
          endcase
     end
    
    // SPI Clock Generator
    always@(posedge clk)
        if (clkdiv_en) begin
           if(clkcount < CLKDIV) begin
                   clkcount <= clkcount + 1; pulse <=0;
           end else begin
                clkcount <= 0; pulse <=1;
                if((pulsecount>0) && (pulsecount < 21)) 
                    ADC_SCLK_buffer <= ~ADC_SCLK_buffer;
           end
        end else  begin
            ADC_SCLK_buffer <= 0; pulse <=0;
        end
    
    // SPI Receptor
    always@(posedge clk)
    begin
        if((fallingSCLK & pulse) && (pulsecount < 21)) begin
            out_buffer <= out_buffer << 1;
            out_buffer[0] <= ADC_SDOUT;
        end
    end
    
    // SPI Transmitter
    always@(posedge clk)
    begin
        if(load_in) in_buffer <= CMD_ADCt[3:0]; 
        if(!fallingSCLK & pulse) begin
            ADC_SDIN_buffer <= in_buffer[3];
            in_buffer <= in_buffer << 1;
        end
    end

    assign ADC_SCLK = ADC_SCLK_buffer;
    assign ADC_SDIN = ADC_SDIN_buffer;    

    /**************************************************************************/

    // REGISTER BANK:   Write control
    always @(negedge clk)
    begin
        if(reset) 
            {CMD_START, CMD_TYP,CMD_ADC,SIZEB,we1} <= 0;
        else if(we & cs) begin
            case (addr)   
                    0: begin CLKDIV[7:0]    <= wrBus;      end
                    1: begin SIZEB[7:0]     <= wrBus;      end
                    2: begin SIZEB[9:8]     <= wrBus[1:0]; end            
                    3: begin CMD_SW[1:0]    <= wrBus[7:6];
                             CMD_START      <= wrBus[5];
                             CMD_TYP        <= wrBus[4];
                             CMD_ADC[3:0]   <= wrBus[3:0]; end
              default: begin we1 <= 1; end     
            endcase 
        end 
        else begin 
            we1 <= 0; end

        if(fullB | rstStart) CMD_START <= 0; 
    end            

    // REGISTER BANK:   Read control    
    always @(posedge clk)
        if(reset) 
            {rdBus} <= 0;
        else begin
            case (addr)   
                  0: begin rdBus  <= CLKDIV;       end
                  1: begin rdBus  <= SIZEB[7:0];   end
                  2: begin rdBus  <= SIZEB[9:8];   end            
                  3: begin rdBus  <= {CMD_SW,CMD_START,CMD_TYP,CMD_ADC};end
            default: begin rdBus  <= rdBus1;       end
            endcase 
        end
 
    // CONTROL
    always @(posedge clk)
        if(reset) begin
            {w_st0, SPI_wr, loadB, initB} <= 0;
            ADC_CS <=1;
        end
        else begin
            case (w_st0)
                 0: begin 
                        rstStart <= 0; 
                        if(CMD_START) begin
                            ADC_CS <=0; 
                            SPI_wr <= 1;                            
                            w_st0 <=1;    
                        end
                    end                       
                 1: begin SPI_wr <= 0; w_st0 <=2; end
                 2: begin
                        if(!busy & ADC_EOC) begin 
                            ADC_CS <=1;
                            if(CMD_TYP) begin
                                rstStart <= 1; 
                                w_st0<= 0; 
                            end
                            else begin 
                                initB<=1;
                                w_st0<= 3; 
                            end                     
                        end
                    end              
                 3: begin loadB <= 1; w_st0<= 4; end              
                 4: begin loadB <= 0; initB<=0; w_st0<= 0; end
            endcase            
        end
    
    // Reception Buffer        
    always @(posedge clk)
    if(reset) 
        {we2, w_st2, fullB, SIZEB1, SIZEB2} <= 0;
    else begin
        case (w_st2)
             0: begin 
                    fullB <= 0; 
                    if(initB) begin 
                        w_st2 <= 1; 
                        SIZEB1<=SIZEB; 
                        SIZEB2<=SIZEB; 
                    end
                end 
             1: begin 
                    if(loadB) begin 
                        // If buffer full set fullB flag by a clock cicle
                        if(SIZEB2>0) begin
                            w_st2 <= 2; end
                        else begin
                            fullB <= 1;
                            w_st2 <= 0;                            
                        end
                    end
                end
             2: begin 
                    //Write data on BRAM  (LOW)
                    wrBus2[7:0] <= out_buffer[7:0]; 
                    addr2 <= {subSIZEB,1'b0};
                    we2 <= 1; w_st2 <= 3; 
                end
             3: begin we2 <= 0; w_st2 <= 4;  end    
             4: begin 
                    //Write data on BRAM  (HI)
                    wrBus2[7:0] <= out_buffer[9:8]; 
                    addr2 <= {subSIZEB,1'b1}; 
                    we2 <= 1; w_st2 <= 5;
                end
             5: begin 
                    we2 <= 0; w_st2 <= 1; SIZEB2 <= SIZEB2-1;
                end         
        endcase
      end     
    
    assign subSIZEB = SIZEB1-SIZEB2;
    
    // ADC channel offset, counter MOD8
    always @(posedge clk)
        if(fullB | reset) 
            CMD_OFFSET <= 0;
        else if(loadB) begin  
            CMD_OFFSET <= CMD_OFFSET + 1; 
        end
        
    // MUX to select the channel offset     
    assign CMD_OFFSETt = CMD_SW[1]? (CMD_SW[0]? CMD_OFFSET[2:0]    : 
                                                CMD_OFFSET[1:0]    )
                                  : (CMD_SW[0]? CMD_OFFSET[0]      : 
                                                3'b0               );
                                                
    // Add ADC command and offset                                                
    assign CMD_ADCt = CMD_ADC + CMD_OFFSETt;          
endmodule
