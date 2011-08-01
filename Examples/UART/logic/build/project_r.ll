Revision 3
; Created by bitgen K.39 at Thu Nov 11 14:39:12 2010
; Bit lines have the following form:
; <offset> <frame address> <frame offset> <information>
; <information> may be zero or more <kw>=<value> pairs
; Block=<blockname     specifies the block associated with this
;                      memory cell.
;
; Latch=<name>         specifies the latch associated with this memory cell.
;
; Net=<netname>        specifies the user net associated with this
;                      memory cell.
;
; COMPARE=[YES | NO]   specifies whether or not it is appropriate
;                      to compare this bit position between a
;                      "program" and a "readback" bitstream.
;                      If not present the default is NO.
;
; Ram=<ram id>:<bit>   This is used in cases where a CLB function
; Rom=<ram id>:<bit>   generator is used as RAM (or ROM).  <Ram id>
;                      will be either 'F', 'G', or 'M', indicating
;                      that it is part of a single F or G function
;                      generator used as RAM, or as a single RAM
;                      (or ROM) built from both F and G.  <Bit> is
;                      a decimal number.
;
; Info lines have the following form:
; Info <name>=<value>  specifies a bit associated with the LCA
;                      configuration options, and the value of
;                      that bit.  The names of these bits may have
;                      special meaning to software reading the .ll file.
;
Info STARTSEL0=1
Bit     9552 0x00000400    240 Block=P5 Latch=T2 Net=T
Bit     9575 0x00000400    263 Block=P4 Latch=T2 Net=T
Bit    10640 0x00000400   1328 Block=P10 Latch=T2 Net=T
Bit    10663 0x00000400   1351 Block=P9 Latch=T2 Net=T
Bit    10768 0x00000400   1456 Block=P12 Latch=T2 Net=T
Bit    10791 0x00000400   1479 Block=P11 Latch=T2 Net=T
Bit    10896 0x00000400   1584 Block=P16 Latch=T2 Net=T
Bit    10919 0x00000400   1607 Block=P15 Latch=T2 Net=T
Bit    12656 0x00020000    240 Block=P5 Latch=O2 Net=rdBus<6>
Bit    12679 0x00020000    263 Block=P4 Latch=O2 Net=rdBus<7>
Bit    13744 0x00020000   1328 Block=P10 Latch=O2 Net=rdBus<4>
Bit    13767 0x00020000   1351 Block=P9 Latch=O2 Net=rdBus<5>
Bit    13872 0x00020000   1456 Block=P12 Latch=O2 Net=rdBus<2>
Bit    13895 0x00020000   1479 Block=P11 Latch=O2 Net=rdBus<3>
Bit    14000 0x00020000   1584 Block=P16 Latch=O2 Net=rdBus<0>
Bit    14023 0x00020000   1607 Block=P15 Latch=O2 Net=rdBus<1>
Bit    15759 0x00020200    239 Block=P5 Latch=IQ1 Net=buffer_data<6>
Bit    15784 0x00020200    264 Block=P4 Latch=IQ1 Net=buffer_data<7>
Bit    16847 0x00020200   1327 Block=P10 Latch=IQ1 Net=buffer_data<4>
Bit    16872 0x00020200   1352 Block=P9 Latch=IQ1 Net=buffer_data<5>
Bit    16975 0x00020200   1455 Block=P12 Latch=IQ1 Net=buffer_data<2>
Bit    17000 0x00020200   1480 Block=P11 Latch=IQ1 Net=buffer_data<3>
Bit    17103 0x00020200   1583 Block=P16 Latch=IQ1 Net=buffer_data<0>
Bit    17128 0x00020200   1608 Block=P15 Latch=IQ1 Net=buffer_data<1>
Bit   131834 0x00062200   1466 Block=SLICE_X2Y48 Latch=YQ Net=wdBus<2>
Bit   131837 0x00062200   1469 Block=SLICE_X2Y48 Latch=XQ Net=wdBus<3>
Bit   131962 0x00062200   1594 Block=SLICE_X2Y44 Latch=YQ Net=wdBus<0>
Bit   131965 0x00062200   1597 Block=SLICE_X2Y44 Latch=XQ Net=wdBus<1>
Bit   901082 0x00202400    922 Block=SLICE_X26Y65 Latch=YQ Net=wdBus<4>
Bit   901085 0x00202400    925 Block=SLICE_X26Y65 Latch=XQ Net=wdBus<5>
Bit   903706 0x00220000    442 Block=SLICE_X27Y80 Latch=YQ Net=wdBus<6>
Bit   903709 0x00220000    445 Block=SLICE_X27Y80 Latch=XQ Net=wdBus<7>
Bit   909416 0x00220200   3048 Block=P30 Latch=I Net=reset_IBUF
Bit  1019098 0x00242400    986 Block=SLICE_X30Y63 Latch=YQ Net=UART/buffrx1/datorx<6>
Bit  1019101 0x00242400    989 Block=SLICE_X30Y63 Latch=XQ Net=UART/buffrx1/datorx<7>
Bit  1019130 0x00242400   1018 Block=SLICE_X30Y62 Latch=YQ Net=UART/buffrx1/datorx<4>
Bit  1019133 0x00242400   1021 Block=SLICE_X30Y62 Latch=XQ Net=UART/buffrx1/datorx<5>
Bit  1080264 0x00280000     72 Block=P88 Latch=IQ1 Net=snwe
Bit  1140058 0x002a0000    890 Block=SLICE_X34Y66 Latch=YQ Net=UART/buffrx1/datorx<0>
Bit  1140061 0x002a0000    893 Block=SLICE_X34Y66 Latch=XQ Net=UART/buffrx1/datorx<1>
Bit  1140090 0x002a0000    922 Block=SLICE_X34Y65 Latch=YQ Net=UART/buffrx1/bufrx<2>
Bit  1140093 0x002a0000    925 Block=SLICE_X34Y65 Latch=XQ Net=UART/buffrx1/bufrx<3>
Bit  1140186 0x002a0000   1018 Block=SLICE_X34Y62 Latch=YQ Net=UART/buffrx1/bufrx<4>
Bit  1140189 0x002a0000   1021 Block=SLICE_X34Y62 Latch=XQ Net=UART/buffrx1/bufrx<5>
Bit  1143162 0x002a0200    890 Block=SLICE_X35Y66 Latch=YQ Net=UART/buffrx1/bufrx<0>
Bit  1143165 0x002a0200    893 Block=SLICE_X35Y66 Latch=XQ Net=UART/buffrx1/bufrx<1>
Bit  1143226 0x002a0200    954 Block=SLICE_X35Y64 Latch=YQ Net=UART/buffrx1/datorx<2>
Bit  1143229 0x002a0200    957 Block=SLICE_X35Y64 Latch=XQ Net=UART/buffrx1/datorx<3>
Bit  1143258 0x002a0200    986 Block=SLICE_X35Y63 Latch=YQ Net=UART/buffrx1/bufrx<6>
Bit  1143261 0x002a0200    989 Block=SLICE_X35Y63 Latch=XQ Net=UART/buffrx1/bufrx<7>
Bit  1145416 0x002a0400     40 Block=P86 Latch=I Net=noe_IBUF
Bit  1148463 0x002a0400   3087 Block=P38 Latch=I Net=clk_BUFGP/IBUFG
Bit  1258042 0x002e0000    922 Block=SLICE_X38Y65 Latch=YQ Net=UART/buffrx1/err_frame
Bit  1258077 0x002e0000    957 Block=SLICE_X38Y64 Latch=XQ Net=UART/buffrx1/err_paridad
Bit  1260271 0x002e0200     47 Block=P84 Latch=IQ1 Net=buffer_addr<0>
Bit  1260296 0x002e0200     72 Block=P83 Latch=IQ1 Net=buffer_addr<1>
Bit  1261210 0x002e0200    986 Block=SLICE_X39Y63 Latch=YQ Net=UART/buffrx1/bufrx<8>
Bit  1261213 0x002e0200    989 Block=SLICE_X39Y63 Latch=XQ Net=UART/buffrx1/bufrx<9>
Bit  1317242 0x00300000   1146 Block=SLICE_X40Y58 Latch=YQ Net=UART/ctrl_rx1/cont_rx<2>
Bit  1317245 0x00300000   1149 Block=SLICE_X40Y58 Latch=XQ Net=UART/ctrl_rx1/cont_rx<3>
Bit  1319152 0x00300000   3056 Block=P44 Latch=O2 Net=Result<23>
Bit  1320186 0x00300200    986 Block=SLICE_X41Y63 Latch=YQ Net=UART/pulso2/dff
Bit  1320314 0x00300200   1114 Block=SLICE_X41Y59 Latch=YQ Net=UART/ctrl_rx1/cont_rx<0>
Bit  1320317 0x00300200   1117 Block=SLICE_X41Y59 Latch=XQ Net=UART/ctrl_rx1/cont_rx<1>
Bit  1376061 0x00320000    989 Block=SLICE_X42Y63 Latch=XQ Net=UART/muestreo1/sample
Bit  1376093 0x00320000   1021 Block=SLICE_X42Y62 Latch=XQ Net=UART/muestreo1/cont_m<3>
Bit  1379066 0x00320200    890 Block=SLICE_X43Y66 Latch=YQ Net=UART/isr1/mask_error
Bit  1379162 0x00320200    986 Block=SLICE_X43Y63 Latch=YQ Net=UART/muestreo1/cont_m<2>
Bit  1379194 0x00320200   1018 Block=SLICE_X43Y62 Latch=YQ Net=UART/muestreo1/cont_m<0>
Bit  1379197 0x00320200   1021 Block=SLICE_X43Y62 Latch=XQ Net=UART/muestreo1/cont_m<1>
Bit  1379293 0x00320200   1117 Block=SLICE_X43Y59 Latch=XQ Net=UART/ctrl_rx1/rx_lleno
Bit  1380826 0x00320200   2650 Block=SLICE_X43Y11 Latch=YQ Net=counter<23>
Bit  1380829 0x00320200   2653 Block=SLICE_X43Y11 Latch=XQ Net=counter<22>
Bit  1380858 0x00320200   2682 Block=SLICE_X43Y10 Latch=YQ Net=counter<21>
Bit  1380861 0x00320200   2685 Block=SLICE_X43Y10 Latch=XQ Net=counter<20>
Bit  1380890 0x00320200   2714 Block=SLICE_X43Y9 Latch=YQ Net=counter<19>
Bit  1380893 0x00320200   2717 Block=SLICE_X43Y9 Latch=XQ Net=counter<18>
Bit  1380922 0x00320200   2746 Block=SLICE_X43Y8 Latch=YQ Net=counter<17>
Bit  1380925 0x00320200   2749 Block=SLICE_X43Y8 Latch=XQ Net=counter<16>
Bit  1380954 0x00320200   2778 Block=SLICE_X43Y7 Latch=YQ Net=counter<15>
Bit  1380957 0x00320200   2781 Block=SLICE_X43Y7 Latch=XQ Net=counter<14>
Bit  1380986 0x00320200   2810 Block=SLICE_X43Y6 Latch=YQ Net=counter<13>
Bit  1380989 0x00320200   2813 Block=SLICE_X43Y6 Latch=XQ Net=counter<12>
Bit  1381018 0x00320200   2842 Block=SLICE_X43Y5 Latch=YQ Net=counter<11>
Bit  1381021 0x00320200   2845 Block=SLICE_X43Y5 Latch=XQ Net=counter<10>
Bit  1381050 0x00320200   2874 Block=SLICE_X43Y4 Latch=YQ Net=counter<9>
Bit  1381053 0x00320200   2877 Block=SLICE_X43Y4 Latch=XQ Net=counter<8>
Bit  1381082 0x00320200   2906 Block=SLICE_X43Y3 Latch=YQ Net=counter<7>
Bit  1381085 0x00320200   2909 Block=SLICE_X43Y3 Latch=XQ Net=counter<6>
Bit  1381114 0x00320200   2938 Block=SLICE_X43Y2 Latch=YQ Net=counter<5>
Bit  1381117 0x00320200   2941 Block=SLICE_X43Y2 Latch=XQ Net=counter<4>
Bit  1381146 0x00320200   2970 Block=SLICE_X43Y1 Latch=YQ Net=counter<3>
Bit  1381149 0x00320200   2973 Block=SLICE_X43Y1 Latch=XQ Net=counter<2>
Bit  1381178 0x00320200   3002 Block=SLICE_X43Y0 Latch=YQ Net=counter<1>
Bit  1381181 0x00320200   3005 Block=SLICE_X43Y0 Latch=XQ Net=counter<0>
Bit  1434781 0x00340000    733 Block=SLICE_X44Y71 Latch=XQ Net=UART/isr1/ISR<0>
Bit  1434810 0x00340000    762 Block=SLICE_X44Y70 Latch=YQ Net=UART/isr1/ISR<1>
Bit  1434842 0x00340000    794 Block=SLICE_X44Y69 Latch=YQ Net=UART/isr1/mask_dato_rdy
Bit  1434877 0x00340000    829 Block=SLICE_X44Y68 Latch=XQ Net=UART/isr1/ISR<2>
Bit  1434906 0x00340000    858 Block=SLICE_X44Y67 Latch=YQ Net=UART/lcr1/LCR<0>
Bit  1434909 0x00340000    861 Block=SLICE_X44Y67 Latch=XQ Net=UART/lcr1/LCR<1>
Bit  1435002 0x00340000    954 Block=SLICE_X44Y64 Latch=YQ Net=UART/lcr1/LCR<4>
Bit  1435005 0x00340000    957 Block=SLICE_X44Y64 Latch=XQ Net=UART/lcr1/LCR<5>
Bit  1438010 0x00340200    858 Block=SLICE_X45Y67 Latch=YQ Net=UART/lcr1/LCR<6>
Bit  1438013 0x00340200    861 Block=SLICE_X45Y67 Latch=XQ Net=UART/lcr1/LCR<7>
Bit  1438074 0x00340200    922 Block=SLICE_X45Y65 Latch=YQ Net=UART/lcr1/LCR<2>
Bit  1438077 0x00340200    925 Block=SLICE_X45Y65 Latch=XQ Net=UART/lcr1/LCR<3>
Bit  1493754 0x00360000    730 Block=SLICE_X46Y71 Latch=YQ Net=UART/isr1/mask_tx_empty
Bit  1493853 0x00360000    829 Block=SLICE_X46Y68 Latch=XQ Net=UART/dato_rdy1/err_overrun
Bit  1494202 0x00360000   1178 Block=SLICE_X46Y57 Latch=YQ Net=UART/div27/div27<2>
Bit  1494205 0x00360000   1181 Block=SLICE_X46Y57 Latch=XQ Net=UART/div27/div27<3>
Bit  1494234 0x00360000   1210 Block=SLICE_X46Y56 Latch=YQ Net=UART/div27/div27<1>
Bit  1497309 0x00360200   1181 Block=SLICE_X47Y57 Latch=XQ Net=UART/div27/div27<0>
Bit  1497341 0x00360200   1213 Block=SLICE_X47Y56 Latch=XQ Net=UART/div27/div27<4>
Bit  1552730 0x00380000    730 Block=SLICE_X48Y71 Latch=YQ Net=UART/dato_rdy1/dato_rdy
Bit  1552794 0x00380000    794 Block=SLICE_X48Y69 Latch=YQ Net=UART/div_ms1/div<12>
Bit  1552797 0x00380000    797 Block=SLICE_X48Y69 Latch=XQ Net=UART/div_ms1/div<13>
Bit  1552826 0x00380000    826 Block=SLICE_X48Y68 Latch=YQ Net=UART/div_ms1/div<14>
Bit  1552829 0x00380000    829 Block=SLICE_X48Y68 Latch=XQ Net=UART/div_ms1/div<15>
Bit  1552922 0x00380000    922 Block=SLICE_X48Y65 Latch=YQ Net=UART/div_ms1/div<6>
Bit  1552925 0x00380000    925 Block=SLICE_X48Y65 Latch=XQ Net=UART/div_ms1/div<7>
Bit  1552954 0x00380000    954 Block=SLICE_X48Y64 Latch=YQ Net=UART/div_ms1/div<2>
Bit  1552957 0x00380000    957 Block=SLICE_X48Y64 Latch=XQ Net=UART/div_ms1/div<3>
Bit  1553018 0x00380000   1018 Block=SLICE_X48Y62 Latch=YQ Net=UART/div_ms1/clk_out
Bit  1556285 0x00380200   1181 Block=SLICE_X49Y57 Latch=XQ Net=UART/div27/div27<5>
Bit  1614554 0x003a0200    474 Block=SLICE_X50Y79 Latch=YQ Net=UART/bufftx1/dato_tx<6>
Bit  1614557 0x003a0200    477 Block=SLICE_X50Y79 Latch=XQ Net=UART/bufftx1/dato_tx<7>
Bit  1614618 0x003a0200    538 Block=SLICE_X50Y77 Latch=YQ Net=UART/isr1/aux1
Bit  1614682 0x003a0200    602 Block=SLICE_X50Y75 Latch=YQ Net=UART/bufftx1/dato_tx<4>
Bit  1614685 0x003a0200    605 Block=SLICE_X50Y75 Latch=XQ Net=UART/bufftx1/dato_tx<5>
Bit  1614746 0x003a0200    666 Block=SLICE_X50Y73 Latch=YQ Net=UART/isr1/carga_ISRd
Bit  1614906 0x003a0200    826 Block=SLICE_X50Y68 Latch=YQ Net=UART/bufftx1/dato_tx<0>
Bit  1614909 0x003a0200    829 Block=SLICE_X50Y68 Latch=XQ Net=UART/bufftx1/dato_tx<1>
Bit  1614938 0x003a0200    858 Block=SLICE_X50Y67 Latch=YQ Net=UART/div_ms1/div<4>
Bit  1614941 0x003a0200    861 Block=SLICE_X50Y67 Latch=XQ Net=UART/div_ms1/div<5>
Bit  1615002 0x003a0200    922 Block=SLICE_X50Y65 Latch=YQ Net=UART/bufftx1/buftx<1>
Bit  1615005 0x003a0200    925 Block=SLICE_X50Y65 Latch=XQ Net=UART/bufftx1/buftx<2>
Bit  1615034 0x003a0200    954 Block=SLICE_X50Y64 Latch=YQ Net=UART/bufftx1/buftx<9>
Bit  1615098 0x003a0200   1018 Block=SLICE_X50Y62 Latch=YQ Net=UART/muestreo1/flag_rx
Bit  1617658 0x003a0400    474 Block=SLICE_X51Y79 Latch=YQ Net=we
Bit  1617661 0x003a0400    477 Block=SLICE_X51Y79 Latch=XQ Net=w_st
Bit  1617850 0x003a0400    666 Block=SLICE_X51Y73 Latch=YQ Net=UART/bufftx1/buftx<5>
Bit  1617853 0x003a0400    669 Block=SLICE_X51Y73 Latch=XQ Net=UART/bufftx1/buftx<6>
Bit  1617882 0x003a0400    698 Block=SLICE_X51Y72 Latch=YQ Net=UART/bufftx1/buftx<7>
Bit  1617885 0x003a0400    701 Block=SLICE_X51Y72 Latch=XQ Net=UART/bufftx1/buftx<8>
Bit  1617914 0x003a0400    730 Block=SLICE_X51Y71 Latch=YQ Net=UART/bufftx1/dato_tx<2>
Bit  1617917 0x003a0400    733 Block=SLICE_X51Y71 Latch=XQ Net=UART/bufftx1/dato_tx<3>
Bit  1617946 0x003a0400    762 Block=SLICE_X51Y70 Latch=YQ Net=UART/bufftx1/buftx<3>
Bit  1617949 0x003a0400    765 Block=SLICE_X51Y70 Latch=XQ Net=UART/bufftx1/buftx<4>
Bit  1617978 0x003a0400    794 Block=SLICE_X51Y69 Latch=YQ Net=UART/ier1/IER<0>
Bit  1617981 0x003a0400    797 Block=SLICE_X51Y69 Latch=XQ Net=UART/ier1/IER<1>
Bit  1618010 0x003a0400    826 Block=SLICE_X51Y68 Latch=YQ Net=UART/ier1/IER<2>
Bit  1618042 0x003a0400    858 Block=SLICE_X51Y67 Latch=YQ Net=UART/div_ms1/div<10>
Bit  1618045 0x003a0400    861 Block=SLICE_X51Y67 Latch=XQ Net=UART/div_ms1/div<11>
Bit  1618074 0x003a0400    890 Block=SLICE_X51Y66 Latch=YQ Net=UART/div_ms1/div<8>
Bit  1618077 0x003a0400    893 Block=SLICE_X51Y66 Latch=XQ Net=UART/div_ms1/div<9>
Bit  1618106 0x003a0400    922 Block=SLICE_X51Y65 Latch=YQ Net=UART/div_ms1/k_div<2>
Bit  1618109 0x003a0400    925 Block=SLICE_X51Y65 Latch=XQ Net=UART/div_ms1/k_div<3>
Bit  1618138 0x003a0400    954 Block=SLICE_X51Y64 Latch=YQ Net=UART/div_ms1/div<0>
Bit  1618141 0x003a0400    957 Block=SLICE_X51Y64 Latch=XQ Net=UART/div_ms1/div<1>
Bit  1618202 0x003a0400   1018 Block=SLICE_X51Y62 Latch=YQ Net=UART/pulso1/dff
Bit  1673850 0x003c0200    794 Block=SLICE_X52Y69 Latch=YQ Net=UART/div_ms1/k_div<12>
Bit  1673853 0x003c0200    797 Block=SLICE_X52Y69 Latch=XQ Net=UART/div_ms1/k_div<13>
Bit  1673946 0x003c0200    890 Block=SLICE_X52Y66 Latch=YQ Net=UART/div_ms1/k_div<14>
Bit  1673949 0x003c0200    893 Block=SLICE_X52Y66 Latch=XQ Net=UART/div_ms1/k_div<15>
Bit  1673978 0x003c0200    922 Block=SLICE_X52Y65 Latch=YQ Net=UART/div_ms1/k_div<4>
Bit  1673981 0x003c0200    925 Block=SLICE_X52Y65 Latch=XQ Net=UART/div_ms1/k_div<5>
Bit  1674010 0x003c0200    954 Block=SLICE_X52Y64 Latch=YQ Net=UART/div_ms1/k_div<0>
Bit  1674013 0x003c0200    957 Block=SLICE_X52Y64 Latch=XQ Net=UART/div_ms1/k_div<1>
Bit  1676954 0x02000000    794 Block=SLICE_X53Y69 Latch=YQ Net=UART/div_ms1/k_div<10>
Bit  1676957 0x02000000    797 Block=SLICE_X53Y69 Latch=XQ Net=UART/div_ms1/k_div<11>
Bit  1676986 0x02000000    826 Block=SLICE_X53Y68 Latch=YQ Net=UART/div_ms1/k_div<8>
Bit  1676989 0x02000000    829 Block=SLICE_X53Y68 Latch=XQ Net=UART/div_ms1/k_div<9>
Bit  1677146 0x02000000    986 Block=SLICE_X53Y63 Latch=YQ Net=UART/div_ms1/k_div<6>
Bit  1677149 0x02000000    989 Block=SLICE_X53Y63 Latch=XQ Net=UART/div_ms1/k_div<7>
Bit  1732893 0x02002400    861 Block=SLICE_X54Y67 Latch=XQ Net=UART/ctrl_tx1/tx_empty
Bit  1732986 0x02002400    954 Block=SLICE_X54Y64 Latch=YQ Net=UART/div161/div16<1>
Bit  1732989 0x02002400    957 Block=SLICE_X54Y64 Latch=XQ Net=UART/div161/div16<0>
Bit  1733021 0x02002400    989 Block=SLICE_X54Y63 Latch=XQ Net=UART/ctrl_tx1/tx_on
Bit  1733050 0x02002400   1018 Block=SLICE_X54Y62 Latch=YQ Net=UART/ctrl_tx1/cont_tx<2>
Bit  1733053 0x02002400   1021 Block=SLICE_X54Y62 Latch=XQ Net=UART/ctrl_tx1/cont_tx<3>
Bit  1736058 0x02002600    922 Block=SLICE_X55Y65 Latch=YQ Net=UART/pulso3/dff
Bit  1736090 0x02002600    954 Block=SLICE_X55Y64 Latch=YQ Net=UART/div161/div16<2>
Bit  1736093 0x02002600    957 Block=SLICE_X55Y64 Latch=XQ Net=UART/div161/div16<3>
Bit  1736122 0x02002600    986 Block=SLICE_X55Y63 Latch=YQ Net=UART/ctrl_tx1/cont_tx<0>
Bit  1736125 0x02002600    989 Block=SLICE_X55Y63 Latch=XQ Net=UART/ctrl_tx1/cont_tx<1>
Bit  1736378 0x02002600   1242 Block=SLICE_X55Y55 Latch=YQ Net=UART/ifrxd1/ifrxd<2>
Bit  1736381 0x02002600   1245 Block=SLICE_X55Y55 Latch=XQ Net=UART/ifrxd1/ifrxd<1>
Bit  2089039 0x02027200     47 Block=P79 Latch=IQ1 Net=buffer_addr<2>
Bit  2205104 0x04002400   1264 Block=P71 Latch=O2 Net=irq_pin_OBUF
Bit  2205255 0x04002400   1415 Block=P67 Latch=O2 Net=UART/bufftx1/buftx_0_mux0000
Bit  2208256 0x04020000   1312 Block=P69 Latch=IQ1 Net=sncs
Bit  2208335 0x04020000   1391 Block=P68 Latch=IQ1 Net=UART/ifrxd1/ifrxd<0>
Bit  2211367 0x04020200   1319 Block=P69 Latch=I Net=ncs_IBUF
