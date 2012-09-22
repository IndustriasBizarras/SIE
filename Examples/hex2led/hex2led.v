module hex2led(HEX,LED);
    input [3:0] HEX;
    output [6:0] LED;

reg [6:0] LED;
always @(HEX)
begin
   case (HEX)
       4'h1 : LED = 7'b1111001;   //1
       4'h2 : LED = 7'b0100100;   //2
       4'h3 : LED = 7'b0110000;   //3
       4'h4 : LED = 7'b0011001;   //4
       4'h5 : LED = 7'b0010010;   //5
       4'h6 : LED = 7'b0000010;   //6
       4'h7 : LED = 7'b1111000;   //7
       4'h8 : LED = 7'b0000000;   //8
       4'h9 : LED = 7'b0010000;   //9
       4'hA : LED = 7'b0001000;   //A
       4'hB : LED = 7'b0000011;   //b
       4'hC : LED = 7'b1000110;   //C
       4'hD : LED = 7'b0100001;   //d
       4'hE : LED = 7'b0000110;   //E
       4'hF : LED = 7'b0001110;   //F
       default : LED = 7'b1000000;   //0
    endcase
end


endmodule
