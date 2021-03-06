#include "moto_v2.h"
#include "ui_moto_v2.h"
#include <QWSServer>
#include <fcntl.h>
#include <stdlib.h>
#include <QtCore>
#include  <QtGui>
#include <stdio.h>
#include <string.h>

using namespace std;

//Temporal variables.
bool a=false;
bool active =false;
bool play=0;
//using namespace std;
int filenum;
unsigned char buf[40];
char spath_old[30];

moto_v2::moto_v2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::moto_v2)
{
    //This lines force the cursor to dissappear from the screen
    ui->setupUi(this);
    if ( QWSServer::isCursorVisible() == true ) {
    QWSServer::setCursorVisible( false );
    }

    //Timer creation and initialization, timer 1 will work as the update trigger, and
    // timer2 turns off the direction lights after 0.5 seconds
    timer1= new QTimer(this);
    timer1->start(5);
    timer2= new QTimer(this);


    //The RPM value is stored by the driver in the /dev/rpm, thus we have to open it
    // in order to use it later. It's assined to an int which corresponds to the data
    // generated by the hardware and is updated wheenever the rpm value is needed.
    filenum = open("/dev/rpm",O_RDWR);

    //ADC setup taking 2 samples per channel qithout muxong the channel
    ADC1 = new ADCw;
    cont=0;//Counts the number of samples already taken
    ADC1->testADC();//Initial ADC tests to check voltage references and it's general behavior.
    ADC1->setBufferLen(2);
    ADC1->setMuxChannels(0);
    ADC1->setClockDiv(ADC_SPI_CLKDIV_MIN); //Max. speed
    printf("\nTaking 1 sample by channel at Fs=99KHz (trigger=50ms)\n");

    //Timer connection to their corresponding slots
    connect(timer1,SIGNAL(timeout()),this,SLOT(update_info()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(update_lights()));

    //UI first Setup: the default, values and images are set here.
    // Images are assigned to labels for the ease and convenience of use.
    ui->label_4->setPixmap(QPixmap(":/imagenes/left_off.png"));
    ui->label_5->setPixmap(QPixmap(":/imagenes/right_off.png"));
    update();// Calling the ui update function for the first time.



//%%%%%%%%%%%File System Setup%%%%%%%%%%%%%//
//This lines serve as the filesystem setup which will be used to display and
//manipulate the music files.
    //First the path to the music is set.
    QString spath="/SD_CARD";

    //A QFileSystemModel object is created to hold the filesystem data of the music
    music_file = new QFileSystemModel(this);

    //We filter the ./ and ../ present in the unix filesystem.
    music_file->setFilter(QDir::NoDotAndDotDot |QDir::Files);

    //In order tho show only supported sound files we filter them creating a name
    // filter for QFileSystemModel
    QStringList Extensions;
    Extensions << "*.mp3" << "*.wav" << "*.aac";
    music_file->setNameFilters(Extensions);

//This line forces sorting of the files by name, disabling sorting by tags
    ui->treeView->setSortingEnabled(false);

//The filesystem model is assigned to the QtreeView graphic display system to show it,
// it's given the music folder path defined above as it's root and not needed columns
//(Date modified and type) are hidden to use more efficiently the limited space in
//SIE's display.
    ui->treeView->setModel(music_file);
    ui->treeView->setRootIndex(music_file->setRootPath(spath));
    ui->treeView->hideColumn(3);
    ui->treeView->hideColumn(2);
    ui->treeView->setColumnWidth(0,220);
    ui->treeView->setColumnWidth(1,50);
    ui->stackedWidget->setCurrentIndex(1);//Forcing the initial view of the app to be
    //the bike's information space.


//%%%%%%%%%%Music Daemon Configuration%%%%%%%%%%%%%
//MPD is used as the music subsytem,being ALSA it's base, which plays in the
//background working as a daemon, it can be interfaced from a console or from a
//graphical enviroment. We chose to interface with it using MPC wich is a console
//client for MPD using the system calls.

//Every time the apps starts it removes the old MPD music database and update it's to
//the contents of the /SD_CARD folder.
    system("rm /root/.mpd/database");
    system("/etc/init.d/mpd restart");
//Once MPD is set up the previous playlist is cleared and a new one is created.
    system("mpc clear");
    system("mpc update");
    system("mpc add /");//Here "/" doesn't mean the system root but the music folder
    //root defined in /etc/mpd.conf
    printf("\nAll Set!!\n");
}

moto_v2::~moto_v2()
{
    delete ui;
}

//In order to be able to use the keypad to manipulate our embedded graphical
//enviroment the default key actions must be overridden to do special actions. This is
//done modifying the ui's event system. This doesn't apply to our playlist (Qtreeview)
//wich will receive keys normally (in order to escape from the playlist TAB key must
//be pressed, then this modified key funcionts will work).
bool moto_v2::event(QEvent *event)
{

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
       //If a keypress is detected and it's key_5 the ui space is toggled.Passing from
       //the bike information system to the music player and viceversa.
        if (ke->key() == Qt::Key_5) {
            if(a)
            {
                ui->stackedWidget->setCurrentIndex(1);
                a=false;
            }
            else
            {
                ui->stackedWidget->setCurrentIndex(0);
                a=true;
            }
           return true;
        }
        //If down is pressed the next song in the playlist will be played and if up is
        //pressed the previous one will. This doesn't affect the ability to move up
        //and down the playlist since events are nos overridden in it bay this
        //function.
        if (ke->key() == Qt::Key_Down)
        {
        system("mpc next");
        play=true;
        return true;
        }
        if (ke->key() == Qt::Key_Up)
        {
        system("mpc prev");
        play=true;
        return true;
        }
        //The direction lights were made to work as key presses and assigned to key_1
        //and key_2. Each time one is pressed the corresponding ON image is shown and
        //timer 2 is started to turn them OFF again.
        if (ke->key() == Qt::Key_1)
        {
        ui->label_4->setPixmap(QPixmap(":/imagenes/left_on.png"));
        timer2->start(200);
        return true;
        }
        if(ke->key() == Qt::Key_2)
        {
        ui->label_5->setPixmap(QPixmap(":/imagenes/right_on.png"));
        timer2->start(200);
        return true;
        }
        //If not in the playlist window TAB works as the play/pause toggle.
        if(ke->key() == Qt::Key_Tab)
        {
            if(ui->stackedWidget->currentIndex())
            {
            if(!play)
               {
                  system("mpc play");
                  play=true;
               }
            else{
                system("mpc pause");
                play=false;
                }

            return true;
            }
        }
        }
    //If the key pressed doesn't correspond to one of the above, the event is sent to
    //Qt's normal event handling system
    return QWidget::event(event);
}


