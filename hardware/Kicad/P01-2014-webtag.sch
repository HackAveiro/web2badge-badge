EESchema Schematic File Version 2
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
LIBS:P01-2014-webtag-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "P01-2014- WebTag - Schematic"
Date "22 aug 2014"
Rev "0.1"
Comp "Aveiro Makers"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ARDUINO_PRO_MINI P?
U 1 1 53F6948B
P 5650 2250
F 0 "P?" H 5650 3100 70  0000 C CNN
F 1 "ARDUINO_PRO_MINI" H 5650 1400 70  0000 C CNN
F 2 "" H 5650 2250 60  0000 C CNN
F 3 "" H 5650 2250 60  0000 C CNN
	1    5650 2250
	1    0    0    -1  
$EndComp
$Comp
L CONN_8 P?
U 1 1 53F6949A
P 6950 3950
F 0 "P?" V 6900 3950 60  0000 C CNN
F 1 "5110LCD" V 7000 3950 60  0000 C CNN
F 2 "" H 6950 3950 60  0000 C CNN
F 3 "" H 6950 3950 60  0000 C CNN
	1    6950 3950
	1    0    0    -1  
$EndComp
Text Notes 4650 2200 0    60   ~ 0
chip select 5110
Text Notes 4500 2100 0    60   ~ 0
data/command
Text Notes 4700 2300 0    60   ~ 0
RST_5110
$Comp
L CONN_2 P?
U 1 1 53F6961C
P 6750 1000
F 0 "P?" V 6700 1000 40  0000 C CNN
F 1 "BATT" V 6800 1000 40  0000 C CNN
F 2 "" H 6750 1000 60  0000 C CNN
F 3 "" H 6750 1000 60  0000 C CNN
	1    6750 1000
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 53F69655
P 6650 1500
F 0 "#PWR?" H 6650 1500 30  0001 C CNN
F 1 "GND" H 6650 1430 30  0001 C CNN
F 2 "" H 6650 1500 60  0000 C CNN
F 3 "" H 6650 1500 60  0000 C CNN
	1    6650 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 53F69684
P 6600 4700
F 0 "#PWR?" H 6600 4700 30  0001 C CNN
F 1 "GND" H 6600 4630 30  0001 C CNN
F 2 "" H 6600 4700 60  0000 C CNN
F 3 "" H 6600 4700 60  0000 C CNN
	1    6600 4700
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 53F69693
P 5950 4100
F 0 "#PWR?" H 5950 4200 30  0001 C CNN
F 1 "VCC" H 5950 4200 30  0000 C CNN
F 2 "" H 5950 4100 60  0000 C CNN
F 3 "" H 5950 4100 60  0000 C CNN
	1    5950 4100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 53F696A2
P 4550 1750
F 0 "#PWR?" H 4550 1750 30  0001 C CNN
F 1 "GND" H 4550 1680 30  0001 C CNN
F 2 "" H 4550 1750 60  0000 C CNN
F 3 "" H 4550 1750 60  0000 C CNN
	1    4550 1750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 53F696B1
P 6550 2600
F 0 "#PWR?" H 6550 2700 30  0001 C CNN
F 1 "VCC" H 6550 2700 30  0000 C CNN
F 2 "" H 6550 2600 60  0000 C CNN
F 3 "" H 6550 2600 60  0000 C CNN
	1    6550 2600
	1    0    0    -1  
$EndComp
Text Notes 6650 4600 0    60   ~ 0
This should be PWMed to\n save power/control \nbacklight brightness
Text Notes 7950 4100 0    60   ~ 0
pwm brightness \ncontrol option
$Comp
L CONN_4X2 P?
U 1 1 53F69AEC
P 2900 3400
F 0 "P?" H 2900 3650 50  0000 C CNN
F 1 "nrf24l01" V 2900 3400 40  0000 C CNN
F 2 "" H 2900 3400 60  0000 C CNN
F 3 "" H 2900 3400 60  0000 C CNN
	1    2900 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 53F69B07
P 2250 3200
F 0 "#PWR?" H 2250 3200 30  0001 C CNN
F 1 "GND" H 2250 3130 30  0001 C CNN
F 2 "" H 2250 3200 60  0000 C CNN
F 3 "" H 2250 3200 60  0000 C CNN
	1    2250 3200
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 53F69B16
P 3300 3100
F 0 "#PWR?" H 3300 3200 30  0001 C CNN
F 1 "VCC" H 3300 3200 30  0000 C CNN
F 2 "" H 3300 3100 60  0000 C CNN
F 3 "" H 3300 3100 60  0000 C CNN
	1    3300 3100
	1    0    0    -1  
