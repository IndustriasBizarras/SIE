EESchema Schematic File Version 2  date Sat 23 Apr 2011 04:32:10 PM COT
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "23 apr 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 7400 7550 0    60   ~ 0
Keyboard
Text Label 8050 4200 0    60   ~ 0
GND
Wire Wire Line
	7950 4200 8050 4200
Wire Wire Line
	5850 4400 5950 4400
Wire Wire Line
	5100 4400 5200 4400
Wire Wire Line
	5100 3850 5200 3850
Wire Wire Line
	5850 3850 5950 3850
Wire Wire Line
	7400 4700 7550 4700
Wire Wire Line
	6950 4200 7050 4200
Wire Wire Line
	7400 3700 7500 3700
Wire Wire Line
	3650 4500 3800 4500
Wire Wire Line
	3650 4300 3800 4300
Wire Wire Line
	3650 4100 3800 4100
Wire Wire Line
	3650 3900 3800 3900
Wire Wire Line
	3650 3700 3800 3700
Wire Wire Line
	3650 3800 3800 3800
Wire Wire Line
	3650 4000 3800 4000
Wire Wire Line
	3650 4200 3800 4200
Wire Wire Line
	3650 4400 3800 4400
Wire Wire Line
	7200 3500 7100 3500
Wire Wire Line
	6750 4000 6650 4000
Wire Wire Line
	7200 4500 7100 4500
Wire Wire Line
	5650 3650 5550 3650
Wire Wire Line
	4900 3650 4800 3650
Wire Wire Line
	4900 4200 4800 4200
Wire Wire Line
	5550 4200 5650 4200
Wire Wire Line
	7750 4000 7650 4000
Text Label 7550 4700 0    60   ~ 0
GND
Text Label 7100 4500 2    60   ~ 0
DOWN
Text Label 7650 4000 2    60   ~ 0
RIGHT
Text Label 7050 4200 0    60   ~ 0
GND
Text Label 6650 4000 2    60   ~ 0
LEFT
Text Label 7500 3700 0    60   ~ 0
GND
Text Label 7100 3500 2    60   ~ 0
UP
Text Label 5950 4400 0    60   ~ 0
GND
Text Label 5550 4200 2    60   ~ 0
VOL_DW
Text Label 5200 4400 0    60   ~ 0
GND
Text Label 4800 4200 2    60   ~ 0
ENTER
Text Label 5950 3850 0    60   ~ 0
GND
Text Label 5550 3650 2    60   ~ 0
VOL_UP
Text Label 5200 3850 0    60   ~ 0
GND
Text Label 4800 3650 2    60   ~ 0
MFB
Text Label 3800 4500 0    60   ~ 0
GND
Text Label 3800 4400 0    60   ~ 0
ENTER
Text Label 3800 4300 0    60   ~ 0
RIGHT
Text Label 3800 4200 0    60   ~ 0
LEFT
Text Label 3800 4100 0    60   ~ 0
DOWN
Text Label 3800 4000 0    60   ~ 0
UP
Text Label 3800 3900 0    60   ~ 0
VOL_DW
Text Label 3800 3800 0    60   ~ 0
VOL_UP
Text Label 3800 3700 0    60   ~ 0
MFB
$Comp
L SW_PUSH_SMALL SW2
U 1 1 4DB321BA
P 5000 4300
F 0 "SW2" H 5150 4410 30  0000 C CNN
F 1 "ENTER" H 5000 4221 30  0000 C CNN
	1    5000 4300
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW8
U 1 1 4DB32171
P 7850 4100
F 0 "SW8" H 8000 4210 30  0000 C CNN
F 1 "RIGHT" H 7850 4021 30  0000 C CNN
	1    7850 4100
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW5
U 1 1 4DB3216D
P 6850 4100
F 0 "SW5" H 7000 4210 30  0000 C CNN
F 1 "LEFT" H 6850 4021 30  0000 C CNN
	1    6850 4100
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW7
U 1 1 4DB32169
P 7300 4600
F 0 "SW7" H 7450 4710 30  0000 C CNN
F 1 "DOWN" H 7300 4521 30  0000 C CNN
	1    7300 4600
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW6
U 1 1 4DB32166
P 7300 3600
F 0 "SW6" H 7450 3710 30  0000 C CNN
F 1 "UP" H 7300 3521 30  0000 C CNN
	1    7300 3600
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW4
U 1 1 4DB32162
P 5750 4300
F 0 "SW4" H 5900 4410 30  0000 C CNN
F 1 "VOL_DW" H 5750 4221 30  0000 C CNN
	1    5750 4300
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW3
U 1 1 4DB3215E
P 5750 3750
F 0 "SW3" H 5900 3860 30  0000 C CNN
F 1 "VOL_UP" H 5750 3671 30  0000 C CNN
	1    5750 3750
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW1
U 1 1 4DB32150
P 5000 3750
F 0 "SW1" H 5150 3860 30  0000 C CNN
F 1 "MFB" H 5000 3671 30  0000 C CNN
	1    5000 3750
	1    0    0    -1  
$EndComp
$Comp
L CONN_9 P1
U 1 1 4DB3212D
P 3300 4100
F 0 "P1" V 3250 4100 60  0000 C CNN
F 1 "CONN_9" V 3350 4100 60  0000 C CNN
	1    3300 4100
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
