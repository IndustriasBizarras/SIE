/* ADC Peripheral.c

Copyright (C) 2010

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <stdio.h>
#include <unistd.h>

#include "jz_adc_peripheral.h"

void ADCTest(JZ_REG * ADCBuffer)
{
if(ADCBuffer!=0)
{
    int aggregate=0; float errorT=0;
    /******************************* TEST 1 ***********************************/
	printf("\nINIT TEST1: Autoselft {(Vref+) - (Vref-)}/2 -> Return 0x0200 \n");
	ADCConfig(ADCBuffer,ADC_CMD_SET_AUTOSELFT_1);
	ADCConfig(ADCBuffer,ADC_CMD_READ_AUTOSELFT_1);
	for(int i=ADC_BUFFER_OFFSET; i< ADC_BUFFER_LEN/2+ADC_BUFFER_OFFSET; i++)
    {
        aggregate += (ADCBuffer[i]&0xFFFF + ((ADCBuffer[i]>>16)&0x0FFF));
		printf("[%08X]", ADCBuffer[i]);
    }
    errorT=(aggregate/16)*100/0x200;
    if((errorT<95)||(errorT>105))
        printf("\n**WARNING** Test FAILED.\n\n");
    else
        printf("\nTest OK\n\n");

	fflush (stdout);
}
}

void ADCPowerDown(JZ_REG * ADCBuffer)
{
	ADCConfig(ADCBuffer,ADC_CMD_SET_POWER_DOWN);
}

JZ_REG * ADCTakeSamples(JZ_REG * ADCBuffer,int CHANNEL)
{
	ADCConfig(ADCBuffer,ADC_CMD_SET_CHANNEL0+CHANNEL);
	ADCConfig(ADCBuffer,ADC_CMD_READ_CHANNEL0+CHANNEL);
	return (JZ_REG*)(ADCBuffer+ADC_BUFFER_OFFSET);
}

void ADCConfig(JZ_REG * ADCBuffer,uchar CMD)
{
	if(ADCBuffer!=0)
	{
		ADCBuffer[0] =  (((ADC_MUX_CHANNELS<<6) + CMD)<<24) + \
				((ADC_BUFFER_LEN+ADC_BUFFER_OFFSET*2) << 8) + \
				(ADC_SPI_CLKDIV);
		while(ADCCheckBufferFull(ADCBuffer)) usleep (10);	
	}
}

int ADCCheckBufferFull(JZ_REG * ADCBuffer)
{
	if(ADCBuffer!=0)
	{
		return ADCBuffer[0]&0x20000000;
	}
	return 0;
}
