#include "all_one.h"
uint32_t *flag;

void gpio_isr()
{
uint32_t a;
*flag  = 1;
a = get_gpioout ();
return;
}



int main ()
{
*flag  = 0;
// Init Commands
irq_enable();
irq_set_mask( 0x00000002 );

ADC_Instruction(0x02,0x01);
pwm_195khz();
LCD_Clean();
Effects_Clean ();
Effects_delay1(0x00000001);

//Interruptions Detection
volatile uint32_t val_delay, t,ctrl,clean;
clean =0;
while (1){

if (* flag)
{
        t = get_gpioout ();
	ctrl = Eff_Status();
	*flag  = 0;
	switch (t) {
		case 0x00000001:
		if ((!clean) & (ctrl==2)) {

			  Eff_Decrease_Echo();
 			  val_delay = Eff_Echo_read();

				if (val_delay<1001)
					LCD_delay(1);
				if ((val_delay>1000) && (val_delay<2001))
					LCD_delay(2);
				if ((val_delay>2000) && (val_delay<3001))
					LCD_delay(3);
				if ((val_delay>3000) && (val_delay<4001))
					LCD_delay(4);
				if ((val_delay>4000) && (val_delay<5001))
					LCD_delay(5);
				if ((val_delay>5000) && (val_delay<6001))
					LCD_delay(6);
				if ((val_delay>6000) && (val_delay<7001))
					LCD_delay(7);
				if (val_delay>7000)
					LCD_delay(8);
		}
		else if ((!clean) & (ctrl==4)){
	
			Eff_Decrease_Flang_up();
			val_delay = Eff_Flang_read_up();

				if (val_delay<41)
					LCD_delay(1);
				if ((val_delay>40) && (val_delay<81))
					LCD_delay(2);
				if ((val_delay>80) && (val_delay<121))
					LCD_delay(3);
				if ((val_delay>120) && (val_delay<161))
					LCD_delay(4);
				if ((val_delay>200) && (val_delay<241))
					LCD_delay(5);
				if ((val_delay>280) && (val_delay<321))
					LCD_delay(6);
				if ((val_delay>320) && (val_delay<361))
					LCD_delay(7);
				if (val_delay>360)
					LCD_delay(8);

		}
		break;
		case 0x00000002:  
		if ((!clean) & (ctrl==2)) {
		  	Eff_Increase_Echo();
 			  val_delay = Eff_Echo_read();

				if (val_delay<1001)
					LCD_delay(1);
				if ((val_delay>1000) && (val_delay<2001))
					LCD_delay(2);
				if ((val_delay>2000) && (val_delay<3001))
					LCD_delay(3);
				if ((val_delay>3000) && (val_delay<4001))
					LCD_delay(4);
				if ((val_delay>4000) && (val_delay<5001))
					LCD_delay(5);
				if ((val_delay>5000) && (val_delay<6001))
					LCD_delay(6);
				if ((val_delay>6000) && (val_delay<7001))
					LCD_delay(7);
				if (val_delay>7000)
					LCD_delay(8);

		}
		else if ((!clean) & (ctrl==4)) {
			Eff_Increase_Flang_up();
 			val_delay = Eff_Flang_read_up();

				if (val_delay<101)
					LCD_delay(1);
				if ((val_delay>100) && (val_delay<151))
					LCD_delay(2);
				if ((val_delay>150) && (val_delay<201))
					LCD_delay(3);
				if ((val_delay>200) && (val_delay<251))
					LCD_delay(4);
				if ((val_delay>250) && (val_delay<301))
					LCD_delay(5);
				if ((val_delay>300) && (val_delay<351))
					LCD_delay(6);
				if ((val_delay>350) && (val_delay<401))
					LCD_delay(7);
				if (val_delay>400)
					LCD_delay(8);
		}
		break;
		case 0x00000003: 
			if ( (!clean) & (ctrl==2) )	//Echo to Flang
			 { 
                           LCD_Flanger();
			   Effects_Flanger ();
			   clean=0;
			   val_delay = Eff_Flang_read_up();

				if (val_delay<101)
					LCD_delay(1);
				if ((val_delay>100) && (val_delay<151))
					LCD_delay(2);
				if ((val_delay>150) && (val_delay<201))
					LCD_delay(3);
				if ((val_delay>200) && (val_delay<251))
					LCD_delay(4);
				if ((val_delay>250) && (val_delay<301))
					LCD_delay(5);
				if ((val_delay>300) && (val_delay<351))
					LCD_delay(6);
				if ((val_delay>350) && (val_delay<401))
					LCD_delay(7);
				if (val_delay>400)
					LCD_delay(8);

			 } else if ((!clean) & (ctrl==4)){		//Flang to Clean
				 LCD_Clean();
				 Effects_Clean ();
				   clean=1;
				}
			else {				//Clean to Echo
				LCD_Echo();
			   	Effects_Echo ();
				   clean=0;
 			  val_delay = Eff_Echo_read();

				if (val_delay<1001)
					LCD_delay(1);
				if ((val_delay>1000) && (val_delay<2001))
					LCD_delay(2);
				if ((val_delay>2000) && (val_delay<3001))
					LCD_delay(3);
				if ((val_delay>3000) && (val_delay<4001))
					LCD_delay(4);
				if ((val_delay>4000) && (val_delay<5001))
					LCD_delay(5);
				if ((val_delay>5000) && (val_delay<6001))
					LCD_delay(6);
				if ((val_delay>6000) && (val_delay<7001))
					LCD_delay(7);
				if (val_delay>7000)
					LCD_delay(8);			
				}
			 
		break;

		case 0x00000004: 
		break;

		default: LCD_delay(1);			  
			}
	} else 
	{
	LCD_none();
		}
}
return 0;


}


