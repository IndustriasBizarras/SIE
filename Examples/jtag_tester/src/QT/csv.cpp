#include <widgetdisplay.h>
#include <QtGui>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QList>
#include <QTextStream>
#include "csv.h"
#include <iostream>
#include <stdio.h>
#include <QGraphicsView>
#include <termio.h>

csv::csv(QWidget *parent): QWidget (parent)
{
    setupUi(this); // this sets up GUI
 
}

void csv::get_dir(QString csv, QString vcd, QString bit)
{
    dir_csv=csv;
    dir_vcd=vcd;
    dir_bit=bit;
}



int csv::bsdl_position(QString pin_number, QString status){          //status puede ser igual a input, output3 o controlr

    QString pin_bsdl, position, alias_status;
    QString line;
    QString temp;
    QStringList pin;

    int bandera=0;



    QFile file2("/usr/bin/xc3s500e_vq100.bsd");
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::about(this,"Error", "Error opening bsdl file");
        return -1;
    }
    QTextStream in2(&file2);

    if(status=="controlr")          //El if se realiza debido a que la posición que en el bsdl, en el renglón de la señal "controlr" no se encuentra referenciado el número del pin. Sin embargo, se puede comprobar en el bsdl de la xc3s500e_vq100 que la señal cotrolr se encuentra una posición atrás de la señal output3 del pin.
        alias_status="output3";
    else
        alias_status=status;

    //Señal en el .bsdl
    while (!in2.atEnd()) {
        line = in2.readLine();

        //Busca en el encabezado para mirar el nombre real de la señal
        if(line.contains(pin_number,Qt::CaseInsensitive)==true && bandera==0){
            pin=line.split(":");
            pin_bsdl=pin[0];
            pin_bsdl=pin_bsdl.replace("\"","");
            pin_bsdl=pin_bsdl.simplified();

            bandera=1;

        //Busca la posición del pin en el bsdl
        }else if(line.contains(pin_bsdl,Qt::CaseInsensitive)==true && line.contains(alias_status,Qt::CaseInsensitive)==true &&
                            bandera==1){
            if(status=="controlr")
                line=in2.readLine(); //Avanza un renglón para obtener la posición de la señal controlr.

            pin=line.split("(");
            position=pin[0];
            position=position.replace("\"",""); //Elimina las comillas
            position=position.simplified(); //Elimina los espacios
            return position.toInt();
        }
    }

    //Detección de errores

    if(bandera==0){
        temp=temp.append("Cannot find pin \"");
        temp=temp.append(pin_number);
        temp=temp.append("\" in .bsd");
        QMessageBox::about(this,"Error",temp);
    }else{
        temp=temp.append("Pin \"");
        temp=temp.append(pin_number);
        temp=temp.append("\" doesn't have the status \"");
        temp=temp.append(status);
        temp=temp.append("\" in .bsd");
        QMessageBox::about(this,"Error",temp);
    }
    return -1;
}



QString csv::pin_alias_status(QString signal){                   //Entrega el estado del pin y el número respectivo separado por una coma. Ej - P38,BIDIR

    QString line;
    QString temp;
    QStringList pin;

    //La posición de los registros en el bsdl se encuentran por < > y no por [ ]
    //signal=signal.replace("[","<");
    //signal=signal.replace("]",">");


    QFile file(dir_csv.toAscii().data());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::about(this,"Error", "Error opening csv file");
        return "error";
    }
    QTextStream in(&file);


    while (!in.atEnd()) {
       line = in.readLine();
       if(line.contains("#",Qt::CaseInsensitive)!=true && line.isEmpty()!=true){
            pin=line.split(",");
            temp=pin[1];
            if(signal==pin[1]){
                line.clear();
                line.append(pin[0]);
                   line.append(",");
                line.append(pin[4]);
                return line;
            }
        }
    }

    return "n/a";              //La señal no se encuentra en el .csv
}





