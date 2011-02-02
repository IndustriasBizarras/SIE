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




void FB_Print_Line38 ()
{
	
	if(1)
	{
		put_string_center (160,210,"By Juan64Bits", 1);
	}
	else
	{
		put_string (160,210,"By Juan64Bits", 1%5);
	}

}

void FB_Print_Line37 ()
{
	
	if(1)
	{
		put_string_center (160,200,"Segundo Semestre de 2010", 1);
	}
	else
	{
		put_string (160,200,"Segundo Semestre de 2010", 1%5);
	}

}

void FB_Print_Line36 ()
{
	
	if(1)
	{
		put_string_center (160,190,"Universidad Nacional de Colombia", 1);
	}
	else
	{
		put_string (160,190,"Universidad Nacional de Colombia", 1%5);
	}

}

void FB_Print_Line35 ()
{
	
	if(0)
	{
		put_string_center (0,156,"CHA [7]", 4);
	}
	else
	{
		put_string (0,156,"CHA [7]", 4%5);
	}

}

void FB_Print_Line10 ()
{
	
	if(0)
	{
		put_string_center (0,16,"CHA [0]", 4);
	}
	else
	{
		put_string (0,16,"CHA [0]", 4%5);
	}

}

void Constant_Bool1 ( bool &out_3)
{
	
	out_3=1;

}

void FB_Print_Line2 ()
{
	
	if(1)
	{
		put_string_center (160,0,"Wellcome to SIE {Executing Code...}", 1);
	}
	else
	{
		put_string (160,0,"Wellcome to SIE {Executing Code...}", 1%5);
	}

}

void ADC_Eight7 ( unsigned short int &out_8, unsigned short int &out_7, unsigned short int &out_6, unsigned short int &out_5, unsigned short int &out_4, unsigned short int &out_3, unsigned short int &out_2, unsigned short int &out_1)
{

	JZ_REG * ADC_DATA = ADCTakeSamples(ADCBuffer,0);
	unsigned int sampleData = ADC_DATA[0];
	out_1 = (sampleData>>16)&0xFFFF;
	out_2 = sampleData&0xFFFF;
	sampleData = ADC_DATA[1];
	out_3 = (sampleData>>16)&0xFFFF;
	out_4 = sampleData&0xFFFF;
	sampleData = ADC_DATA[2];
	out_5 = (sampleData>>16)&0xFFFF;
	out_6 = sampleData&0xFFFF;
	sampleData = ADC_DATA[3];
	out_7 = (sampleData>>16)&0xFFFF;
	out_8 = sampleData&0xFFFF;

}

void Right_Shift25 ( int in_0, int &out_1)
{

	out_1 = in_0 >> 2;
}

void FB_Draw_HLine11 ( unsigned short int in_3)
{
	if(!firstLoop)		// do nothing in first loop
	{
	   	fillrect(64,96,64+255,96+16,0); //Black Rect
		rect(64,96,64+255,96+16,3); //Extern Rect
		fillrect(64,96,64+(in_3%(255+1)),96+16,3);
	}

}

void FB_Put_Int18 ( int in_1)
{
	
	put_int(16,104,in_1,2);

}

void Right_Shift24 ( int in_0, int &out_1)
{

	out_1 = in_0 >> 2;
}

void FB_Draw_HLine6 ( unsigned short int in_3)
{
	if(!firstLoop)		// do nothing in first loop
	{
	   	fillrect(64,76,64+255,76+16,0); //Black Rect
		rect(64,76,64+255,76+16,3); //Extern Rect
		fillrect(64,76,64+(in_3%(255+1)),76+16,3);
	}

}

void FB_Put_Int17 ( int in_1)
{
	
	put_int(16,84,in_1,2);

}

void Right_Shift23 ( int in_0, int &out_1)
{

	out_1 = in_0 >> 2;
}

void FB_Draw_HLine4 ( unsigned short int in_3)
{
	if(!firstLoop)		// do nothing in first loop
	{
	   	fillrect(64,56,64+255,56+16,0); //Black Rect
		rect(64,56,64+255,56+16,3); //Extern Rect
		fillrect(64,56,64+(in_3%(255+1)),56+16,3);
	}

}

