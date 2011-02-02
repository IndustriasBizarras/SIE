//UNAL 2010
//RFM22B Demo example by juan64bits, based on HOPE RF examples for PIC
//and datasheet. http://www.hoperf.com/rf_fsk/rfm22b.htm
//FIXME: 
//  *¿?
//TODO: 
//  *In order to avoid using while() loops is necessary to 
//   implement ISR (interrupt service routine) for RF_IRQ pin
//  *

#include <avr/io.h>
#include <util/delay.h>

#define DEBUG    0          // Debug mode.
#define DEMO_RX  0          // Rx demo mode.
#define DEMO_TX  1          // Tx demo mode.

#define F_CPU    1000000UL   // 1 MHz
#define SPI_PORT PORTB       // SPI PORT
#define SPI_DDR  DDRB        // PORT REGISTER
#define SPI_CS   PB0         // RF_nSEL

#define RF_PORT PORTD   // RF PORT
#define RF_DDR  DDRD    // RF DDRD
#define RF_PIN  PIND    // RF PIN
#define RF_RXEN PD4     // Rx enable
#define RF_TXEN PD3     // Tx enable
#define RF_IRQ  PD7     // IRQ

#define RF22B_PWRSTATE_POWERDOWN            0x00
#define RF22B_PWRSTATE_READY                0x01
#define RF22B_Rx_packet_received_interrupt  0x02
#define RF22B_PACKET_SENT_INTERRUPT         0x04
#define RF22B_PWRSTATE_RX                   0x05
#define RF22B_PWRSTATE_TX                   0x09

void initUSART0(unsigned long baud)
{
    UBRR0 = F_CPU/16/baud-1;           // Set Baudrate
    UCSR0C = (3<<UCSZ00);               // Character Size 8 bit
    UCSR0B |= _BV(RXEN0) | _BV(TXEN0);  // Receiver and Transmitter Enable    
}

unsigned char receive1byteUSART0(void)
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void transmit1byteUSART0(unsigned char data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

void transmitStrUSART0(char *str)
{
    while (*str != 0) {
        transmit1byteUSART0(*str);
        *str++;
    }
}

void sendByteToHexUart(unsigned char value) 
{
    transmit1byteUSART0('0');    
    transmit1byteUSART0('x');
    if((value>>4)<10)
        transmit1byteUSART0('0'+(value>>4));
    else
        transmit1byteUSART0('A'+(value>>4)-10);
    if((value&0x0F)<10)
        transmit1byteUSART0('0'+(value&0x0F));
    else
        transmit1byteUSART0('A'+(value&0x0F)-10);        
    transmit1byteUSART0(' ');
    transmit1byteUSART0(0);

}

unsigned char spiWriteRead(unsigned char dataout)
{
  unsigned char datain;
  // Start transmission (MOSI)
  SPDR = dataout;
  // Wait for transmission complete
  while(!(SPSR & (1<<SPIF))){}
  // Get return Value;
  datain = SPDR;     
  // Return Serial In Value (MISO)
  return datain;
}

void initSPI(void)
{
    // Set MOSI and SCK as output, others as input
    SPI_DDR = 0xFF;
    SPI_DDR &= ~(1<<PB4); 
    // Enable SPI, Master, set clock rate fck/2 (maximum)
    SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);  

    SPI_PORT |= (1<<SPI_CS);    // SPI SS set to high
}

unsigned char spiRead(unsigned char address)
{
    // nSEL= L
    SPI_PORT &= ~(1<<SPI_CS);
    //_delay_us(10);              // Setup time : min 20 ns
    unsigned char result;
    spiWriteRead(address&0x7f);        // D7 = 0 for read
    result = spiWriteRead(0x00);       // SDI don't care
    // nSEL= H
    //_delay_us(10);              // High period min: 80ns
    SPI_PORT |= (1<<SPI_CS);
    return(result);
}

