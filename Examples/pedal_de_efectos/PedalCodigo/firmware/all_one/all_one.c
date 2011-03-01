#include "all_one.h"

uart_t  	*uart0  =     (uart_t *)   	0xF0000000;
effects_t 	*effects0  =  (effects_t *)     0xFF010000;
gpio_t 	      	*gpio0  =     (gpio_t *)   	0xFF020000;
adc_t	  	*adc0  	=     (adc_t *)    	0xFF030000;
lcd_t  		*lcd0   =     (lcd_t *)    	0xFF040000;
ecual_t    	*ecual0 =     (ecual_t *)  	0XFF060000;
pwm_t	  	*pwm0  	=     (pwm_t *)    	0xFF050000;


void irq_handler(uint32_t pending){
gpio_isr();
}
//--------------------------------------LCD Functions ------------------------------||
void LCD_none()

{
lcd0->none=2;
}

void LCD_Instruction (uint8_t inst)
{

lcd0->data=inst; 
lcd0->address=0x04;
lcd0->control=0x05; 	//0x05 for Instruction

return;
}
void LCD_Data (uint8_t addr,uint8_t dato)
{
lcd0->data=dato;
lcd0->address=addr;
lcd0->control=0x06; 	//0x06 for Data
return;
}

void LCD_Pedal()
{
LCD_Data(0x80,0xA0);		//Espacio
LCD_Data(0x81,0xA0);		//Espacio
LCD_Data(0x82,0x50);		//P
LCD_Data(0x83,0x65);		//e
LCD_Data(0x84,0x64);		//d
LCD_Data(0x85,0x61);		//a
LCD_Data(0x86,0x6C);		//l
LCD_Data(0x87,0xA0);		//Espacio
LCD_Data(0x88,0x64);		//d
LCD_Data(0x89,0x65);		//e
LCD_Data(0x8A,0xA0);		//Espacio
LCD_Data(0x8B,0x65);		//e
LCD_Data(0x8C,0x66);		//f
LCD_Data(0x8D,0x65);		//e
LCD_Data(0x8E,0x63);		//c
LCD_Data(0x8F,0x74);		//t
LCD_Data(0x90,0x6F);		//o
LCD_Data(0x91,0x73);		//s
return;
}


void LCD_Clear (){
LCD_Instruction (0x01);
}
void LCD_Echo()
{
LCD_Clear ();
LCD_Pedal();
LCD_Data(0x94,0x52);		//R
LCD_Data(0x95,0x65);		//e	
LCD_Data(0x96,0x74);		//t
LCD_Data(0x97,0x72);		//r
LCD_Data(0x98,0x61);		//a
LCD_Data(0x99,0x73);		//s
LCD_Data(0x9A,0x6F);		//o
LCD_Data(0xA1,0x45);		//E
LCD_Data(0xA2,0x66);		//f
LCD_Data(0xA3,0x65);		//e
LCD_Data(0xA4,0x63);		//c
LCD_Data(0xA5,0x74);		//t
LCD_Data(0xA6,0x6F);		//o
LCD_Data(0xE1,0x45);		//E
LCD_Data(0xE2,0x63);		//c
LCD_Data(0xE3,0x68);		//h
LCD_Data(0xE4,0x6F);		//o
return;
}

void LCD_Flanger()
{
LCD_Clear ();
LCD_Pedal();
LCD_Data(0x94,0x52);		//R
LCD_Data(0x95,0x65);		//e	
LCD_Data(0x96,0x74);		//t
LCD_Data(0x97,0x72);		//r
LCD_Data(0x98,0x61);		//a
LCD_Data(0x99,0x73);		//s
LCD_Data(0x9A,0x6F);		//o
LCD_Data(0xA1,0x45);		//E
LCD_Data(0xA2,0x66);		//f
LCD_Data(0xA3,0x65);		//e
LCD_Data(0xA4,0x63);		//c
LCD_Data(0xA5,0x74);		//t
LCD_Data(0xA6,0x6F);		//o

LCD_Data(0xE1,0x46);		//F
LCD_Data(0xE2,0x6C);		//l
LCD_Data(0xE3,0x61);		//a
LCD_Data(0xE4,0x6E);		//n
LCD_Data(0xE5,0x67);		//g
LCD_Data(0xE6,0x65);		//e
LCD_Data(0xE7,0x72);		//r
return;
}

