`timescale 1ns / 1ps

module reg_bank(clk, reset, en, we, wdBus, rdBus, address, reg0, reg1, reg2, reg3, reg4, regMT, error, status, max_lev, max_com, control);

  input clk, reset, en, we;
  
  input  [7:0]  wdBus;
  output [7:0]  rdBus;
  input  [4:0]  address;

  input  [31:0] reg0;
  input  [31:0] reg1;
  input  [31:0] reg2;
  input  [31:0] reg3;
  input  [31:0] reg4;
  input  [31:0] regMT;
  input  [16:0] error;
  input  [7:0]  status;
  output [15:0] max_com;
  output [7:0]  max_lev;
  output [7:0]  control;


  reg    [7:0]  reg_bank [31:0];
  reg    [7:0]  rdBus;

 

    // Read control    
    always @(posedge clk)
      if(reset) 
         rdBus = 8'h00;
      else begin
			rdBus = reg_bank[address];
      end

     //  Store Inputs
    always @(posedge clk)
     begin
      if(en) begin  
        reg_bank[0]  = reg0[7:0];
        reg_bank[1]  = reg0[15:8];
        reg_bank[2]  = reg0[23:16];
        reg_bank[3]  = reg0[31:24];

        reg_bank[4]  = reg1[7:0];
        reg_bank[5]  = reg1[15:8];
        reg_bank[6]  = reg1[23:16];
        reg_bank[7]  = reg1[31:24];

        reg_bank[8]  = reg2[7:0];
        reg_bank[9]  = reg2[15:8];
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

        reg_bank[22] = {4'b0, status};

//        reg_bank[23] = regMT[7:0];
//        reg_bank[24] = regMT[15:8];
//        reg_bank[25] = regMT[23:16];
//        reg_bank[26] = regMT[31:24];
      end
     end

     assign max_com[7:0]   = reg_bank[26];
     assign max_com[15:8]  = reg_bank[27];
     assign max_lev        = reg_bank[28];
     assign control        = reg_bank[29];

    // Write control    
    always @(negedge clk)
      if(we & en) begin
        case (address)  
          27: reg_bank[26] = wdBus;
          28: reg_bank[27] = wdBus; 
          29: reg_bank[28] = wdBus;
          30: reg_bank[29] = wdBus;
        endcase
      end

endmodule