void FB_Put_Int16 ( int in_1)
{
	
	put_int(16,64,in_1,2);

}

void Right_Shift22 ( int in_0, int &out_1)
{

	out_1 = in_0 >> 2;
}

void FB_Draw_HLine0 ( unsigned short int in_3)
{
	if(!firstLoop)		// do nothing in first loop
	{
	   	fillrect(64,36,64+255,36+16,0); //Black Rect
		rect(64,36,64+255,36+16,3); //Extern Rect
		fillrect(64,36,64+(in_3%(255+1)),36+16,3);
	}

}

void FB_Put_Int15 ( int in_1)
{
	
	put_int(16,44,in_1,2);

}

void Right_Shift8 ( int in_0, int &out_1)
{

	out_1 = in_0 >> 2;
}

void FB_Draw_HLine3 ( unsigned short int in_3)
{
	if(!firstLoop)		// do nothing in first loop
	{
	   	fillrect(64,16,64+255,16+16,0); //Black Rect
		rect(64,16,64+255,16+16,3); //Extern Rect
		fillrect(64,16,64+(in_3%(255+1)),16+16,3);
	}

}

void FB_Put_Int9 ( int in_1)
{
	
	put_int(16,24,in_1,2);

}

void FB_Put_Int19 ( int in_1)
{
	
	put_int(16,124,in_1,2);

}

void Right_Shift26 ( int in_0, int &out_1)
{

	out_1 = in_0 >> 2;
}

void FB_Draw_HLine12 ( unsigned short int in_3)
{
	if(!firstLoop)		// do nothing in first loop
	{
	   	fillrect(64,116,64+255,116+16,0); //Black Rect
		rect(64,116,64+255,116+16,3); //Extern Rect
		fillrect(64,116,64+(in_3%(255+1)),116+16,3);
	}

}

void FB_Put_Int20 ( int in_1)
{
	
	put_int(16,144,in_1,2);

}

void Right_Shift27 ( int in_0, int &out_1)
{

	out_1 = in_0 >> 2;
}

void FB_Draw_HLine13 ( unsigned short int in_3)
{
	if(!firstLoop)		// do nothing in first loop
	{
	   	fillrect(64,136,64+255,136+16,0); //Black Rect
		rect(64,136,64+255,136+16,3); //Extern Rect
		fillrect(64,136,64+(in_3%(255+1)),136+16,3);
	}

}

void FB_Put_Int21 ( int in_1)
{
	
	put_int(16,164,in_1,2);

}

void Right_Shift28 ( int in_0, int &out_1)
{

	out_1 = in_0 >> 2;
}

void FB_Draw_HLine14 ( unsigned short int in_3)
{
	if(!firstLoop)		// do nothing in first loop
	{
	   	fillrect(64,156,64+255,156+16,0); //Black Rect
		rect(64,156,64+255,156+16,3); //Extern Rect
		fillrect(64,156,64+(in_3%(255+1)),156+16,3);
	}

}

void FB_Print_Line29 ()
{
	
	if(0)
	{
		put_string_center (0,36,"CHA [1]", 4);
	}
	else
	{
		put_string (0,36,"CHA [1]", 4%5);
	}

}

void FB_Print_Line30 ()
{
	
	if(0)
	{
		put_string_center (0,56,"CHA [2]", 4);
	}
	else
	{
		put_string (0,56,"CHA [2]", 4%5);
	}

}

void FB_Print_Line31 ()
{
	
	if(0)
	{
		put_string_center (0,76,"CHA [3]", 4);
	}
	else
	{
		put_string (0,76,"CHA [3]", 4%5);
	}

}

void FB_Print_Line32 ()
{
	
	if(0)
	{
		put_string_center (0,96,"CHA [4]", 4);
	}
	else
	{
		put_string (0,96,"CHA [4]", 4%5);
	}

}