unsigned char spiWrite(unsigned char address,unsigned char data)
{
    // nSEL= L
    SPI_PORT &= ~(1<<SPI_CS);
    //_delay_us(10);              // Setup time : min 20 ns
    unsigned char result;
    spiWriteRead(address|0x80);    // Send address, D7 = 1 for write
    result = spiWriteRead(data);   // Send register value
    // nSEL= H
    //_delay_us(10);              // High period min: 80ns
    SPI_PORT |= (1<<SPI_CS);
#if DEBUG==1
    transmitStrUSART0("Setting REG[ ");
    sendByteToHexUart(address);
    transmitStrUSART0("]= ");
    sendByteToHexUart(data);
    transmitStrUSART0(" ( ");
    sendByteToHexUart(spiRead(address));
    transmitStrUSART0(")");
    transmitStrUSART0("\r\n");
#endif    
    return(result);
}

void rfm22bInit(void)
{
    RF_PORT |=  (1<<RF_IRQ); // IRQ PULLUP

    RF_DDR &= ~(1<<RF_IRQ);  // Input
    RF_DDR |= (1<<RF_TXEN);  // Output
    RF_DDR |= (1<<RF_RXEN);  // Output
    
    RF_PORT &= ~(1<<RF_RXEN); // RXEN Low
    RF_PORT &= ~(1<<RF_TXEN); // TXEN Low   

    _delay_ms(100); 

#if DEMO_TX==1
    transmitStrUSART0("RFM22B Initialize Process (TX DEMO)\r\n");
#elif DEMO_RX==1 
    transmitStrUSART0("RFM22B Initialize Process (RX DEMO)\r\n");
#endif

#if DEBUG==1
    transmitStrUSART0(" Register 0x03:");    
    sendByteToHexUart(spiRead(0x03));

    transmitStrUSART0(" Register 0x04:");    
    sendByteToHexUart(spiRead(0x04));
    
    transmitStrUSART0("\r\n");
#else
    spiRead(0x03);
    spiRead(0x04);
#endif

        
    spiWrite(0x06, 0x00); // no wakeup up, lbd,
    // disable lbd, wakeup timer, use internal 32768,xton = 1; in ready mode
    spiWrite(0x07, RF22B_PWRSTATE_READY);
    spiWrite(0x09, 0x7f); // c = 12.5p
    spiWrite(0x0a, 0x05);
    spiWrite(0x0b, 0xf4); // gpio0 for received data output
    spiWrite(0x0c, 0xef); // gpio 1 for clk output
    spiWrite(0x0d, 0xfd); // gpio 2 micro-controller clk output
    spiWrite(0x0e, 0x00); // gpio 0, 1,2 NO OTHER FUNCTION.
    spiWrite(0x70, 0x20); // disable manchest
    
    spiWrite(0x1d, 0x00); // enable afc
    spiWrite(0x1c, 0x1d); // RATE_24K: // 2.4k
    //0x20 calculate from the datasheet
    //= 500*(1+2*down3_bypass)/(2^ndec*RB*(1+enmanch))
    spiWrite(0x20,0x41);
    // 0x21 , rxosr[10--8] = 0; stalltr = (default), ccoff[19:16] = 0; 
    spiWrite(0x21, 0x60); 
    spiWrite(0x22, 0x27); // 0x22 ncoff =5033 = 0x13a9
    spiWrite(0x23, 0x52); // 0x23
    spiWrite(0x24, 0x00); // 0x24
    spiWrite(0x25, 0x06); // 0x25
    spiWrite(0x2a, 0x1e);
    
    //case RATE_24K: // 2.4k
    spiWrite(0x6e, 0x13);
    spiWrite(0x6f, 0xa9);
    //PH+FIFO
    spiWrite(0x30, 0x8c); // enable packet handler, msb first, enable crc,
                           // 0x31 only readable
    // 0x32address enable for headere byte 0, 1,2,3, receive 
    // header check for byte 0, 1,2,3          
    spiWrite(0x32, 0xff); 
    // header 3, 2, 1,0 used for head length, fixed packet length,
    // synchronize word length 3, 2,
    spiWrite(0x34, 64);
    spiWrite(0x33, 0x42); 
    // 64 nibble = 32byte preamble
    spiWrite(0x36, 0x2d); // synchronize word
    spiWrite(0x37, 0xd4);
    spiWrite(0x38, 0x00);
    spiWrite(0x39, 0x00);
    spiWrite(0x3a, 's'); // tx header
    spiWrite(0x3b, 'o');
    spiWrite(0x3c, 'n');
    spiWrite(0x3d, 'g');
    spiWrite(0x3e, 1); // total tx 1 byte 0x52, 53, 54, 55 H set to default;  
    // check hearder
    spiWrite(0x3f, 's');
    spiWrite(0x40, 'o');
    spiWrite(0x41, 'n');
    spiWrite(0x42, 'g');
    spiWrite(0x43, 0xff); // all the bit to be checked
    spiWrite(0x44, 0xff); // all the bit to be checked
    spiWrite(0x45, 0xff); // all the bit to be checked
    spiWrite(0x46, 0xff); // all the bit to be checked  
    // 0x56 ---------0x6c 
    spiWrite(0x6d, 0x0f); // set power max power
    spiWrite(0x79, 0x0); // no hopping
    spiWrite(0x7a, 0x0); // no hopping
    // Gfsk, fd[8] =0, no invert for Tx/Rx data, fifo mode, txclk -->gpio
    spiWrite(0x71, 0x22); 
    spiWrite(0x72, 0x38); // frequency deviation setting to 45k = 72*625
    spiWrite(0x73, 0x0);
    spiWrite(0x74, 0x0); // no offset
    //band 434
    spiWrite(0x75, 0x53); // hbsel = 0, sbsel =1 ???, fb = 19
    spiWrite(0x76, 0x64); // 25600= 0x6400 for 434Mhz
    spiWrite(0x77, 0x00);    
}