void LCD_Clean()
{
LCD_Clear ();
LCD_Pedal();
LCD_Data(0x9D,0x53);		//S
LCD_Data(0x9E,0x69);		//i
LCD_Data(0x9F,0x6E);		//n
LCD_Data(0xA0,0xA0);		//Espacio
LCD_Data(0xA1,0x45);		//E
LCD_Data(0xA2,0x66);		//f
LCD_Data(0xA3,0x65);		//e
LCD_Data(0xA4,0x63);		//c
LCD_Data(0xA5,0x74);		//t
LCD_Data(0xA6,0x6F);		//o
LCD_Data(0xA7,0x73);		//s

return;
}

void LCD_delay (uint32_t amount)	//0 for flanger --- 1 for echo	
{
uint8_t addr;
uint8_t character;
character = 0xFF;
addr = 0xD4;	

switch (amount) {
	case 1: 
		LCD_Data(addr,character);
		LCD_Data(addr+1,0xA0);		 
		LCD_Data(addr+2,0xA0);		 
		LCD_Data(addr+3,0xA0);		 
		LCD_Data(addr+4,0xA0);		 
		LCD_Data(addr+5,0xA0);		 
		LCD_Data(addr+6,0xA0);
		LCD_Data(addr+7,0xA0);		 
	break;
	case 2: 
		LCD_Data(addr,character);
		LCD_Data(addr+1,character);		 
		LCD_Data(addr+2,0xA0);		 
		LCD_Data(addr+3,0xA0);		 
		LCD_Data(addr+4,0xA0);		 
		LCD_Data(addr+5,0xA0);		 
		LCD_Data(addr+6,0xA0);		 
		LCD_Data(addr+7,0xA0);
	break;
	case 3: 
		LCD_Data(addr,character);
		LCD_Data(addr+1,character);		 
		LCD_Data(addr+2,character);		 
		LCD_Data(addr+3,0xA0);		 
		LCD_Data(addr+4,0xA0);		 
		LCD_Data(addr+5,0xA0);		 
		LCD_Data(addr+6,0xA0);		 
		LCD_Data(addr+7,0xA0);		 
	break;
	case 4: 
		LCD_Data(addr,character);
		LCD_Data(addr+1,character);		 
		LCD_Data(addr+2,character);		 
		LCD_Data(addr+3,character);		 
		LCD_Data(addr+4,0xA0);		 
		LCD_Data(addr+5,0xA0);		 
		LCD_Data(addr+6,0xA0);		 
		LCD_Data(addr+7,0xA0);		 
	break;
	case 5: 
		LCD_Data(addr,character);		 
		LCD_Data(addr+1,character);		
		LCD_Data(addr+2,character);		 
		LCD_Data(addr+3,character);		 
		LCD_Data(addr+4,character);		 
		LCD_Data(addr+5,0xA0);		 
		LCD_Data(addr+6,0xA0);		 
		LCD_Data(addr+7,0xA0);		 
	break;
	case 6: 
		LCD_Data(addr,character);		 
		LCD_Data(addr+1,character);		 
		LCD_Data(addr+2,character);		 
		LCD_Data(addr+3,character);		 
		LCD_Data(addr+4,character);
		LCD_Data(addr+5,character);			 
		LCD_Data(addr+6,0xA0);		 
		LCD_Data(addr+7,0xA0);		 
	break;
	case 7: 
		LCD_Data(addr,character);		 
		LCD_Data(addr+1,character);		 
		LCD_Data(addr+2,character);		 
		LCD_Data(addr+3,character);		 
		LCD_Data(addr+4,character);		 
		LCD_Data(addr+5,character);
		LCD_Data(addr+6,character);
	        LCD_Data(addr+7,0xA0);		 
	break;
	case 8: 
		LCD_Data(addr,character);		 
		LCD_Data(addr+1,character);		 
		LCD_Data(addr+2,character);		 
		LCD_Data(addr+3,character);		 
		LCD_Data(addr+4,character);		 
		LCD_Data(addr+5,character);		 
		LCD_Data(addr+6,character);
		LCD_Data(addr+7,character);		 
	break;

	default: LCD_Data(0x15,0xE0);
}
return;
}
void LCD_Stop()
{
lcd0->control=0x00;
return;
}

//----------------------------------Effects Functions ------------------------------||


// ---- Status Read Functions  -----------    

uint32_t Eff_Status()
{
volatile uint32_t a;
a = effects0->status;
return a;
}

uint32_t Eff_Echo_read()
{
volatile uint32_t a;
a = effects0->Par_delay1;
return a;
}

