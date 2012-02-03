#include "ADCw.h"

ADCw::ADCw()
{
	BUFFER_OFFSET = 8;					//Ignore first 16 samples
	ADC_SPI_CLKDIV=ADC_SPI_CLKDIV_MAX;  //Set clock to minimum speed
	BUFFER_LEN=16;
	MUX_CHANNELS =0;

	ADCBuffer = jz_adc_init();

	//Clean FPGA RAM memory
	for (int i = 0; i < 512; i++)     //RAMB16_s9_s9 has 2048 bytes 8-bit
	{
		ADCBuffer[i] = 0x00000000; //Clean 4 register by cicle
	}

	adcConfig(ADC_CMD_SET_SPI_CLKDIV);
	adcConfig(ADC_CMD_SET_FAST_CONV);
	printf("\nADC in Fast Convertion Mode (10us) and Fs=9.8KHz (Min)\n");
}

void ADCw::testADC()
{
	/******************************* TEST 1 ***********************************/
	printf("\nINIT TEST1: Autoselft {(Vref+) - (Vref-)}/2 -> Return 0x0200 \n");
	adcConfig(ADC_CMD_SET_AUTOSELFT_1);
	adcConfig(ADC_CMD_READ_AUTOSELFT_1);
	for(int i=BUFFER_OFFSET; i< BUFFER_LEN/2+BUFFER_OFFSET; i++)
		printf("[%08X]", ADCBuffer[i]);
	fflush (stdout);

	/******************************* TEST 2 ***********************************/
	printf("\n\nINIT TEST2: Autoselft (Vref-) -> Return 0x0000 \n");
	adcConfig(ADC_CMD_SET_AUTOSELFT_2);
	adcConfig(ADC_CMD_READ_AUTOSELFT_2);
	for(int i=BUFFER_OFFSET; i< BUFFER_LEN/2+BUFFER_OFFSET; i++)
		printf("[%08X]", ADCBuffer[i]);
	fflush (stdout);

	/******************************* TEST 3 ***********************************/
	printf("\n\nINIT TEST3: Autoselft (Vref+) -> Return 0x03FF \n");
	adcConfig(ADC_CMD_SET_AUTOSELFT_3);
	adcConfig(ADC_CMD_READ_AUTOSELFT_3);
	for(int i=BUFFER_OFFSET; i< BUFFER_LEN/2+BUFFER_OFFSET; i++)
		printf("[%08X]", ADCBuffer[i]);
	fflush (stdout);

	printf("\n\nTESTS complete\n");
}

void ADCw::powerDownADC()
{
	adcConfig(ADC_CMD_SET_POWER_DOWN);
	printf("\nADC in Power Down Mode \n");
}

JZ_REG* ADCw::takeSamplesADC(int CHANNEL)
{
	adcConfig(ADC_CMD_SET_CHANNEL0+CHANNEL);
	adcConfig(ADC_CMD_READ_CHANNEL0+CHANNEL);
	return (JZ_REG*)(ADCBuffer+BUFFER_OFFSET);
}

void ADCw::adcConfig(uchar CMD)
{
	ADCBuffer[0] =  (((MUX_CHANNELS<<6) + CMD)<<24) + \
					((BUFFER_LEN+BUFFER_OFFSET*2) << 8) + \
					(ADC_SPI_CLKDIV);
	while(adcCheckBufferFull()) usleep (10);
}

int ADCw::adcCheckBufferFull()
{
	return ADCBuffer[0]&0x20000000;
}
