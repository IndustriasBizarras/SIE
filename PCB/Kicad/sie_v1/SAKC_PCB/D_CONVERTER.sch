EESchema Schematic File Version 2  date Fri 23 Apr 2010 12:32:33 PM COT
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves,./SAKC.cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 5 9
Title ""
Date "23 feb 2010"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 6600 2900 1    20   BiDi ~ 0
GND
Text HLabel 6000 2600 2    20   BiDi ~ 0
ANALOG[0..7]
Wire Bus Line
	6000 2600 5950 2600
Wire Bus Line
	5950 2600 5950 2200
Wire Wire Line
	5850 2400 5400 2400
Wire Wire Line
	5850 2300 5400 2300
Wire Wire Line
	5850 2200 5400 2200
Wire Wire Line
	5850 2100 5400 2100
Connection ~ 5600 2700
Wire Wire Line
	5600 2700 5700 2700
Wire Wire Line
	6600 2900 6600 2800
Wire Wire Line
	6600 2800 6550 2800
Connection ~ 5600 2800
Connection ~ 4250 2100
Wire Wire Line
	4250 2050 4250 2150
Wire Wire Line
	4400 2300 4250 2300
Wire Wire Line
	4400 2400 4250 2400
Wire Wire Line
	4400 2600 4250 2600
Wire Wire Line
	5600 2550 5600 2600
Wire Wire Line
	5600 2600 5400 2600
Wire Wire Line
	5400 2650 5600 2650
Wire Wire Line
	5600 2650 5600 2950
Wire Wire Line
	5600 2950 4900 2950
Wire Wire Line
	4400 2650 4250 2650
Wire Wire Line
	4400 2450 4250 2450
Wire Wire Line
	4400 2350 4250 2350
Wire Wire Line
	4250 2150 4400 2150
Wire Wire Line
	4400 2100 4250 2100
Wire Wire Line
	4900 1900 4900 1850
Wire Wire Line
	5950 2800 5600 2800
Wire Wire Line
	3750 2000 3750 1800
Wire Wire Line
	5850 2150 5400 2150
Wire Wire Line
	5850 2250 5400 2250
Wire Wire Line
	5850 2350 5400 2350
Wire Wire Line
	5850 2450 5400 2450
Entry Wire Line
	5850 2450 5950 2550
Entry Wire Line
	5850 2400 5950 2500
Entry Wire Line
	5850 2350 5950 2450
Entry Wire Line
	5850 2300 5950 2400
Entry Wire Line
	5850 2250 5950 2350
Entry Wire Line
	5850 2200 5950 2300
Entry Wire Line
	5850 2150 5950 2250
Entry Wire Line
	5850 2100 5950 2200
Text Label 5600 2450 2    20   ~ 0
ANALOG7
Text Label 5600 2400 2    20   ~ 0
ANALOG6
Text Label 5600 2350 2    20   ~ 0
ANALOG5
Text Label 5600 2300 2    20   ~ 0
ANALOG4
Text Label 5600 2250 2    20   ~ 0
ANALOG3
Text Label 5600 2200 2    20   ~ 0
ANALOG2
Text Label 5600 2150 2    20   ~ 0
ANALOG1
Text Label 5600 2100 2    20   ~ 0
ANALOG0
Text GLabel 5600 2550 2    20   BiDi ~ 0
3.3V
Text GLabel 4900 1850 3    20   BiDi ~ 0
3.3V
Text GLabel 4250 2050 3    20   BiDi ~ 0
3.3V
Text GLabel 3750 2000 1    20   BiDi ~ 0
3.3V
Text HLabel 3750 1800 3    20   BiDi ~ 0
3.3V
Text HLabel 5700 2700 2    20   BiDi ~ 0
AN_GND
Text HLabel 4250 2300 0    20   BiDi ~ 0
ADC_EOC
Text HLabel 4250 2350 0    20   BiDi ~ 0
ADC_CS
Text HLabel 4250 2400 0    20   BiDi ~ 0
ADC_CSTART
Text HLabel 4250 2450 0    20   BiDi ~ 0
ADC_SCLK
Text HLabel 4250 2600 0    20   BiDi ~ 0
ADC_SDIN
Text HLabel 4250 2650 0    20   BiDi ~ 0
ADC_SDOUT
$Comp
L INDUCTOR L12
U 1 1 4B7C62AC
P 6250 2800
F 0 "L12" V 6200 2800 40  0000 C CNN
F 1 "HZ0805C202R-00" V 6350 2800 40  0000 C CNN
	1    6250 2800
	0    -1   -1   0   
$EndComp
$Comp
L TLV1548 U11
U 1 1 4B7C620D
P 4700 2900
F 0 "U11" H 4550 3800 60  0000 C CNN
F 1 "TLV1548" H 4700 2900 40  0000 C CNN
	1    4700 2900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