void rfm22bSetReady(void)
{
#if DEBUG==1
    transmitStrUSART0("RFM22B Setting Ready Mode\r\n");

    transmitStrUSART0(" Register 0x03:");    
    sendByteToHexUart(spiRead(0x03));

    transmitStrUSART0(" Register 0x04:");    
    sendByteToHexUart(spiRead(0x04));
    
    transmitStrUSART0("\r\n");
#else
    spiRead(0x03);
    spiRead(0x04);
#endif
             
    spiWrite(0x07, RF22B_PWRSTATE_READY); 
}

void rfm22bSetSleep(void)
{
    spiWrite(0x07, RF22B_PWRSTATE_READY);

#if DEBUG==1
    transmitStrUSART0("RFM22B Setting Sleep Mode\r\n");

    transmitStrUSART0(" Register 0x03:");    
    sendByteToHexUart(spiRead(0x03));

    transmitStrUSART0(" Register 0x04:");    
    sendByteToHexUart(spiRead(0x04));
    
    transmitStrUSART0("\r\n");
#else
    spiRead(0x03);
    spiRead(0x04);
#endif 

    spiWrite(0x07, RF22B_PWRSTATE_POWERDOWN);    
}

void rfm22bSendByte(unsigned char value)
{
   
    transmitStrUSART0("RFM22B Sending Data:");  
    sendByteToHexUart(value);
    transmitStrUSART0("\r\n");  
    
    rfm22bSetReady();
    
    RF_PORT &= ~(1<<RF_RXEN); // RXEN low
    RF_PORT |= (1<<RF_TXEN); // TXEN High

    // disABLE AUTO TX MODE, enable multi packet clear fifo
    spiWrite(0x08, 0x03); 
    // disABLE AUTO TX MODE, enable multi packet, clear fifo
    spiWrite(0x08, 0x00); 

    // ph +fifo mode
    spiWrite(0x34, 64); // 64 nibble = 32byte preamble
    spiWrite(0x3e, 1); // total tx 1 byte
    spiWrite(0x7f, value); // Insert to FIFO 
    spiWrite(0x05, RF22B_PACKET_SENT_INTERRUPT);
    
#if DEBUG==1
    transmitStrUSART0("RFM22B Clearing IRQ\r\n");

    transmitStrUSART0(" Register 0x03:");    
    sendByteToHexUart(spiRead(0x03));

    transmitStrUSART0(" Register 0x04:");    
    sendByteToHexUart(spiRead(0x04));
    
    transmitStrUSART0("\r\n");
#else
    spiRead(0x03);
    spiRead(0x04);
#endif 
    
    spiWrite(0x07, RF22B_PWRSTATE_TX); // to tx mode

    while(RF_PIN & (1<<RF_IRQ)); // wait for interruption
    
    rfm22bSetReady();
    
    RF_PORT &= ~(1<<RF_RXEN); // RXEN low
    RF_PORT &= ~(1<<RF_TXEN); // TXEN low
    
    _delay_ms(50);
}