void FB_Print_Line33 ()
{
	
	if(0)
	{
		put_string_center (0,116,"CHA [5]", 4);
	}
	else
	{
		put_string (0,116,"CHA [5]", 4%5);
	}

}

void FB_Print_Line34 ()
{
	
	if(0)
	{
		put_string_center (0,136,"CHA [6]", 4);
	}
	else
	{
		put_string (0,136,"CHA [6]", 4%5);
	}

}




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
		
	
    		

		

		

		

		

		

	
	ADC_SPI_CLKDIV=255;
	ADC_BUFFER_LEN=8;
	ADC_MUX_CHANNELS=7;
		

		

		

		

		

		


    
    	//Inputs/Outputs: Block: <FB Print Line> with ID[38] 
	//Inputs/Outputs: Block: <FB Print Line> with ID[37] 
	//Inputs/Outputs: Block: <FB Print Line> with ID[36] 
	//Inputs/Outputs: Block: <FB Print Line> with ID[35] 
	//Inputs/Outputs: Block: <FB Print Line> with ID[10] 
	//Inputs/Outputs: Block: <Constant Bool> with ID[1] 
	bool out_3_1=0;
	//Inputs/Outputs: Block: <System While> with ID[5] 
	bool in_6_5=0;
	//Inputs/Outputs: Block: <FB Print Line> with ID[2] 
	//Inputs/Outputs: Block: <ADC Eight> with ID[7] 
	unsigned short int out_8_7=0;
	unsigned short int out_7_7=0;
	unsigned short int out_6_7=0;
	unsigned short int out_5_7=0;
	unsigned short int out_4_7=0;
	unsigned short int out_3_7=0;
	unsigned short int out_2_7=0;
	unsigned short int out_1_7=0;
	//Inputs/Outputs: Block: <Right Shift> with ID[25] 
	int in_0_25=0;
	int out_1_25=0;
	//Inputs/Outputs: Block: <FB Draw HLine> with ID[11] 
	unsigned short int in_3_11=0;
	//Inputs/Outputs: Block: <FB Put Int> with ID[18] 
	int in_1_18=0;
	//Inputs/Outputs: Block: <Right Shift> with ID[24] 
	int in_0_24=0;
	int out_1_24=0;
	//Inputs/Outputs: Block: <FB Draw HLine> with ID[6] 
	unsigned short int in_3_6=0;
	//Inputs/Outputs: Block: <FB Put Int> with ID[17] 
	int in_1_17=0;
	//Inputs/Outputs: Block: <Right Shift> with ID[23] 
	int in_0_23=0;
	int out_1_23=0;
	//Inputs/Outputs: Block: <FB Draw HLine> with ID[4] 
	unsigned short int in_3_4=0;
	//Inputs/Outputs: Block: <FB Put Int> with ID[16] 
	int in_1_16=0;
	//Inputs/Outputs: Block: <Right Shift> with ID[22] 
	int in_0_22=0;
	int out_1_22=0;
	//Inputs/Outputs: Block: <FB Draw HLine> with ID[0] 
	unsigned short int in_3_0=0;
	//Inputs/Outputs: Block: <FB Put Int> with ID[15] 
	int in_1_15=0;
	//Inputs/Outputs: Block: <Right Shift> with ID[8] 
	int in_0_8=0;
	int out_1_8=0;
	//Inputs/Outputs: Block: <FB Draw HLine> with ID[3] 
	unsigned short int in_3_3=0;
	//Inputs/Outputs: Block: <FB Put Int> with ID[9] 
	int in_1_9=0;
	//Inputs/Outputs: Block: <FB Put Int> with ID[19] 
	int in_1_19=0;
	//Inputs/Outputs: Block: <Right Shift> with ID[26] 
	int in_0_26=0;
	int out_1_26=0;
	//Inputs/Outputs: Block: <FB Draw HLine> with ID[12] 
	unsigned short int in_3_12=0;
	//Inputs/Outputs: Block: <FB Put Int> with ID[20] 
	int in_1_20=0;
	//Inputs/Outputs: Block: <Right Shift> with ID[27] 
	int in_0_27=0;
	int out_1_27=0;
	//Inputs/Outputs: Block: <FB Draw HLine> with ID[13] 
	unsigned short int in_3_13=0;
	//Inputs/Outputs: Block: <FB Put Int> with ID[21] 
	int in_1_21=0;
	//Inputs/Outputs: Block: <Right Shift> with ID[28] 
	int in_0_28=0;
	int out_1_28=0;
	//Inputs/Outputs: Block: <FB Draw HLine> with ID[14] 
	unsigned short int in_3_14=0;
	//Inputs/Outputs: Block: <FB Print Line> with ID[29] 
	//Inputs/Outputs: Block: <FB Print Line> with ID[30] 
	//Inputs/Outputs: Block: <FB Print Line> with ID[31] 
	//Inputs/Outputs: Block: <FB Print Line> with ID[32] 
	//Inputs/Outputs: Block: <FB Print Line> with ID[33] 
	//Inputs/Outputs: Block: <FB Print Line> with ID[34] 

    
    