void csv::script(){

    FILE *fp1;

    fp1 = fopen("script_jtag.txt", "w");

    fprintf(fp1,"cable jz47xx\n");
    fprintf(fp1,"detect\n");
    fprintf(fp1,"instruction CFG_OUT 000100 BYPASS\n");
    fprintf(fp1,"instruction CFG_IN 000101 BYPASS\n");
    fprintf(fp1,"instruction JSTART 001100 BYPASS\n");
    fprintf(fp1,"instruction JPROGRAM 001011 BYPASS\n");
    fprintf(fp1,"pld load "+dir_bit.toLatin1()+"\n");
    fprintf(fp1,"reset\n");
    fprintf(fp1,"quit");
    fclose(fp1);    
    system("jtag script_jtag.txt");

    QFile file(dir_vcd.toAscii().data());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::about(this,"Error", "Error opening GTKWave file");
        return;
    }

    QTextStream in(&file);

    int contador=0;
    int bandera=0;
    int posicion;
    int lim_sup, lim_inf, temp_int;

    //Registro boundary scan por defecto para la función INTEST
    QString reg_bscan="001101101101100110110110011011011011001101101101100110110110110011011011011001101101100100110110110110011011011011001101101101100110110110011011011011001011011001101101101101100011011001101101101101101101100010011011011011000110110110110110001101101101101100011011001101101101101101101100011011000110110110110011011011001101101101100110110110110011011011011001101101101100110110110110011011011011001101101101100110110110110011011011001101101101111110110011011011011011000110110011011011011011011011000110110110110110001101101101101100011011011011011000110110011011011011011011011000110110";

    QString line;
    QString var;
    QString registros;

    QString names, sizes, alias;
    QStringList names_list, alias_list, sizes_list;

    QStringList temp, temp2;              //Variables auxiliares

    FILE *fp;

    fp = fopen("script.txt", "w");

    //Encabezado del script
    fprintf(fp,"cable jz47xx\n");
    fprintf(fp,"detect\n");
    fprintf(fp,"instruction intest\n");
    fprintf(fp,"shift ir\n");

    names.clear();
    sizes.clear();
    alias.clear();

    while (!in.atEnd()) {
       line = in.readLine();
       if(line.startsWith("$scope",Qt::CaseInsensitive)==true){         //Se necesita leer a partir del segundo scope - Nombre real de las señales en el csv
             bandera=bandera+1;


       }else if(line.startsWith("$var",Qt::CaseInsensitive)==true && bandera==0){

            bandera=bandera+1;       //Linea adicionada debido a que los archivos .vcd generados a partir de VHDL no tienen un primer scope

       }else if(line.startsWith("$var",Qt::CaseInsensitive)==true && bandera==2){    //Lectura de la señal y su alias dentro del archivo



           temp=line.split(" ");
           var=temp[4];

           if(temp[5]!="$end"){                 //Si es un registro, temp[5] guardará los límites o su posición. Si es una variable singular, guardará $end, lo que indicará que no es un registro
               line=temp[5];
               temp2=line.split(":");
               line=temp2[0];
               line=line.replace("[","");
               line=line.replace("]","");
               line.prepend("<");
               line.append(">");

               var.append(line); //Es necesario tomar la posición de uno de los bits del registro, para que se pueda reconocer su estado en el .csv
           }
           line=pin_alias_status(var);

           if(line=="n/a"){
               continue;
           }
           temp2=line.split(","); //Se toma el estado del pin


           if(temp2[1]=="INPUT"||temp2[1]=="BIDIR"){        //Comprueba si el pin solicitado es de entrada o bidireccional
              line=temp[5];
               if(line.contains(":")==true)        //Contempla el caso en que solo se encuentre declarada la posición de un registro en el vcd, por ejemplo registro [3] y no registro [3:0]. Estos casos se cosideran como variables singulares.
                   names.append(temp[4]);
               else
                   names.append(var);

               names.append(" ");


               alias.append(temp[3]);
               alias.append(" ");

               sizes.append(temp[5]);
               sizes.append(" ");

               contador++;

           }

       }else if(line.startsWith("$enddefinitions",Qt::CaseInsensitive)==true){       //Termina la definición de las señales

           names_list=names.split(" ");          //Problemas con la función qstringlist::append
           alias_list=alias.split(" ");
           sizes_list=sizes.split(" ");

           bandera=0;                            //Se reinicializa la bandera

       }else if(line.startsWith("#",Qt::CaseInsensitive)==true){
           line=line.replace("#","");

           if(bandera==0){
               bandera=1;
           }else if(bandera==1){
               fprintf(fp,"dr %s\n", reg_bscan.toAscii().data());
               fprintf(fp,"shift dr\n");
               bandera=2;
           }else{
               fprintf(fp,"dr %s\n", reg_bscan.toAscii().data());
               fprintf(fp,"shift dr\n");
               fprintf(fp,"dr out\n");
           }


       }else if(line.startsWith("0")==true || line.startsWith("1")==true ||line.startsWith("x")==true
                ||line.startsWith("z")==true){              //Variables singulares

            if(line.startsWith("x")==true||line.startsWith("z")==true){           //Se envían ceros en caso de que se presenten estas variables.
                line=line.replace(0,1,"0");
            }
            var=line.at(0);
            line.remove(0,1);                             //Remueve el caracter en la posición 0

            for (int i=0; i<contador; i++){
                  if(line==alias_list[i]){                  //Verifica si el caracter se encuentra en la lista
                      line=pin_alias_status(names_list[i]);
                      temp2=line.split(","); //Es necesario tomar el número del pin. Ej P38

                      posicion=bsdl_position(temp2[0],"input");
                      reg_bscan=reg_bscan.replace(587-posicion,1,var);         //Reemplaza en el registro boundary scan

                      break;
                  }
             }



        }else if(line.startsWith("b")==true){          //Registros

            line.remove(0,1);           //Remueve el caracter en la posición 0 ("b")
            temp=line.split(" ");
            registros=temp[0];          //Valor del registro
            registros=registros.replace("x","0");
            registros=registros.replace("z","0"); //Reemplaza con cero en caso de encontrarse con "x" y "z"

            for (int i=0; i<contador; i++){
                if(temp[1]==alias_list[i]){                  //Verifica si el caracter se encuentra en la lista

                    var=sizes_list[i];                       //Valor de los límites del registro
                    var=var.replace("[","");
                    var=var.replace("]","");
                    temp=var.split(":");

                    var=temp[0];
                    lim_sup=var.toInt();                     //Obtención límite superior

                    var=temp[1];
                    lim_inf=var.toInt();                     //Obtención límite inferior


                    temp_int=registros.size();                     //El archivo no muestra los ceros a la izquierda


                    for(int j=0; j<=abs(lim_sup-lim_inf); j++){
                        var.clear();

                        var.append(names_list[i]);       //Nombre del vector correspondiente en el .csv
                        var.append("<");
                        if(lim_sup>lim_inf){                            //Little Endian
                            var.append(line.setNum(lim_inf+j));
                        }else{                                          //Big Endian
                            var.append(line.setNum(lim_inf-j));
                        }
                        var.append(">");

                        line=pin_alias_status(var);
                        temp2=line.split(","); //Es necesario tomar el número del pin. Ej P38

                        posicion=bsdl_position(temp2[0],"input");


                        if(j<temp_int){
                            reg_bscan=reg_bscan.replace(587-posicion,1,registros.at(temp_int-j-1));     //Se lee de derecha a izquierda
                        }else{
                            reg_bscan=reg_bscan.replace(587-posicion,1,line.setNum(0));     //Reemplaza con ceros si ya no hay mas caracteres
                        }

                    }
                    break;

                }

            }

        }

    }


    fprintf(fp,"dr %s\n", reg_bscan.toAscii().data());      //Retardo de final de lista
    fprintf(fp,"shift dr\n");
    fprintf(fp,"dr out\n");


    fprintf(fp,"shift dr\n");
    fprintf(fp,"dr out\n");
    fprintf(fp,"reset\n");
    fprintf(fp,"quit");

    fclose(fp);

    system("jtag script.txt");
    remove("script_jtag.txt");

}