//This functions updates the information space in the ui. It handles the battery,
//fuel, rpm and speed meters.
void moto_v2::update_info()
{
    //A counter is set to count the number of samples taken of each of the meters in
    //order to do an average with them later. this is done to reduce noise in the
    //measurements.
if(cont<20)
{
    //Reads and stores samples from the rpm
    read(filenum,buf,sizeof(int));
    rpm_temp[cont]=*((int*)buf);
    //Reads and stores samples from the ADC for the battery and fuel meters.
    read_ADC(bat,fuel);
    val_bat[cont]=(float)bat*0.00322;
    val_fuel[cont]=(float)fuel*0.00322;
    cont++;
}
else
{
    //temporal average variables
    float prom_bat=0,prom_fuel=0,rpm_val=0;
    //Sample sum.
    for(int i=0;i<20;i++)
    {
        prom_bat=prom_bat+val_bat[i];
        prom_fuel=prom_fuel+val_fuel[i];
//The RPM value is received up to 8160 rpm's quantized in steps of 32 rpm.
//This way using the 8-bit bus we recieve int values from 0 to 255 wich corerspond to
//0 to 8160 rpms.
        rpm_val = rpm_val+ (((float)rpm_temp[i])*32.0)/1000.0;
    }
//The averages are calculated for each variable. In the case of bat and fuel a
//percenteage is calculated reflecting the minimun and maximum values reachable in
//real life for the two sensors, for bat that is between 10 and 15 volts -we used here
//the same values for fuel because we couldn't get the measuremtns for the fuel
//sensor-.
    prom_bat=((prom_bat/20)-1.25)/0.65*100;
    prom_fuel=((prom_fuel/20)-1.25)/0.65*100;
    rpm_val=rpm_val/20;
//Speed is calculated form the rpm value, taking into account the bike's gear
//relations.
    speed_val =rpm_val*(2.71)*1000*0.00377*45.72/2;
    ui->label_3->setNum(prom_bat);
//the values in the speed and rpm meters are updated with the calculated ones.
    ui->rmp_meter->setValue(rpm_val);
    ui->speed_meter->setValue(speed_val);
//Default colors for the fuel and bat bars.
    QColor Barra1(0,255,0);
    QColor Barra2(0,255,0);

//Logic to establish the fuel and bat bar colors. From 0 to 15% it should be red
//reflecting very low level. From 15% to 50% color is yellow  and fom 50% up the color
//should be green.
    if(prom_fuel<0)
    {
        Barra2.setRgb(255,0,0);
        ui->qprog_2->setBarColor(Barra2);
        //ui->label_2->setNum(0);
        ui->qprog_2->setValue(0);
    }
    else
    {
        if(prom_fuel>100)
        {
            Barra2.setRgb(0,255,0);
            ui->qprog_2->setBarColor(Barra2);
            //ui->label_2->setNum(100);
            ui->qprog_2->setValue(100);
        }
        else
        {
            if((prom_fuel>0) & (prom_fuel<=20)) Barra2.setRgb(255,0,0);
            if((prom_fuel>20) & (prom_fuel<=50)) Barra2.setRgb(255,255,0);
            if((prom_fuel>50) & (prom_fuel<=100)) Barra2.setRgb(0,255,0);
            ui->qprog_2->setBarColor(Barra2);
            //ui->label_2->setNum(prom_fuel);
            ui->qprog_2->setValue(prom_fuel);
        }
    }

    //Visualizacion del Nivel de Bateria
    if(prom_bat<0)
    {
        Barra1.setRgb(255,0,0);
        ui->qprog->setBarColor(Barra1);
        //ui->label->setNum(0);
        ui->qprog->setValue(0);
    }
    else
    {
        if(prom_bat>=100)
        {
            Barra1.setRgb(0,255,0);
            ui->qprog->setBarColor(Barra1);
            //ui->label->setNum(100);
            ui->qprog->setValue(100);
        }
        else
        {
            if((prom_bat>0) & (prom_bat<=20)) Barra1.setRgb(255,0,0);
            if((prom_bat>20) & (prom_bat<=50)) Barra1.setRgb(255,255,0);
            if((prom_bat>50) & (prom_bat<=100)) Barra1.setRgb(0,255,0);
            ui->qprog->setBarColor(Barra1);
            //ui->label->setNum(prom_bat);
            ui->qprog->setValue(prom_bat);
        }
    }

    rpm_val=0;
    prom_bat=0;
    prom_fuel=0;
    cont=0;
}
}

