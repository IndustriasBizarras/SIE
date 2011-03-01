EESchema Schematic File Version 2  date mié 22 sep 2010 13:56:54 COT
LIBS:/home/ari/Documentos/ps2/Design files/header_20x2,/home/ari/Documentos/ps2/Design files/header_4,/home/ari/Documentos/ps2/Design files/header_2,/home/ari/kicad/SparkFun.lbr/SparkFun,power,device,transistors,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,opto,atmel,contrib,valves,./ps2.cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title "PS2"
Date "22 sep 2010"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	7450 1550 7300 1550
Wire Wire Line
	5450 2300 5450 2500
Wire Wire Line
	5550 2300 5550 2500
Wire Wire Line
	4900 3200 4900 3400
Wire Wire Line
	5850 3200 5850 3400
Wire Wire Line
	4700 3800 4700 3200
Wire Wire Line
	5250 3900 5250 3200
Wire Wire Line
	7800 1700 7300 1700
Wire Wire Line
	7800 1600 7300 1600
Wire Wire Line
	5850 2700 5650 2700
Wire Wire Line
	5650 2700 5650 2300
Wire Wire Line
	4900 2700 4700 2700
Wire Wire Line
	4300 2300 4300 2700
Wire Wire Line
	4700 2700 4700 2300
Wire Wire Line
	4300 2700 4500 2700
Wire Wire Line
	5250 2300 5250 2700
Wire Wire Line
	5250 2700 5450 2700
Wire Wire Line
	7800 1650 7300 1650
Wire Wire Line
	7800 1750 7300 1750
Wire Wire Line
	5650 3850 5650 3200
Wire Wire Line
	4300 3850 4300 3200
Wire Wire Line
	6500 3150 6300 3150
Wire Wire Line
	5450 3200 5450 3400
Wire Wire Line
	4500 3200 4500 3400
Wire Wire Line
	4600 2300 4600 2500
Wire Wire Line
	4500 2300 4500 2500
Text Label 7450 1550 0    39   ~ 0
GND
Text Label 4500 2500 1    39   ~ 0
GND
Text Label 5450 2500 1    39   ~ 0
GND
Text Label 4600 2500 1    39   ~ 0
VCC
Text Label 5550 2500 1    39   ~ 0
VCC
Text Label 4500 3400 1    39   ~ 0
VCC
Text Label 4900 3400 1    39   ~ 0
VCC
Text Label 5450 3400 1    39   ~ 0
VCC
Text Label 5850 3400 1    39   ~ 0
VCC
Text Label 6300 3150 0    39   ~ 0
VCC
Text Label 7800 1750 0    39   ~ 0
PS2_CLK2
Text Label 7800 1700 0    39   ~ 0
PS2_DATA2
Text Label 7800 1650 0    39   ~ 0
PS2_CLK1
Text Label 7800 1600 0    39   ~ 0
PS2_DATA1
Text Label 5650 3850 1    39   ~ 0
PS2_CLK2
Text Label 5250 3900 1    39   ~ 0
PS2_DATA2
Text Label 4700 3800 1    39   ~ 0
PS2_CLK1
Text Label 4300 3850 1    39   ~ 0
PS2_DATA1
NoConn ~ 7300 1800
NoConn ~ 7300 1850
NoConn ~ 7300 1900
NoConn ~ 7300 1950
NoConn ~ 7300 2000
NoConn ~ 7300 2050
NoConn ~ 7300 2100
NoConn ~ 7300 2150
NoConn ~ 7300 2200
NoConn ~ 7300 2250
NoConn ~ 7300 2300
NoConn ~ 7300 2350
NoConn ~ 7300 2400
NoConn ~ 7300 2450
NoConn ~ 7300 2500
NoConn ~ 6700 2500
NoConn ~ 6700 2450
NoConn ~ 6700 2400
NoConn ~ 6700 2350
NoConn ~ 6700 2300
NoConn ~ 6700 2250
NoConn ~ 6700 2200
NoConn ~ 6700 2150
NoConn ~ 6700 2100
NoConn ~ 6700 2050
NoConn ~ 6700 2000
NoConn ~ 6700 1950
NoConn ~ 6700 1900
NoConn ~ 6700 1850
NoConn ~ 6700 1800
NoConn ~ 6700 1750
NoConn ~ 6700 1700
NoConn ~ 6700 1650
NoConn ~ 6700 1600
NoConn ~ 6700 1550
NoConn ~ 8150 2550
NoConn ~ 8150 2500
NoConn ~ 8150 2450
NoConn ~ 8150 2400
NoConn ~ 8150 2150
NoConn ~ 8150 2100
NoConn ~ 8150 2050
NoConn ~ 8150 2000
NoConn ~ 6500 3250
NoConn ~ 5750 2300
NoConn ~ 5350 2300
NoConn ~ 4800 2300
NoConn ~ 4400 2300
$Comp
L R R8
U 1 1 4C9A359B
P 5850 2950
F 0 "R8" V 5930 2950 50  0000 C CNN
F 1 "10K" V 5850 2950 50  0000 C CNN
	1    5850 2950
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 4C9A358F
P 5450 2950
F 0 "R7" V 5530 2950 50  0000 C CNN
F 1 "10K" V 5450 2950 50  0000 C CNN
	1    5450 2950
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 4C9A3588
P 4900 2950
F 0 "R6" V 4980 2950 50  0000 C CNN
F 1 "10K" V 4900 2950 50  0000 C CNN
	1    4900 2950
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4C9A3558
P 4500 2950
F 0 "R5" V 4580 2950 50  0000 C CNN
F 1 "10K" V 4500 2950 50  0000 C CNN
	1    4500 2950
	1    0    0    -1  
