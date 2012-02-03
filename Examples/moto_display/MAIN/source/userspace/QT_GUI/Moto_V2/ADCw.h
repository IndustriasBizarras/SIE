#ifndef ADCW_H
#define ADCW_H

#include "jz_adc_peripheral.h"
#include <stdio.h>
#include <unistd.h>

class ADCw
{
public:
	ADCw();
	~ADCw(){}

	void testADC();
	void powerDownADC();
	JZ_REG * takeSamplesADC(int CHANNEL);
	void setClockDiv(uchar value){ ADC_SPI_CLKDIV = value;}
	void setBufferLen(int  value){ BUFFER_LEN = value;}
	void setMuxChannels(uchar value){ MUX_CHANNELS = value;}
private:	
	void adcConfig(uchar CMD);
	int adcCheckBufferFull();

	JZ_REG * ADCBuffer;
	uchar ADC_SPI_CLKDIV;
	int BUFFER_LEN;
	int BUFFER_OFFSET;
	uchar MUX_CHANNELS;
};

#endif // ADCW_H
