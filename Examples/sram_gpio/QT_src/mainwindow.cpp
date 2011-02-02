#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RAM=initFPGA_RAM();
    LED=initGPIO_LED();
    iter=0;

    startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

JZ_PIO *
MainWindow::initGPIO_LED()
{
    JZ_PIO *pio;

    pio = jz_gpio_map (LED_PORT);
    jz_gpio_as_output (pio, LED_PIN);
    jz_gpio_clear_pin (pio, LED_PIN);

    return pio;
}

JZ_REG *
MainWindow::initFPGA_RAM()
{
    JZ_PIO *pio;
    JZ_REG *virt_addr;

    pio = jz_gpio_map (CS2_PORT);
    jz_gpio_as_func (pio, CS2_PIN, 0);

    virt_addr = (JZ_REG *) (jz_mmap(0x13010000) + 0x18);

    if (*virt_addr != 0x0FFF7700)
    {
        *virt_addr = 0x0FFF7700;
        printf ("ADC: Configuring CS2 8 bits and 0 WS: %08X\n", *virt_addr);
    }
    else
        printf ("ADC: CS2, already configured: %08X\n", *virt_addr);

    virt_addr = (JZ_REG *) jz_mmap (0x14000000);

    return virt_addr;
}


void
MainWindow::timerEvent(QTimerEvent*)
{
    QString plain_text;

    jz_gpio_out (LED, LED_PIN, iter&0b1);

    if(iter&0b1) plain_text = "[ON]"; else plain_text = "[OFF]";
    ui->label_2->setText("LED is " + plain_text);
    iter++;

    /* Escribiendo en RAM */
    plain_text="\t**Iteration: "+QString::number(iter)+"**\nW:";
    for(int i = 0; i<14; i++)
    {
        RAM[i]= i & 0xFF;
        plain_text+="["+QString::number(i&0xFF)+"]";
    }

    /* Leyendo de RAM */
    int temp;
    plain_text+="\nR:";
    for(int i = 0; i<14; i++)
    {
        temp=RAM[i];
        plain_text+="["+QString::number(temp)+"]";
    }
    ui->plainTextEdit->appendPlainText(plain_text);
}