//Auxiliar function to do the ADC taking sample process
void moto_v2::read_ADC(int &tbat,int &tfuel)
{
    JZ_REG *dataADC;
    dataADC =   ADC1->takeSamplesADC(0);
    tbat    =   (dataADC[0])&0x0FFF;//The value is memory filtered
    dataADC =   ADC1->takeSamplesADC(1);
    tfuel   =   (dataADC[0])&0x0FFF;
}

//Auxiliar function that updates the direction light state to off.
void moto_v2::update_lights(){
    ui->label_4->setPixmap(QPixmap(":/imagenes/left_off.png"));
    ui->label_5->setPixmap(QPixmap(":/imagenes/right_off.png"));
    update();//This only updates the ui view
}

//%%%%%%%%%Playlist manipulation function%%%%%%%%%%%%%
//If an item in the list is activated it's index is saved in a string and sent
//conctenated with MPC's play function in order to play the corresponding song. If the
//song that is playing is pressed again it gets paused.
void moto_v2::on_treeView_activated(QModelIndex index)
{
    int fila=index.row();
    char spath[30];

    //The following three lines are needed in order to make MPC play the correct song.
    //For some reason when selecting an image with a big index it sometimes fails to
    //play the correct song -don't know yet why but this seems to work 90% of the time
    //:P!-.
    system("mpc clear");
    system("mpc update");
    system("mpc add /");

    sprintf(spath,"mpc play %d",fila+1);
    if(strcmp(spath,spath_old)==0)
    {
        strcpy(spath_old,spath);
        play=false;
        system("mpc pause");
    }
    else
    {
        strcpy(spath_old,spath);
        play=true;
        system(spath);
    }
}

