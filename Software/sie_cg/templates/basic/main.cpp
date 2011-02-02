#include "jz_adc_peripheral.h"
#include "jz_fpga_init.h"
#include <stdio.h>
#include <unistd.h>

extern "C" 
{
  #include "fbutils.h"
}


JZ_REG * FPGA_ADDR;
JZ_REG * ADCBuffer;
bool frameBufferOpened = 0;
bool firstLoop = 1;

/***![HEADER SECTION]***/

/***![BLOCK SECTION]***/

/***![EXTRA SECTION]***/

int main()
{
	/* OPEN FRAME BUFFER */
	printf("Opening framebuffer...\n\n");

	if (open_framebuffer()) {
		close_framebuffer();
		printf("Could not open framebuffer!!\n\n");
	}
	else
	{	
		setColorsFromDefaultPallet();
		rect(0,0,xres,yres,0); //Extern Rect
    }
			   
	/* MAPING FPGA MEMORY */			   
	FPGA_ADDR=jz_cs2_init();
	ADCBuffer = FPGA_ADDR;
	ADCTest(ADCBuffer);
		
	
    /***![INIT SECTION]***/
    
    /***![IO SECTION]***/
    
    /***![MAIN SECTION]***/
    
    return 0;
}


