EESchema Schematic File Version 2  date Fri 23 Apr 2010 12:32:33 PM COT
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves,./SAKC.cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 2 9
Title ""
Date "23 feb 2010"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1250 1750 1250 1950
Connection ~ 5550 5950
Wire Wire Line
	5150 5950 5950 5950
Wire Wire Line
	4050 5150 4050 5300
Wire Wire Line
	5550 6650 5550 7050
Connection ~ 5150 5300
Wire Wire Line
	4800 5300 6400 5300
Wire Wire Line
	5950 5300 5950 5450
Wire Wire Line
	10200 2140 10200 2300
Wire Wire Line
	10200 2800 10200 2700
Connection ~ 9280 2300
Wire Wire Line
	9280 2360 9280 2300
Wire Wire Line
	1100 1950 1100 1750
Wire Wire Line
	1000 1950 1000 1750
Wire Wire Line
	850  1950 850  1750
Wire Wire Line
	2300 3800 2300 3600
Wire Wire Line
	8225 2200 8000 2200
Connection ~ 9350 5450
Wire Wire Line
	9350 5350 9350 5500
Wire Wire Line
	5900 2150 5900 2250
Wire Wire Line
	7900 2400 7900 2300
Connection ~ 4100 2300
Wire Wire Line
	4250 2300 3800 2300
Wire Wire Line
	7800 5700 7800 5450
Wire Wire Line
	7800 5450 8350 5450
Wire Wire Line
	9000 5450 9350 5450
Wire Wire Line
	2100 3600 2200 3600
Wire Wire Line
	2200 3600 2200 3800
Wire Wire Line
	5050 4100 5050 4250
Wire Wire Line
	4250 3500 4250 3650
Wire Wire Line
	4250 3500 5050 3500
Wire Wire Line
	5050 3500 5050 3700
Wire Wire Line
	9025 2200 8875 2200
Wire Wire Line
	5000 2400 5000 2350
Wire Wire Line
	5000 2350 5100 2350
Wire Wire Line
	5900 2350 5900 2300
Wire Wire Line
	3000 2300 2900 2300
Wire Wire Line
	3800 2200 4000 2200
Wire Wire Line
	4100 2700 4100 2800
Wire Wire Line
	3150 2200 2900 2200
Wire Wire Line
	5900 2250 6000 2250
Wire Wire Line
	6500 2700 6500 2800
Wire Wire Line
	5250 2250 5000 2250
Wire Wire Line
	2900 2300 2900 2350
Wire Wire Line
	7900 2300 8075 2300
Wire Wire Line
	4250 3650 3150 3650
Connection ~ 3600 3650
Wire Wire Line
	4250 4050 4250 4200
Wire Wire Line
	2300 3600 2350 3600
Wire Wire Line
	9350 6050 9350 5900
Wire Wire Line
	8350 5500 8050 5500
Wire Wire Line
	8050 5500 8050 5400
Wire Wire Line
	8350 5400 7850 5400
Wire Wire Line
	7850 5400 7850 5350
Connection ~ 8050 5400
Wire Wire Line
	5900 2300 6750 2300
Connection ~ 6500 2300
Wire Wire Line
	9425 2300 8875 2300
Wire Wire Line
	8875 2200 8875 2100
Wire Wire Line
	9100 5350 9100 5450
Connection ~ 9100 5450
Connection ~ 2300 3600
Wire Wire Line
	800  1750 800  1950
Wire Wire Line
	900  1750 900  1950
Wire Wire Line
	950  1750 950  1950
Wire Wire Line
	1050 1750 1050 1950
Wire Wire Line
	3600 4200 3600 4050
Wire Wire Line
	9280 2810 9280 2760
Wire Wire Line
	1150 1950 1150 1750
Wire Wire Line
	1200 1950 1200 1750
Wire Wire Line
	10200 3300 10200 3400
Wire Wire Line
	5150 5300 5150 5350
Connection ~ 5950 5300
Wire Wire Line
	4050 5300 4400 5300
Wire Wire Line
	6400 5300 6400 5200
Wire Wire Line
	5150 5950 5150 5850
Wire Wire Line
	5550 5950 5550 6050
Wire Wire Line
	5950 5950 5950 5850
Text HLabel 1250 1750 3    20   BiDi ~ 0
VRTC
Text GLabel 1250 1950 1    20   BiDi ~ 0
VRTC
Text GLabel 6400 5200 3    20   BiDi ~ 0
VRTC
Text GLabel 4050 5150 3    20   BiDi ~ 0
3.3V
Text GLabel 5550 7050 1    20   BiDi ~ 0
GND
$Comp
L DIODE D9
U 1 1 4BD1CA91
P 5950 5650
F 0 "D9" H 5950 5750 40  0000 C CNN
F 1 "CDBU0130L" H 5950 5550 40  0000 C CNN
	1    5950 5650
	0    -1   -1   0   
