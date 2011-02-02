
// REG OFFSET 		1000h
//reg0(32bit)W		0h
//reg1(32bit)W		4h
//reg2(32bit)W		8h
//reg3(32bit)W		Ch
//reg4(32bit)W		10h
//error(16bit)R 	14h
//status(16bit)R	16h
//mt_rnd(32bit)R	18h
//max_lev(8bit)W 	1Ch
//control(8bit)W	1Dh
//max_com(16bit)W	1Eh


`timescale 1ns / 1ps
module ehw(clk, sram_data, addr, nwe, ncs, noe, reset, led, 
                irq_pin);
  
    parameter   B = (7);

    input       clk, addr, nwe, ncs, noe, reset;
    inout [B:0] sram_data;
    output      led;
    output      irq_pin;

    // synchronize signals                               
    reg    	    sncs, snwe;
    reg     [12:0]  buffer_addr; 
    reg     [B:0]   buffer_data; 
	 wire led;

    // bram-cpu interfaz
    reg             we;
    reg             w_st=0;
    reg     [B:0]   wdBus;
    reg     [B:0]   rdBus;
    wire    [12:0]  addr;
    reg     [7:0]   bae;


    // bram-evalfit interfaz
    wire    we_eval, en_ev; 
    wire    [63:0] ev_do;
    wire    [63:0] ev_di;
    wire    [63:0] ev_do_aux;
    wire    [63:0] ev_di_aux;
	 
    // Interconnection
    wire   [31:0] mt_rnd;
    wire   [31:0] reg0;
    wire   [31:0] reg1;
    wire   [31:0] reg2;
    wire   [31:0] reg3;
    wire   [31:0] reg4;
    wire   [15:0] status;
	 wire   [15:0] status_aux;
    wire   [15:0] error;
    wire   [8:0]  evalfit_addr;

    wire   en_fit;
    wire   [15:0] max_com;
    wire   [3:0]  max_lev;
    wire   [7:0]  control;

	reg    [7:0]  reg_bank [31:0];
	wire 	 enReg;
	wire 	 [4:0] address; 

// Test : LED blinking
    reg     [25:0]  counter;
    always @(posedge clk) begin
        if (~reset)
            counter <= {25{1'b0}};
        else
            counter <= counter + 1;
    end 
    assign led = counter[24];
    
// Data Bus direction control
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
    if(~reset) {w_st, we, wdBus} <= 0;
      else begin
        wdBus <= buffer_data;
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


 // Address Decoder
 // We have 2 memory blocks 1: 512 x 64 bits memory 32kb = 4kB  0000 - 0FFF  buffer_addr[12] = 0
 //                         2: Register Bank                    1000 - 101F  buffer_addr[12] = 1

 // SIE has an eight bits data bus, this module generate the required signals to create a 64 bits word.
  always @(buffer_addr)
   begin
     if(~buffer_addr[12]) begin
        case (buffer_addr[2:0])
          0: bae <= 8'h01;
          1: bae <= 8'h02;
          2: bae <= 8'h04;
          3: bae <= 8'h08;
          4: bae <= 8'h10;
          5: bae <= 8'h20;
          6: bae <= 8'h40;
          7: bae <= 8'h80;
        endcase
     end
     else
       bae <= 8'h00;
   end
	wire en1, en2;	// enable memory signals
	assign en0 = bae[0] | bae[1] | bae[2] | bae[3];
	assign en1 = bae[4] | bae[5] | bae[6] | bae[7];

	reg[31:0] DIA_Aux;
	always @ (posedge clk) begin
		if (bae[0]) DIA_Aux[7:0] = wdBus[7:0];
		if (bae[1]) DIA_Aux[15:8] = wdBus[7:0];
		if (bae[2]) DIA_Aux[23:16] = wdBus[7:0];
		if (bae[3]) DIA_Aux[31:24] = wdBus[7:0];
		if (bae[4]) DIA_Aux[7:0] = wdBus[7:0];
		if (bae[5]) DIA_Aux[15:8] = wdBus[7:0];
		if (bae[6]) DIA_Aux[23:16] = wdBus[7:0];
		if (bae[7]) DIA_Aux[31:24] = wdBus[7:0];		
	end

	reg [2:0] state, nextstate;	//FSM for write in 32bit mode to memory
	wire we0, we1;
	wire nreset;
	assign nreset = ~reset;
	parameter S0 = 3'b000;
	parameter S1 = 3'b001;
	parameter S2 = 3'b010;
	
	always @ (posedge clk, posedge nreset)
	if (nreset) state <= S0;
	else state <= nextstate;
	// next state logic
	always@(*)
		case (state)
		S0:if (bae[3]&we) nextstate = S1;
			else 
				if (bae[7]&we) nextstate = S2;
				else	nextstate = S0;
		S1: nextstate = S0;
		S2: nextstate = S0;
		default: nextstate = S0;
		endcase
	// output logic
	assign we0 = (state == S1);
	assign we1 = (state == S2);

// Read control    
	reg [7:0] 	MemDOA;
	wire [63:0] DOA_Aux;
	
    always @(posedge clk)
      if(~reset)begin 
         rdBus = 8'h00;
			end
      else begin
			if(enReg)
				rdBus = reg_bank[address];
				else
					rdBus = MemDOA[7:0];
      end
// memory output mux 	
	always @(buffer_addr[2:0])
		case (buffer_addr[2:0])
			0 : MemDOA = DOA_Aux[7:0];
			1 : MemDOA = DOA_Aux[15:8]; 
			2 : MemDOA = DOA_Aux[23:16];
			3 : MemDOA = DOA_Aux[31:24]; 
			4 : MemDOA = DOA_Aux[39:32]; 
			5 : MemDOA = DOA_Aux[47:40]; 
			6 : MemDOA = DOA_Aux[55:48]; 
			7 : MemDOA = DOA_Aux[63:56]; 
			default: MemDOA = 8'h00;
		endcase
		
//  Store Inputs
    always @(posedge clk)
     begin
      if(enReg) begin
			reg_bank[0] = reg0[7:0];
			reg_bank[1] = reg0[15:8];
			reg_bank[2] = reg0[23:16];
			reg_bank[3] = reg0[31:24];
			reg_bank[4] = reg1[7:0];
			reg_bank[5] = reg1[15:8];
			reg_bank[6] = reg1[23:16];
			reg_bank[7] = reg1[31:24];
			reg_bank[8] = reg2[7:0];
			reg_bank[9] = reg2[15:8];
			reg_bank[10] = reg2[23:16];
			reg_bank[11] = reg2[31:24];
			reg_bank[12] = reg3[7:0];
			reg_bank[13] = reg3[15:8];
			reg_bank[14] = reg3[23:16];
			reg_bank[15] = reg3[31:24];
			reg_bank[16] = reg4[7:0];
			reg_bank[17] = reg4[15:8];
			reg_bank[18] = reg4[23:16];
			reg_bank[19] = reg4[31:24];
			reg_bank[20] = error[7:0];
			reg_bank[21] = error[15:8];
			reg_bank[22] = status[7:0];
			reg_bank[23] = status[15:8];
			reg_bank[24] = mt_rnd[7:0];
			reg_bank[25] = mt_rnd[15:8];
			reg_bank[26] = mt_rnd[23:16];
			reg_bank[27] = mt_rnd[31:24];
      end
     end

	assign 	address[4:0] = buffer_addr[4:0];
	assign 	enReg = buffer_addr[12];
//	assign   reg0[7:0] 	= reg_bank[0];
//	assign   reg0[15:8] 	= reg_bank[1];
//	assign   reg0[23:16] = reg_bank[2];
//	assign   reg0[31:24] = reg_bank[3]; 
//	assign   reg1[7:0] 	= reg_bank[4]; 
//	assign   reg1[15:8] 	= reg_bank[5];
//	assign   reg1[23:16] = reg_bank[6];
//	assign   reg1[31:24] = reg_bank[7];
//	assign   reg2[7:0] 	= reg_bank[8]; 
//	assign   reg2[15:8] 	= reg_bank[9];
//	assign   reg2[23:16] = reg_bank[10];
//	assign   reg2[31:24] = reg_bank[11];
//	assign   reg3[7:0] 	= reg_bank[12];
//	assign   reg3[15:8] 	= reg_bank[13];
//	assign   reg3[23:16] = reg_bank[14];
//	assign   reg3[31:24] = reg_bank[15];
//	assign   reg4[7:0] 	= reg_bank[16];
//	assign   reg4[15:8] 	= reg_bank[17];
//	assign   reg4[23:16] = reg_bank[18]; 
//	assign   reg4[31:24] = reg_bank[19];
	assign 	max_lev[3:0] = reg_bank[28][3:0];
	assign 	control[7:0] = reg_bank[29];
	assign 	max_com[7:0] = reg_bank[30];
	assign 	max_com[15:8] = reg_bank[31];
	// Write control    
	always @(negedge clk)
	if(we & enReg) begin
	  case (address)
//		 0: reg_bank[0] = wdBus;
//		 1: reg_bank[1] = wdBus;
//		 2: reg_bank[2] = wdBus;
//		 3: reg_bank[3] = wdBus;
//		 4: reg_bank[4] = wdBus;
//		 5: reg_bank[5] = wdBus;
//		 6: reg_bank[6] = wdBus;
//		 7: reg_bank[7] = wdBus;
//		 8: reg_bank[8] = wdBus;
//		 9: reg_bank[9] = wdBus;
//		 10: reg_bank[10] = wdBus;
//		 11: reg_bank[11] = wdBus;
//		 12: reg_bank[12] = wdBus;
//		 13: reg_bank[13] = wdBus;
//		 14: reg_bank[14] = wdBus;
//		 15: reg_bank[15] = wdBus;
//		 16: reg_bank[16] = wdBus;
//		 17: reg_bank[17] = wdBus;
//		 18: reg_bank[18] = wdBus;
//		 19: reg_bank[19] = wdBus;
		 28: reg_bank[28] = wdBus;
		 29: reg_bank[29] = wdBus;
		 30: reg_bank[30] = wdBus;
		 31: reg_bank[31] = wdBus;
	  endcase
	end	  
assign irq_pin = 0;
//assign ev_do_aux = {ev_do[7:0], ev_do[15:8], ev_do[23:16], ev_do[31:24], ev_do[39:32], ev_do[47:40], ev_do[55:48], ev_do[63:56]};
//assign ev_di = {ev_di_aux[7:0], ev_di_aux[15:8], ev_di_aux[23:16], ev_di_aux[31:24], ev_di_aux[39:32], ev_di_aux[47:40], ev_di_aux[55:48], ev_di_aux[63:56]};
assign ev_do_aux[63:32] = ev_do[31:0];
assign ev_do_aux[31:16] = ev_do[47:32];
assign ev_do_aux[15:0]  = ev_do[63:48];

assign ev_di[63:32] = ev_di_aux[31:0];		//Endianess adjust for 32-bit level data
assign ev_di[31:16] = ev_di_aux[47:32];	//endianess adjust for 16-bit LUT
assign ev_di[7:0]  = ev_di_aux[63:56];		//endianess adjust for 8-bit VARS
assign ev_di[15:8]  = ev_di_aux[55:48];	//endianess adjust for 8-bit VARS


assign status[14:0] = status_aux[14:0];

RAMB16_S36_S36 #(.INIT_00(256'hABCDEF00_00000000_00000000_00000000_00000000_00000000_00000000_76543210) )
					mem0 	( .CLKA(clk), .ENA(en0), 	.SSRA(1'b0), .ADDRA(buffer_addr[11:3]), .WEA(we0),     .DIA(DIA_Aux[31:0]), 	.DIPA(1'b0),	.DOA(DOA_Aux[31:0]),
                  .CLKB(clk), .ENB(en_ev),  .SSRB(1'b0), .ADDRB(evalfit_addr),      .WEB(we_eval), .DIB(ev_do_aux[31:0]), 	  	.DIPB(1'b0), 	.DOB(ev_di_aux[31:0]));  
						
RAMB16_S36_S36 #(.INIT_00(256'hCE5A4000_00000000_00000000_00000000_00000000_00000000_00000000_78111300) )
					mem1( .CLKA(clk), .ENA(en1), 	.SSRA(1'b0), .ADDRA(buffer_addr[11:3]), .WEA(we1),     .DIA(DIA_Aux[31:0]), 	.DIPA(0'b0),	.DOA(DOA_Aux[63:32]),
                  .CLKB(clk), .ENB(en_ev),  .SSRB(1'b0), .ADDRB(evalfit_addr),      .WEB(we_eval), .DIB(ev_do_aux[63:32]), 	.DIPB(0'b0), 	.DOB(ev_di_aux[63:32]));

// evalfit_peripheral
evalfit_peripheral evalfit( .clk(clk), .reset(control[7]), .habilita(control[6]), .maxcombs(max_com), .nivel_max(max_lev),
                            .peripheral_mem_in(ev_di), .peripheral_mem_en(en_ev), .peripheral_mem_out(ev_do), .peripheral_mem_we(we_eval), 
                            .peripheral_mem_addr(evalfit_addr), .evalfit3_estado(status_aux[15:0]), .errores(error), 
                            .fin_ack(status[15]), .reg0_s(reg0), .reg1_s(reg1), .reg2_s(reg2), .reg3_s(reg3), .reg4_s(reg4));

// MersenneTwister
 mt_mem random( .clk(clk), .ena(1'b1), .resetn(reset), .random(mt_rnd));

endmodule