void csv::boundary_scan(){

    FILE *fp2;

    fp2 = fopen("script_jtag2.txt", "w");

    fprintf(fp2,"cable jz47xx\n");
    fprintf(fp2,"detect\n");
    fprintf(fp2,"instruction CFG_OUT 000100 BYPASS\n");
    fprintf(fp2,"instruction CFG_IN 000101 BYPASS\n");
    fprintf(fp2,"instruction JSTART 001100 BYPASS\n");
    fprintf(fp2,"instruction JPROGRAM 001011 BYPASS\n");
    fprintf(fp2,"pld load /root/Generador_Script/pulsa.bit\n");
    fprintf(fp2,"reset\n");
    fprintf(fp2,"quit");
    fclose(fp2);
    system("jtag script_jtag2.txt");

    QStringList pin;
    QString signals_name1;
    QString line;

    QFile file(dir_csv.toAscii().data());// Lectura CSV
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::about(this,"Error", "Error opening CSV file");
        return;
    }
    QTextStream in(&file);

    QFile file2("register_out.txt");
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::about(this,"Error", "Error opening UrJtag file");
        return;
    }

    while (!in.atEnd()) {
       line = in.readLine();
       if(line.contains("#",Qt::CaseInsensitive)!=true && line.isEmpty()!=true){
            pin=line.split(",");
            if(pin[4]=="INPUT" || pin[4]=="OUTPUT" || pin[4]=="BIDIR"){
              signals_name1=signals_name1.append(pin[1]+',');
            }
        }
    }

   signals_name=signals_name1.split(',');

    QTextStream in2(&file2);
    line=in2.readAll();
    remove("register_out.txt");
    registers=line.split("\n");
    remove("script_jtag2.txt");
}