$EndComp
$Comp
L R R34
U 1 1 4BD1CA30
P 5150 5600
F 0 "R34" V 5230 5600 50  0000 C CNN
F 1 "1K" V 5150 5600 50  0000 C CNN
	1    5150 5600
	1    0    0    -1  
$EndComp
$Comp
L DIODE D8
U 1 1 4BD1CA19
P 4600 5300
F 0 "D8" H 4600 5400 40  0000 C CNN
F 1 "CDBU0130L" H 4600 5200 40  0000 C CNN
	1    4600 5300
	1    0    0    -1  
$EndComp
$Comp
L BATTERY BT1
U 1 1 4BD1C7FC
P 5550 6350
F 0 "BT1" V 5450 5850 50  0000 C CNN
F 1 "BATTERY" V 5550 5950 50  0000 C CNN
	1    5550 6350
	0    1    1    0   
$EndComp
Text GLabel 10200 2140 3    20   BiDi ~ 0
3.3V
Text GLabel 10200 3400 1    20   BiDi ~ 0
GND
$Comp
L R R31
U 1 1 4BA5068A
P 10200 3050
F 0 "R31" V 10280 3050 50  0000 C CNN
F 1 "1K" V 10200 3050 50  0000 C CNN
	1    10200 3050
	1    0    0    -1  
$EndComp
$Comp
L LED D7
U 1 1 4BA50684
P 10200 2500
F 0 "D7" H 10200 2600 50  0000 C CNN
F 1 "LED" H 10200 2400 50  0000 C CNN
	1    10200 2500
	0    1    1    0   
$EndComp
Text GLabel 7900 2400 1    20   BiDi ~ 0
GND
Text GLabel 1200 1950 1    20   BiDi ~ 0
GND
Text HLabel 1200 1750 3    20   BiDi ~ 0
GND
Text GLabel 1150 1950 1    20   BiDi ~ 0
BAT_V
Text HLabel 1150 1750 3    20   BiDi ~ 0
BAT_V
Text GLabel 9350 6050 1    20   BiDi ~ 0
GND
Text GLabel 7800 5700 1    20   BiDi ~ 0
GND
$Comp
L C C57
U 1 1 4BA2EDEC
P 9280 2560
F 0 "C57" H 9330 2660 50  0000 L CNN
F 1 "100n" H 9330 2460 50  0000 L CNN
	1    9280 2560
	1    0    0    -1  
$EndComp
Text GLabel 9280 2810 1    20   BiDi ~ 0
GND
Text GLabel 2100 3600 0    20   BiDi ~ 0
GND
Text GLabel 5050 4250 1    20   BiDi ~ 0
GND
Text GLabel 4250 4200 1    20   BiDi ~ 0
GND
Text GLabel 3600 4200 1    20   BiDi ~ 0
GND
Text GLabel 6500 2800 1    20   BiDi ~ 0
GND
Text GLabel 5000 2400 1    20   BiDi ~ 0
GND
Text GLabel 4100 2800 1    20   BiDi ~ 0
GND
Text GLabel 2900 2350 1    20   BiDi ~ 0
GND
Text GLabel 2350 3600 2    20   BiDi ~ 0
BAT_V
Text GLabel 3150 3650 0    20   BiDi ~ 0
BAT_V
Text GLabel 7850 5350 3    20   BiDi ~ 0
3.3V
Text GLabel 9100 5350 3    20   BiDi ~ 0
2V5
Text GLabel 9350 5350 3    20   BiDi ~ 0
2.5V
Text GLabel 9425 2300 2    20   BiDi ~ 0
1.2V
Text GLabel 9025 2200 2    20   BiDi ~ 0
1.2V
Text GLabel 8875 2100 3    20   BiDi ~ 0
1V2
Text GLabel 8000 2200 0    20   BiDi ~ 0
BAT_V
Text GLabel 6750 2300 2    20   BiDi ~ 0
3.3V
Text GLabel 6000 2250 2    20   BiDi ~ 0
3.3V
Text GLabel 5900 2150 3    20   BiDi ~ 0
3V3
Text GLabel 5000 2250 0    20   BiDi ~ 0
BAT_V
Text GLabel 4250 2300 2    20   BiDi ~ 0
1.8v
Text GLabel 4000 2200 2    20   BiDi ~ 0
1.8v
Text GLabel 2900 2200 0    20   BiDi ~ 0
BAT_V
Text GLabel 1100 1950 1    20   BiDi ~ 0
2V5
Text GLabel 1050 1950 1    20   BiDi ~ 0
2.5V
Text GLabel 1000 1950 1    20   BiDi ~ 0
1V2
Text GLabel 950  1950 1    20   BiDi ~ 0
1.2V
Text GLabel 900  1950 1    20   BiDi ~ 0
1.8V
Text GLabel 850  1950 1    20   BiDi ~ 0
3V3
Text GLabel 800  1950 1    20   BiDi ~ 0
3.3V
Text HLabel 1100 1750 3    20   BiDi ~ 0
2V5
Text HLabel 1050 1750 3    20   BiDi ~ 0
2.5V
Text HLabel 1000 1750 3    20   BiDi ~ 0
1V2
Text HLabel 950  1750 3    20   BiDi ~ 0
1.2V
Text HLabel 900  1750 3    20   BiDi ~ 0
1.8V
Text HLabel 850  1750 3    20   BiDi ~ 0
3V3
Text HLabel 800  1750 3    20   BiDi ~ 0
3.3V
$Comp
L LT1117CST U10
U 1 1 4B7C6C38
P 8575 2400
F 0 "U10" H 8425 2700 60  0000 C CNN
F 1 "LT1117CST-1.2" H 8575 2400 40  0000 C CNN
	1    8575 2400
	1    0    0    -1  
