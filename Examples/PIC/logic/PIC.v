module PIC   ( DI, DO, addr, 
               ISRC_LP, nIRQ,
               CS, nwe, noe,
               MCLK,
               RESET); 

input  [7:0] DI;
output [7:0] DO;
input  [6:0] addr;
input  [6:0] ISRC_LP;
output nIRQ;
input  CS, nwe, noe;
input  MCLK, RESET;

//------------------------------
// registros internos


reg nIRQ;

reg [7:0] DO;  //Registro de salida.


reg [7:0] IRQEnable;                    //Interrupt Mask
reg	   IRQSoft;                     //Soft interrupt flag


wire [7:0] ISRCF, IREG_LP;

assign  ISRCF   = {ISRC_LP, IRQSoft};    //
assign  IREG_LP = ( ISRCF  & IRQEnable); //


always @(posedge MCLK)
  begin
    nIRQ <= ~(|IREG_LP);
  end


always @(CS or addr or noe or IREG_LP or ISRCF or IRQEnable)
begin
      if (~CS & noe)
         begin
           case (addr)
             7'b0000000: DO<=IREG_LP;          //IRQStatus
             7'b0000001: DO<=ISRCF;            //IRQRawStatus
             7'b0000010: DO<=IRQEnable;        //IRQEnable
             default:    DO<=8'b0;
           endcase
         end
      else DO<=8'b0;
end


always @(posedge MCLK or posedge RESET)
begin
 if (RESET)
    begin
      IRQEnable <= 8'b0;
      IRQSoft   <=  1'b0;
    end
 else
    begin
      if (~CS & nwe)
         begin
           case (addr)
             7'b0000010: IRQEnable <= ( DI | IRQEnable); //EnableSet
             7'b0000011: IRQEnable <= (~DI & IRQEnable); //EnableClear
             7'b0000100: IRQSoft   <= DI[1];                   //Programmed IRQ       
             default: ;
           endcase
         end
    end
end




endmodule