void csv::pulsadores()
{
    RAM=initFPGA_RAM();


    cont2=0;
    photo=0;

    result_out();

    cont_hi=0;
    cont_vi=0;


    startTimer(100);
}

JZ_REG *csv::initFPGA_RAM()
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

void csv::timerEvent(QTimerEvent*)
{
        int pb;
        pb=RAM[0]&0x00000003;
        if(pb==2)
        {
            cont_hi=cont_hi+1;
        }
        if(pb==1)
        {
            cont_vi=cont_vi+1;
        }
        if(pb==0)
        {
            mipixmap=QPixmap::grabWidget(miwidget);
            mipixmap.save("photo"+QString::number(photo)+".png","PNG");
            photo=photo+1;
        }
        if(cont_vi>cont2-1)
        {
            cont_vi=0;
        }
        if(cont_hi>registers.size())
        {
            cont_hi=0;
        }

        miwidget->set_init_point(cont_hi, cont_vi);
        update();
}

void csv::result_out()
{

    miwidget=new(WidgetDisplay);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(miwidget);
    layout->setMargin(1);
    setLayout(layout);

    int count, count2, bsdl_pos, bsdl_pos_ctrl;
    count2=registers.size()-1;
    count=signals_name.size()-1;
    bsdl_pos=0;
    bsdl_pos_ctrl=0;

    QString name_aux="h,h,h";
    QString name_aux2="init_name_aux2";
    QString next_name_aux="init_next_name_aux";
    QString valor_vector;
    QString line;
    QStringList name_aux_list=name_aux.split(",");
    QString vector;
    QString vector2;
    QString vector_orden;
    QString pin_number, status, var;
    QStringList pin;


   signals_name.sort(); //Ordena las senales
   signals_name.removeFirst();
   signals_name.append(" ");

    int cont;

    for(int i=0; i<count; i++) //recorre señal por señal
    {


        name_aux=signals_name[i];
        name_aux_list=name_aux.split("<");
        name_aux=name_aux_list.at(0);

       next_name_aux=signals_name[i+1];
        name_aux_list=next_name_aux.split("<");
        next_name_aux=name_aux_list.at(0);

        if(name_aux==next_name_aux && name_aux!=name_aux2)
        {
            miwidget->add_signal(name_aux);

            vector2.append(name_aux);
            for(int h=0; h<count2;h++)
            {
                vector_orden.clear();
                valor_vector.clear();
                cont=i;
                while(name_aux==next_name_aux)
              {
              ///////////////////////////
                    line=pin_alias_status(signals_name[cont]);         //Line guarda el estado de la señal (INPUT, OUTPUT, BIDIR) y el número del pin
                    pin=line.split(",");

                    pin_number=pin[0];
                    status=pin[1];

                    if(status=="BIDIR"){
                        bsdl_pos_ctrl=bsdl_position(pin_number,"controlr");         //controlr informa sobre el estado del pin bidireccional ("1" si se encuentra como entrada, "0" si se encuentra como salida)

                    }else if(status=="INPUT")
                        bsdl_pos=bsdl_position(pin_number,"input");

                    else if(status=="OUTPUT")
                        bsdl_pos=bsdl_position(pin_number,"output3");

                    else{                                                           //Detección de errores
                        line=line.append("The signal \"" + signals_name[cont] + "\" doesn't have a status.");
                        QMessageBox::about(this,"Error", line);
                        return;
                    }

               // pos=bsdl(signals_name[cont]);
                line=registers[h];
                if(status=="BIDIR"){
                    var=line.at(587-bsdl_pos_ctrl);
                    if(var=="1")
                        bsdl_pos=bsdl_position(pin_number,"input");
                    else
                        bsdl_pos=bsdl_position(pin_number,"output3");
                }
              /////////////////////////////
                valor_vector.append(line.at(587-bsdl_pos));
                name_aux2=name_aux;
                cont=cont+1;
                name_aux_list.clear();
                name_aux=signals_name[cont];
                name_aux_list=name_aux.split("<");
                name_aux=name_aux_list.at(0);
             }
                ///

                for(int z=0;z<valor_vector.size();z++)
                {
                    vector_orden.append(valor_vector.at(valor_vector.size()-z-1));
                }
                ///
               vector2.append(vector_orden);
               vector.append('2');
               name_aux=name_aux2;
            }
            miwidget->add_vector2(vector2);
            miwidget->add_size_word(vector_orden.size());
            miwidget->add_vector(vector);
            vector.clear();
            vector2.clear();
            cont2=cont2+1;
        }
        miwidget->add_signal(signals_name[i]);


        line=pin_alias_status(signals_name[i]);         //Line guarda el estado de la señal (INPUT, OUTPUT, BIDIR) y el número del pin
        pin=line.split(",");

        pin_number=pin[0];
        status=pin[1];

        if(status=="BIDIR"){
            bsdl_pos_ctrl=bsdl_position(pin_number,"controlr");         //controlr informa sobre el estado del pin bidireccional ("1" si se encuentra como entrada, "0" si se encuentra como salida)

        }else if(status=="INPUT")
            bsdl_pos=bsdl_position(pin_number,"input");

        else if(status=="OUTPUT")
            bsdl_pos=bsdl_position(pin_number,"output3");

        else{                                                           //Detección de errores
            line=line.append("La señal \"" + QString(signals_name[i]) + "\" doesn't have a status.");
            QMessageBox::about(this,"Error", line);
            return;
        }

        for (int j=0; j<count2; j++) //recorre vector por vector
        {
            line=registers[j];
            if(status=="BIDIR"){
                var=line.at(587-bsdl_pos_ctrl);
                if(var=="1")
                    bsdl_pos=bsdl_position(pin_number,"input");
                else
                    bsdl_pos=bsdl_position(pin_number,"output3");
            }

            if(line.at(587-bsdl_pos)=='1')
            {
                vector.append('1');
            }
            else
            {
                vector.append('0');
            }
        }
        miwidget->add_vector(vector);
        vector.clear();
        cont2=cont2+1;
    }
    miwidget->set_init(1);
    update();

}