$EndComp
$Comp
L HOLE J14
U 1 1 4B7C701D
P 8900 3900
F 0 "J14" H 8800 4200 60  0000 C CNN
F 1 "HOLE4" H 8900 3900 60  0000 C CNN
	1    8900 3900
	1    0    0    -1  
$EndComp
$Comp
L HOLE J13
U 1 1 4B7C701B
P 8250 3900
F 0 "J13" H 8150 4200 60  0000 C CNN
F 1 "HOLE3" H 8250 3900 60  0000 C CNN
	1    8250 3900
	1    0    0    -1  
$EndComp
$Comp
L HOLE J12
U 1 1 4B7C7019
P 7650 3900
F 0 "J12" H 7550 4200 60  0000 C CNN
F 1 "HOLE1" H 7650 3900 60  0000 C CNN
	1    7650 3900
	1    0    0    -1  
$EndComp
$Comp
L HOLE J11
U 1 1 4B7C7014
P 7000 3900
F 0 "J11" H 6900 4200 60  0000 C CNN
F 1 "HOLE1" H 7000 3900 60  0000 C CNN
	1    7000 3900
	1    0    0    -1  
$EndComp
NoConn ~ 9000 5500
$Comp
L C C60
U 1 1 4B7C6CC3
P 9350 5700
F 0 "C60" H 9400 5800 50  0000 L CNN
F 1 "100n" H 9400 5600 50  0000 L CNN
	1    9350 5700
	1    0    0    -1  
$EndComp
$Comp
L C C42
U 1 1 4B7C6CBC
P 6500 2500
F 0 "C42" H 6550 2600 50  0000 L CNN
F 1 "100n" H 6550 2400 50  0000 L CNN
	1    6500 2500
	1    0    0    -1  
$EndComp
$Comp
L C C41
U 1 1 4B7C6CBA
P 4100 2500
F 0 "C41" H 4150 2600 50  0000 L CNN
F 1 "100n" H 4150 2400 50  0000 L CNN
	1    4100 2500
	1    0    0    -1  
$EndComp
$Comp
L C C53
U 1 1 4B7C6CB7
P 3600 3850
F 0 "C53" H 3650 3950 50  0000 L CNN
F 1 "100n" H 3650 3750 50  0000 L CNN
	1    3600 3850
	1    0    0    -1  
$EndComp
$Comp
L C C56
U 1 1 4B7C6CB4
P 4250 3850
F 0 "C56" H 4300 3950 50  0000 L CNN
F 1 "10u" H 4300 3750 50  0000 L CNN
	1    4250 3850
	1    0    0    1   
$EndComp
$Comp
L C C54
U 1 1 4B7C6CB1
P 5050 3900
F 0 "C54" H 5100 4000 50  0000 L CNN
F 1 "100n" H 5100 3800 50  0000 L CNN
	1    5050 3900
	1    0    0    -1  
$EndComp
$Comp
L HEADER_2 J17
U 1 1 4B7C6CA6
P 2450 4100
F 0 "J17" H 2200 4300 60  0000 C CNN
F 1 "HEADER_2" H 2450 4100 60  0000 C CNN
	1    2450 4100
	0    -1   -1   0   
$EndComp
$Comp
L LT1117CST U7
U 1 1 4B7C6C99
P 3500 2400
F 0 "U7" H 3350 2700 60  0000 C CNN
F 1 "LT1117CST-1.8" H 3500 2400 40  0000 C CNN
	1    3500 2400
	1    0    0    -1  
$EndComp
$Comp
L LP3988IMF UF2
U 1 1 4B7C6C43
P 8650 5650
F 0 "UF2" H 8550 6000 60  0000 C CNN
F 1 "LP3988IMF-2.5/MIC5205-2.5YM5TR" H 8650 5650 30  0000 C CNN
	1    8650 5650
	1    0    0    -1  
$EndComp
$Comp
L LT1117CST U8
U 1 1 4B7C6C33
P 5600 2450
F 0 "U8" H 5450 2750 60  0000 C CNN
F 1 "LT1117CST-3.3" H 5600 2450 40  0000 C CNN
	1    5600 2450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