uint32_t Eff_Flang_read_up()
{
volatile uint32_t a;
a = effects0->offset_uplimit;
return a;
}

uint32_t Eff_Flang_read_low()
{
volatile uint32_t a;
a = effects0->offset_lowlimit;
return a;
}


// ---- Control Functions      ------- 

				//Increase Echo Delay
void Eff_Increase_Echo()
{
volatile uint32_t a;
a = Eff_Echo_read();
if (a>7000) 
	{
	a=0;
	Effects_delay1 (8000);
	} else {
	Effects_delay1 (a + 1000);
	}
return;
}
				//Decrease Echo Delay
void Eff_Decrease_Echo()
{
volatile uint32_t a;
a = Eff_Echo_read();
if (a<1500) 
	{
	a=0;
	Effects_delay1 (1000);
	} else {
	Effects_delay1 (a - 1000);
	}
return;
}

				//Increase Flanger up parameter - max delay
void Eff_Increase_Flang_up()
{
volatile uint32_t a;
a = Eff_Flang_read_up();
if (a>360){
	a=0;
	Flanger_up_limit (360);
	} else {
	Flanger_up_limit (a + 40);
	}
return;
}
				//Decrease Flanger up parameter
void Eff_Decrease_Flang_up()
{
volatile uint32_t a;
a = Eff_Flang_read_up();
if (a<40){
	a=0;
	Flanger_up_limit (40);
	} else {
	Flanger_up_limit (a - 40);
	}
return;
}

				//Clean Sound
void Effects_Clean ()
{
effects0->control=0x01;
Effects_delay1 (0x00000001);
return;
}

				// Call to Effects Switch
void Effects_Echo ()
{
effects0->control=0x01;
return;
}
void Effects_Flanger ()
{
effects0->control=0x02;
return;
}
				//Echo delay setting

void Effects_delay1(uint32_t delay1)
{
effects0->Par_delay1=delay1;
return;
}

void Effects_delay2(uint32_t delay2)
{
effects0->Par_delay2=delay2;
return;
}
				//Flanger settings
void Flanger_up_limit (uint32_t uplimit)
{
effects0->offset_uplimit = uplimit;
return;
}

void Flanger_low_limit (uint32_t lowlimit)
{
effects0->offset_lowlimit = lowlimit;
return;
}


//----------------------------------UART Functions ------------------------------||

void uart_init()
{
	//uart0->ier = 0x00;  // Interrupt Enable Register
	//uart0->lcr = 0x03;  // Line Control Register:    8N1
	//uart0->mcr = 0x00;  // Modem Control Register

	// Setup Divisor register (Fclk / Baud)
	//uart0->div = (FCPU/(57600*16));
}

char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}

//----------------------------------PWM Functions ------------------------------||

void pwm_enable(){
pwm0->cspwm=1;
return;
}
void pwm_freq_div(uint32_t freq_div)
{
pwm0->freq_div=freq_div;
return;
}
void pwm_time_add(uint32_t time_add)
{
pwm0->time_add=time_add;
return;
}
void pwm_cycle_adder(uint32_t cycle_adder)
{
pwm0->cycle_adder=cycle_adder;
return;
}
void pwm_195khz()
{
pwm_enable();
pwm_freq_div (0x00000100);		//0x100 for 195Khz
pwm_time_add(1);
pwm_cycle_adder(2);
}
void pwm_max()
{
pwm_freq_div (0x00000200);		//200 is 98Khz
pwm_time_add(1);
pwm_cycle_adder(1);
}


//----------------------------------ADC Functions ------------------------------||

void ADC_Instruction (uint8_t chan,uint8_t ctrl)
{
adc0->channel=chan;	//coloca el canal de conversion  (canal 1=00)
adc0->control=ctrl;	//01 inicia la conversion
return;

}


//----------------------------------EQUAL Functions ------------------------------||


void set_gainb(uint32_t gainb)
{
	ecual0->gainB = gainb;
	return;
}

void set_gainh(uint32_t gainh)
{
	ecual0->gainH = gainh;
	return;
}

uint32_t getecual_gainh ()
{
	return ecual0->gainH;
}
uint32_t getecual_gainb ()
{
	return ecual0->gainB;
}

//----------------------------------GPIO Functions ------------------------------||
uint32_t get_gpioin ()
{	
	uint32_t a;
	a=gpio0->in;	
	return a;
}

uint32_t get_gpioout ()
{
return gpio0->out;
}
//atencion a las interrupciones LCD_Data(0x80,dato);

