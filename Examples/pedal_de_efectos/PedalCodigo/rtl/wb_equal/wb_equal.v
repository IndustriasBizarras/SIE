module wb_equal(
	input clk,
	input reset,
	input [7:0] datain,
	input RDYin,
	output [23:0] eqbass,
	output RDYeq,


	// Wishbone interface
	input              wb_stb_i,
	input              wb_cyc_i,
	output             wb_ack_o,
	input              wb_we_i,
	input       [31:0] wb_adr_i,
	input        [3:0] wb_sel_i,
	input       [31:0] wb_dat_i,
	output reg  [31:0] wb_dat_o
);

   wire [7:0] Wire_6;
   wire [7:0] Wire_8;
   wire [7:0] Wire_9;
   wire [7:0] Wire_10;
   wire [7:0] Wire_11;
   wire [7:0] Wire_12;
   wire [7:0] Wire_13;
   wire [7:0] Wire_14;
   wire [7:0] Wire_15;
   wire [7:0] Wire_16;
   wire [7:0] Wire_18;
   wire Wire_49;
   wire [7:0] Wire_55;
   wire [7:0] Wire_57;
   wire [7:0] Wire_59;
   wire [7:0] Wire_63;
   wire [15:0] Wire_78;
   wire [15:0] Wire_79;
   wire [15:0] Wire_80;
   wire [15:0] Wire_81;
   wire [15:0] Wire_82;
   wire [15:0] Wire_83;
   wire [15:0] Wire_84;
   wire [15:0] Wire_85;
   wire [15:0] Wire_86;
   wire [15:0] Wire_87;
   wire [15:0] Wire_88;
   wire [15:0] Wire_89;
   wire [15:0] Wire_90;
   wire [15:0] Wire_91;
   wire [15:0] Wire_92;
   wire [15:0] Wire_93;
   wire Wire_94;
   wire [16:0] Wire_95;
   wire [16:0] Wire_96;
   wire [16:0] Wire_97;
   wire [16:0] Wire_98;
   wire [16:0] Wire_99;
   wire [16:0] Wire_100;
   wire [16:0] Wire_101;
   wire [16:0] Wire_102;
   wire [16:0] Wire_103;
   wire [16:0] Wire_104;
   wire [16:0] Wire_105;
   wire [16:0] Wire_106;
   wire [16:0] Wire_107;
   wire [16:0] Wire_108;
   wire [16:0] Wire_109;
   wire [16:0] Wire_110;
   wire Wire_111;
   wire Wire_112;
   wire [19:0] Wire_113;
   wire Wire_115;
   wire [22:0] Wire_116;
   wire [7:0] Wire_131;
   wire Wire_140;
   wire Wire_141;
   wire [22:0] Wire_142;
   wire [19:0] Wire_143;

reg [2:0]gainb;
reg [2:0]gainh;
   