#if DEMO_RX==1  
void rfm22bRxReset(void)
{
    spiWrite(0x07, RF22B_PWRSTATE_READY);
    // threshold for rx almost full, interrupt when 1 byte received
    spiWrite(0x7e, 1); 
    spiWrite(0x08, 0x03); //clear fifo disable multi packet
    spiWrite(0x08, 0x00); // clear fifo, disable multi packet
    spiWrite(0x07, RF22B_PWRSTATE_RX ); // to rx mode
    spiWrite(0x05, RF22B_Rx_packet_received_interrupt);
    
#if DEBUG==1
    transmitStrUSART0(" Register 0x03:");    
    sendByteToHexUart(spiRead(0x03));

    transmitStrUSART0(" Register 0x04:");    
    sendByteToHexUart(spiRead(0x04));
    
    transmitStrUSART0("\r\n");
#else
    spiRead(0x03);
    spiRead(0x04);
#endif 
}
 
void rfm22bSetRxMode(void)
{
    RF_PORT &= ~(1<<RF_RXEN); // RXEN low
    RF_PORT &= ~(1<<RF_TXEN); // TXEN low
    
 #if DEBUG==1   
    transmitStrUSART0("RFM22B Setting Rx Mode\r\n");    
 #endif  
  
    rfm22bSetReady();
     _delay_ms(50);
     
    RF_PORT |=  (1<<RF_RXEN); // RXEN High
    RF_PORT &= ~(1<<RF_TXEN); // TXEN low
    
    rfm22bRxReset();
}
#endif
#if DEBUG==1
void rfm22bReadAllRegisters(void)
{
    //***  TEST: Read all registers ***//
    unsigned char i;
    transmitStrUSART0("Reading all registers:");    
    for(i=0; i<0x80; i++)
    {
        transmitStrUSART0("REG[ ");
        sendByteToHexUart(i);
        transmitStrUSART0("]= ");
        sendByteToHexUart(spiRead(i));
        transmitStrUSART0("\r\n");
    }  
}
#endif
int main(void)
{
    initSPI();              // initialize SPI
    initUSART0(4800);       // initialize USART0

    //POWER ON DELAY for RFM22B
    _delay_ms(1000);        
          
#if DEBUG==1
    rfm22bReadAllRegisters();
#endif
 
#if DEMO_TX==1  
    rfm22bInit();
    //*** TRANSMIT ***//    
    unsigned char count=0;
    while(1)
    {
        rfm22bSendByte(count++);
        _delay_ms(1000);
    } 
#elif DEMO_RX==1   
    rfm22bInit(); 
    //*** RECEIVE ***//
    rfm22bSetRxMode();
    
    while(1)
    {
        while(RF_PIN & (1<<RF_IRQ)); // wait for interruption        
        
#if DEBUG==1
        transmitStrUSART0("RFM22B Clearing IRQ\r\n");

        transmitStrUSART0(" Register 0x03:");    
        sendByteToHexUart(spiRead(0x03));

        transmitStrUSART0(" Register 0x04:");    
        sendByteToHexUart(spiRead(0x04));
        
        transmitStrUSART0("\r\n");
#else
        spiRead(0x03);
        spiRead(0x04);
#endif 
        
        transmitStrUSART0("RFM22B Receiving Data: ");                    
        sendByteToHexUart(spiRead(0x7f));
        
        transmitStrUSART0("\r\n");
        
        _delay_ms(1000);
        rfm22bSetRxMode(); // rx reset
    }
#endif     
    return 0;
}