$EndComp
Text Notes 4450 2400 0    60   ~ 0
Chip enable nrf
Wire Wire Line
	4900 3000 5050 3000
Wire Wire Line
	5050 2800 4750 2800
Wire Wire Line
	4750 2800 4750 3900
Wire Wire Line
	4550 2100 5050 2100
Wire Wire Line
	4350 2200 5050 2200
Wire Wire Line
	5050 2300 4650 2300
Wire Wire Line
	6600 4300 6600 4700
Wire Wire Line
	5950 4100 6600 4100
Connection ~ 6600 4600
Wire Wire Line
	6250 2600 6550 2600
Wire Wire Line
	5050 1800 4800 1800
Wire Wire Line
	4800 1800 4800 1650
Wire Wire Line
	4800 1650 4550 1650
Wire Wire Line
	4550 1650 4550 1750
Wire Wire Line
	6850 1350 6850 2300
Wire Wire Line
	6850 2300 6250 2300
Wire Wire Line
	6650 1350 6650 1500
Wire Wire Line
	5050 2700 4850 2700
Wire Wire Line
	4850 2700 4850 3250
Wire Wire Line
	4850 3250 8200 3250
Wire Wire Line
	8200 3250 8200 4000
Wire Wire Line
	8200 4000 7900 4000
Wire Wire Line
	3300 3250 3300 3100
Wire Wire Line
	2500 3250 2500 3100
Wire Wire Line
	2500 3100 2250 3100
Wire Wire Line
	2250 3100 2250 3200
Wire Wire Line
	5050 2400 4450 2400
Wire Wire Line
	4450 2400 4450 4450
Wire Wire Line
	4450 4450 1750 4450
Wire Wire Line
	1750 4450 1750 3350
Wire Wire Line
	1750 3350 2500 3350
Wire Wire Line
	3300 3450 4750 3450
Connection ~ 4750 3450
Wire Wire Line
	2500 3550 2350 3550
Wire Wire Line
	2350 3550 2350 3700
Wire Wire Line
	2350 3700 4950 3700
Wire Wire Line
	4950 3700 4950 2900
Wire Wire Line
	4950 2900 5050 2900
Wire Wire Line
	2500 3450 2250 3450
Wire Wire Line
	2250 3450 2250 4000
Wire Wire Line
	3300 3550 3600 3550
Wire Wire Line
	3600 3550 3600 1900
Wire Wire Line
	3600 1900 5050 1900
Text Notes 3800 1900 0    60   ~ 0
IRQ
Wire Wire Line
	3300 3350 4700 3350
Wire Wire Line
	4700 3350 4700 2600
Wire Wire Line
	4700 2600 5050 2600
Text Notes 4750 2600 0    60   ~ 0
CSN
Wire Notes Line
	1650 5200 1650 6900
Wire Notes Line
	1650 6900 6300 6900
Wire Notes Line
	6300 6900 6300 5200
Wire Notes Line
	6300 5200 1650 5200
Text Notes 1850 5400 0    60   ~ 12
PINOUT ARDUINO - 
Text Label 6050 3700 0    60   ~ 0
chipselect
Text Label 6250 3600 0    60   ~ 0
reset
Text Label 5800 3800 0    60   ~ 0
data/command
Text Label 4800 2800 0    60   ~ 0
DIN
Text Label 6350 4000 0    60   ~ 0
SCLK
Wire Wire Line
	3950 3600 6600 3600
Wire Wire Line
	4350 2200 4350 3200
Wire Wire Line
	4350 3200 5300 3200
Wire Wire Line
	5300 3200 5300 3700
Wire Wire Line
	5300 3700 6600 3700
Wire Wire Line
	4550 2100 4550 3800
Wire Wire Line
	4550 3800 6600 3800
Wire Wire Line
	2250 4000 6600 4000
Wire Wire Line
	4900 3000 4900 4000
Connection ~ 4900 4000
Wire Wire Line
	4750 3900 6600 3900
Wire Wire Line
	4650 2300 4650 3050
Wire Wire Line
	4650 3050 3950 3050
Wire Wire Line
	5050 2500 4250 2500
Wire Wire Line
	4250 2500 4250 4200
Wire Wire Line
	4250 4200 6600 4200
Text Label 6150 4200 0    60   ~ 0
PWMLCD
Wire Wire Line
	3950 3050 3950 3600
$EndSCHEMATC