initial begin
gainb=0;
gainh=0;
end

   ShiftedReg ShiftedReg_m (
		      .adcin(datain[7:0]), 
                      .clk(clk), 
                      .RDYadc(RDYin), 
                      .outshift0(Wire_57[7:0]), 
                      .outshift1(Wire_63[7:0]), 
                      .outshift2(Wire_59[7:0]), 
                      .outshift3(Wire_55[7:0]), 
                      .outshift4(Wire_6[7:0]), 
                      .outshift5(Wire_8[7:0]), 
                      .outshift6(Wire_9[7:0]), 
                      .outshift7(Wire_10[7:0]), 
                      .outshift8(Wire_11[7:0]), 
                      .outshift9(Wire_12[7:0]), 
                      .outshift10(Wire_13[7:0]), 
                      .outshift11(Wire_14[7:0]), 
                      .outshift12(Wire_15[7:0]), 
                      .outshift13(Wire_16[7:0]), 
                      .outshift14(Wire_131[7:0]), 
                      .outshift15(Wire_18[7:0]), 
                      .RDYshift(Wire_49));
   CoefficientBass CoefficientBass_m (
			   .clk(clk), 
                           .datain0(Wire_57[7:0]), 
                           .datain1(Wire_63[7:0]), 
                           .datain2(Wire_59[7:0]), 
                           .datain3(Wire_55[7:0]), 
                           .datain4(Wire_6[7:0]), 
                           .datain5(Wire_8[7:0]), 
                           .datain6(Wire_9[7:0]), 
                           .datain7(Wire_10[7:0]), 
                           .datain8(Wire_11[7:0]), 
                           .datain9(Wire_12[7:0]), 
                           .datain10(Wire_13[7:0]), 
                           .datain11(Wire_14[7:0]), 
                           .datain12(Wire_15[7:0]), 
                           .datain13(Wire_16[7:0]), 
                           .datain14(Wire_131[7:0]), 
                           .datain15(Wire_18[7:0]), 
                           .RDYshift(Wire_49), 
                           .dataoutb0(Wire_78[15:0]), 
                           .dataoutb1(Wire_79[15:0]), 
                           .dataoutb2(Wire_80[15:0]), 
                           .dataoutb3(Wire_81[15:0]), 
                           .dataoutb4(Wire_82[15:0]), 
                           .dataoutb5(Wire_83[15:0]), 
                           .dataoutb6(Wire_84[15:0]), 
                           .dataoutb7(Wire_85[15:0]), 
                           .dataoutb8(Wire_86[15:0]), 
                           .dataoutb9(Wire_87[15:0]), 
                           .dataoutb10(Wire_88[15:0]), 
                           .dataoutb11(Wire_89[15:0]), 
                           .dataoutb12(Wire_90[15:0]), 
                           .dataoutb13(Wire_91[15:0]), 
                           .dataoutb14(Wire_92[15:0]), 
                           .dataoutb15(Wire_93[15:0]), 
                           .RDYcoeBass(Wire_111));
   CoefficientHigh CoefficientHigh_m (
			   .clk(clk), 
                           .datain0(Wire_57[7:0]), 
                           .datain1(Wire_63[7:0]), 
                           .datain2(Wire_59[7:0]), 
                           .datain3(Wire_55[7:0]), 
                           .datain4(Wire_6[7:0]), 
                           .datain5(Wire_8[7:0]), 
                           .datain6(Wire_9[7:0]), 
                           .datain7(Wire_10[7:0]), 
                           .datain8(Wire_11[7:0]), 
                           .datain9(Wire_12[7:0]), 
                           .datain10(Wire_13[7:0]), 
                           .datain11(Wire_14[7:0]), 
                           .datain12(Wire_15[7:0]), 
                           .datain13(Wire_16[7:0]), 
                           .datain14(Wire_131[7:0]), 
                           .datain15(Wire_18[7:0]), 
                           .RDYshift(Wire_49), 
                           .dataouth0(Wire_95[16:0]), 
                           .dataouth1(Wire_96[16:0]), 
                           .dataouth2(Wire_97[16:0]), 
                           .dataouth3(Wire_98[16:0]), 
                           .dataouth4(Wire_99[16:0]), 
                           .dataouth5(Wire_100[16:0]), 
                           .dataouth6(Wire_101[16:0]), 
                           .dataouth7(Wire_102[16:0]), 
                           .dataouth8(Wire_103[16:0]), 
                           .dataouth9(Wire_104[16:0]), 
                           .dataouth10(Wire_105[16:0]), 
                           .dataouth11(Wire_106[16:0]), 
                           .dataouth12(Wire_107[16:0]), 
                           .dataouth13(Wire_108[16:0]), 
                           .dataouth14(Wire_109[16:0]), 
                           .dataouth15(Wire_110[16:0]), 
                           .RDYcoehigh(Wire_94));
   adderbass adderbass_m (
		     .clk(clk), 
                     .inBass0(Wire_78[15:0]), 
                     .inBass1(Wire_79[15:0]), 
                     .inBass2(Wire_80[15:0]), 
                     .inBass3(Wire_81[15:0]), 
                     .inBass4(Wire_82[15:0]), 
                     .inBass5(Wire_83[15:0]), 
                     .inBass6(Wire_84[15:0]), 
                     .inBass7(Wire_85[15:0]), 
                     .inBass8(Wire_86[15:0]), 
                     .inBass9(Wire_87[15:0]), 
                     .inBass10(Wire_88[15:0]), 
                     .inBass11(Wire_89[15:0]), 
                     .inBass12(Wire_90[15:0]), 
                     .inBass13(Wire_91[15:0]), 
                     .inBass14(Wire_92[15:0]), 
                     .inBass15(Wire_93[15:0]), 
                     .RDYcoeBass(Wire_111), 
                     .outBASS(Wire_113[19:0]), 
                     .RDYaddBass(Wire_112));
   adderhigh adderhigh_m (
		     .clk(clk), 
                     .inHIGH0(Wire_95[16:0]), 
                     .inHIGH1(Wire_96[16:0]), 
                     .inHIGH2(Wire_97[16:0]), 
                     .inHIGH3(Wire_98[16:0]), 
                     .inHIGH4(Wire_99[16:0]), 
                     .inHIGH5(Wire_100[16:0]), 
                     .inHIGH6(Wire_101[16:0]), 
                     .inHIGH7(Wire_102[16:0]), 
                     .inHIGH8(Wire_103[16:0]), 
                     .inHIGH9(Wire_104[16:0]), 
                     .inHIGH10(Wire_105[16:0]), 
                     .inHIGH11(Wire_106[16:0]), 
                     .inHIGH12(Wire_107[16:0]), 
                     .inHIGH13(Wire_108[16:0]), 
                     .inHIGH14(Wire_109[16:0]), 
                     .inHIGH15(Wire_110[16:0]), 
                     .RDYcoeHigh(Wire_94), 
                     .outHIGH(Wire_116[22:0]), 
                     .RDYaddHigh(Wire_115));
   BassCtrlGain BassCtrlGain_m (
			.clk(clk), 
                        .gainB(gainb), 
                        .inBass(Wire_113[19:0]), 
                        .RDYaddbass(Wire_112), 
                        .outBass(Wire_143[19:0]), 
                        .RDYctrlbass(Wire_140));
   HighCtrlGain HighCtrlGain_m (
			.clk(clk), 
                        .gainH(gainh), 
                        .inHigh(Wire_116[22:0]), 
                        .RDYaddhigh(Wire_115), 
                        .outHigh(Wire_142[22:0]), 
                        .RDYctrlhigh(Wire_141));
   adderfinal adderfinal_m (
		      .clk(clk), 
                      .inBass(Wire_143[19:0]), 
                      .inHIGH(Wire_142[22:0]), 
                      .RDYctrlbass(Wire_140), 
                      .RDYctrlhigh(Wire_141), 
                      .eqbass(eqbass[23:0]), 
                      .RDYeq(RDYeq));



reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

always @(posedge clk)
begin


	if (reset) begin
		wb_dat_o<=0;	
		ack<= 0;
	end else begin
       		ack <= wb_stb_i & wb_cyc_i;
		if (wb_rd & ~ack) begin           // read cycle
			
			 case (wb_adr_i[7:0])
				8'h00: begin 
					wb_dat_o[2:0] <= gainb;
					wb_dat_o[31:3] <=0;
					end 
				8'h04: begin 
					wb_dat_o[2:0] <= gainh;
					wb_dat_o[31:3] <=0;
					end 

				default: wb_dat_o <= 32'hFF;				//FF read cycle address incorrect
			endcase

		end else if (wb_wr & ~ack ) begin // write cycle
				
				 case (wb_adr_i[7:0]) 
						8'h00: begin 
							gainb<=wb_dat_i[2:0];
						end
						8'h04: begin 
							gainh<=wb_dat_i[2:0];
						end
						default: wb_dat_o<= 32'h0F;			//0F write cycle address incorrect
				endcase
		end else wb_dat_o <= 32'hDF;
		
	end
end



endmodule