do
{	
	FB_Print_Line38 ();
	FB_Print_Line37 ();
	FB_Print_Line36 ();
	FB_Print_Line35 ();
	FB_Print_Line10 ();
	Constant_Bool1 ( out_3_1);
	in_6_5 = out_3_1;
	FB_Print_Line2 ();
	ADC_Eight7 ( out_8_7, out_7_7, out_6_7, out_5_7, out_4_7, out_3_7, out_2_7, out_1_7);
	in_0_25 = out_5_7;
	Right_Shift25 ( in_0_25, out_1_25);
	in_3_11 = out_1_25;
	FB_Draw_HLine11 ( in_3_11);
	in_1_18 = out_5_7;
	FB_Put_Int18 ( in_1_18);
	in_0_24 = out_4_7;
	Right_Shift24 ( in_0_24, out_1_24);
	in_3_6 = out_1_24;
	FB_Draw_HLine6 ( in_3_6);
	in_1_17 = out_4_7;
	FB_Put_Int17 ( in_1_17);
	in_0_23 = out_3_7;
	Right_Shift23 ( in_0_23, out_1_23);
	in_3_4 = out_1_23;
	FB_Draw_HLine4 ( in_3_4);
	in_1_16 = out_3_7;
	FB_Put_Int16 ( in_1_16);
	in_0_22 = out_2_7;
	Right_Shift22 ( in_0_22, out_1_22);
	in_3_0 = out_1_22;
	FB_Draw_HLine0 ( in_3_0);
	in_1_15 = out_2_7;
	FB_Put_Int15 ( in_1_15);
	in_0_8 = out_1_7;
	Right_Shift8 ( in_0_8, out_1_8);
	in_3_3 = out_1_8;
	FB_Draw_HLine3 ( in_3_3);
	in_1_9 = out_1_7;
	FB_Put_Int9 ( in_1_9);
	in_1_19 = out_6_7;
	FB_Put_Int19 ( in_1_19);
	in_0_26 = out_6_7;
	Right_Shift26 ( in_0_26, out_1_26);
	in_3_12 = out_1_26;
	FB_Draw_HLine12 ( in_3_12);
	in_1_20 = out_7_7;
	FB_Put_Int20 ( in_1_20);
	in_0_27 = out_7_7;
	Right_Shift27 ( in_0_27, out_1_27);
	in_3_13 = out_1_27;
	FB_Draw_HLine13 ( in_3_13);
	in_1_21 = out_8_7;
	FB_Put_Int21 ( in_1_21);
	in_0_28 = out_8_7;
	Right_Shift28 ( in_0_28, out_1_28);
	in_3_14 = out_1_28;
	FB_Draw_HLine14 ( in_3_14);
	FB_Print_Line29 ();
	FB_Print_Line30 ();
	FB_Print_Line31 ();
	FB_Print_Line32 ();
	FB_Print_Line33 ();
	FB_Print_Line34 ();

firstLoop=0;
}while(in_6_5);
    
    return 0;
}


