module comp(in_tmp, out_comp);
  input [3:0]in_tmp;
  output out_comp;
  reg tmp;
    always@(in_tmp)
      tmp = (4'b1000 == in_tmp) ? 1'b1 : 1'b0;
    assign out_comp=tmp;
endmodule
