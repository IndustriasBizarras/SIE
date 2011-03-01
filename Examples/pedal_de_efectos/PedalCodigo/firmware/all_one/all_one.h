/****************************************************************************
 * Types
 */
typedef unsigned int  uint32_t;    // 32 Bit
typedef signed   int   int32_t;    // 32 Bit

typedef unsigned char  uint8_t;    // 8 Bit
typedef signed   char   int8_t;    // 8 Bit


//----------------------------------Interruptions ------------------------------||
typedef void(*isr_ptr_t)(void);

void     irq_enable();
void     irq_disable();
void     irq_set_mask(uint32_t mask);
uint32_t irq_get_mak();

void     isr_init();
void     isr_register(int irq, isr_ptr_t isr);
void     isr_unregister(int irq);



//---------------------------------LCD Structure-----------------------------||
typedef struct {
	volatile uint8_t address;
	volatile uint8_t data;
	volatile uint8_t status;
	volatile uint8_t control;			//for Instruction - address is a no care
	volatile uint8_t none;
} lcd_t;

void LCD_Data (uint8_t addr,uint8_t dato);
void LCD_Instruction (uint8_t inst);
void LCD_Init();
void LCD_Pedal();
void LCD_delay (uint32_t amount);	//0 for treble --- 1 for bass	
void LCD_Stop();
void LCD_Flanger();
void LCD_Echo();
void LCD_Clean();

//---------------------------------Effects Structure-----------------------------||
typedef struct {
	volatile uint32_t control;
	volatile uint32_t Par_delay1;
	volatile uint32_t Par_delay2;
	volatile uint32_t offset_uplimit;
	volatile uint32_t offset_lowlimit;
	volatile uint32_t status;
} effects_t;

void Effects_Init();
void Effects_delay1(uint32_t delay1);
void Effects_Echo ();
void Effects_Flanger ();
void Effects_Clean ();
void Flanger_up_limit (uint32_t uplimit);
void Flanger_low_limit (uint32_t uplimit);
uint32_t Eff_Status();
uint32_t Eff_Echo_read();
uint32_t Eff_Flang_read_up();
uint32_t Eff_Flang_read_low();
void Eff_Increase_Echo();
void Eff_Decrease_Echo();
void Eff_Increase_Flang_up();
void Eff_Decrease_Flang_up();


//---------------------------------ADC Structure-----------------------------||

typedef struct {
	volatile uint8_t status;
	volatile uint8_t data_rdy;
	volatile uint8_t data_adc;
	volatile uint8_t channel;
	volatile uint8_t control;
	volatile uint8_t busy;
} adc_t;

void ADC_Instruction (uint8_t chan,uint8_t ctrl);
void ADC_enable();


//---------------------------------PWM Structure-----------------------------||

typedef struct {
	volatile uint32_t cspwm;
	volatile uint32_t freq_div;
	volatile uint32_t time_add;
	volatile uint32_t cycle_adder;
	
} pwm_t;

void pwm_enable();
void pwm_freq_div(uint32_t freq_div);	
void pwm_time_add(uint32_t time_add);
void pwm_cycle_adder (uint32_t cycle_adder);
void pwm_40khz();
void pwm_195khz();


//---------------------------------UART Structure-----------------------------||


#define UART_DR   0x01                    // RX Data Ready
#define UART_ERR  0x02                    // RX Error
#define UART_BUSY 0x10                    // TX Busy

typedef struct {
   volatile uint32_t ucr;
   volatile uint32_t rxtx;
} uart_t;

void uart_init();
void uart_putchar(char c);
void uart_putstr(char *str);
char uart_getchar();


//---------------------------------EQUAL Structure-----------------------------||
 
typedef struct {
	volatile uint32_t gainB;
	volatile uint32_t gainH;
} ecual_t;

void set_gainb(uint32_t gainb);
void set_gainh(uint32_t gainh);
uint32_t getecual_gainh ();
uint32_t getecual_gainb ();


//---------------------------------GPIO Structure-----------------------------||
 
typedef struct {
	volatile uint32_t in;
	volatile uint32_t out;
} gpio_t;

uint32_t get_gpioin();
uint32_t get_gpioout();
void gpio_isr();