$EndComp
$Comp
L HEADER_2 J2
U 1 1 4C9A34CA
P 6800 3000
F 0 "J2" H 6550 3200 60  0000 C CNN
F 1 "HEADER_2" H 6800 3000 60  0000 C CNN
	1    6800 3000
	-1   0    0    1   
$EndComp
$Comp
L HEADER_4 J4
U 1 1 4C9A34A9
P 7900 2700
F 0 "J4" H 7700 2900 60  0000 C CNN
F 1 "HEADER_4" H 7900 2700 60  0000 C CNN
	1    7900 2700
	1    0    0    -1  
$EndComp
$Comp
L HEADER_4 J3
U 1 1 4C9A34A5
P 7900 2300
F 0 "J3" H 7700 2500 60  0000 C CNN
F 1 "HEADER_4" H 7900 2300 60  0000 C CNN
	1    7900 2300
	1    0    0    -1  
$EndComp
$Comp
L HEADER_20X2 J1
U 1 1 4C9A3459
P 7050 2650
F 0 "J1" H 6900 3900 60  0000 C CNN
F 1 "HEADER_20X2" H 7050 2650 60  0000 C CNN
	1    7050 2650
	1    0    0    -1  
$EndComp
$Comp
L MINI-DIN6PTH ?
U 1 1 4C9A33C5
P 5450 2100
AR Path="/4C9A3321" Ref="?"  Part="1" 
AR Path="/4C9A33C5" Ref="JS2"  Part="1" 
F 0 "JS2" V 5150 2100 60  0000 C CNN
F 1 "MINI-DIN6PTH" V 5300 2150 60  0000 C CNN
	1    5450 2100
	0    1    1    0   
$EndComp
$Comp
L MINI-DIN6PTH JS1
U 1 1 4C9A3321
P 4500 2100
F 0 "JS1" V 4200 2100 60  0000 C CNN
F 1 "MINI-DIN6PTH" V 4350 2150 60  0000 C CNN
	1    4500 2100
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 4C9A32D6
P 5650 2950
F 0 "R4" V 5730 2950 50  0000 C CNN
F 1 "270" V 5650 2950 50  0000 C CNN
	1    5650 2950
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4C9A32D1
P 5250 2950
F 0 "R3" V 5330 2950 50  0000 C CNN
F 1 "270" V 5250 2950 50  0000 C CNN
	1    5250 2950
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4C9A32C5
P 4700 2950
F 0 "R2" V 4780 2950 50  0000 C CNN
F 1 "270" V 4700 2950 50  0000 C CNN
	1    4700 2950
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4C9A308B
P 4300 2950
F 0 "R1" V 4380 2950 50  0000 C CNN
F 1 "270" V 4300 2950 50  0000 C CNN
	1    4300 2950
	1    0    0    -1  
$EndComp
$EndSCHEMATC
