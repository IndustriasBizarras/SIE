#include "widgetdisplay.h"
#include <QtGui>


WidgetDisplay::WidgetDisplay(QWidget *parent): QWidget(parent)
{
    width = 20;       //Ancho de los pulsos
    inter_line = 15;
    xo = 5;
    yo = 3*width;
    after_name = 3.5*width;   //Margen antes de las formas de onda
    yo_barra=0.5*yo;
    init=0;
    h_max=13;    //Máximo número de vectores de prueba en pantalla video-activa
    v_max=10;    //Máximo número de señales en pantalla video-activa
    vi=0;        //vi=vector de prueba inicial a graficar
    hi=0;        //hi=señal inicial a graficar
}

void WidgetDisplay::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setPen(Qt::green);
    painter.setFont(QFont("Arial", 0.5*width));
    painter.fillRect(0,0,320,240,Qt::black);

    if(init==1)
    {
        v_sup=vi+v_max;
        h_sup=hi+h_max;
        if(vi+v_max>name_signals.size())  v_sup=name_signals.size();
        if(hi+h_max>vectors.at(0).size())    h_sup=vectors.at(0).size();

        pintar(&painter,8," ");//linea de tiempo e inicializacion de algunas variables

        for(int i=vi; i<v_sup;i++)
        {
            pintar(&painter,2,name_signals.at(i));//nombre señales
            for(int j=hi;j<h_sup;j++)
            {
                if(vectors.at(i).at(j)=='1')
                {
                    pintar(&painter,1," ");//Estado alto
                }
                else if(vectors.at(i).at(j)=='0')
                {
                    pintar(&painter,0," ");//Estado bajo
                }
                else if(vectors.at(i).at(j)=='2')
                {
                    size_name=name_signals.at(i).size();
                    for(int z=0; z<vectors2.size();z++)
                    {
                        if(name_signals.at(i)==vectors2.at(z).left(size_name))
                        {
                            valor_vector.clear();
                            for(int w=0; w<size_word.at(z);w++)
                            {
                                valor_vector.append(vectors2.at(z).at(size_name+j*size_word.at(z)+w));
                            }
                            pintar(&painter,5,valor_vector);//valor vectores
                        }
                    }
                }
            }
            pintar(&painter,3," ");//salto linea
        }
       // pintar(&painter,7," ");//lineas guias opcional
    }
}


void WidgetDisplay::set_init(int value)//indica que todos los vectores están listos para ser graficados
{
    init=value;
}

void WidgetDisplay::add_signal(QString name)//se agrega el nombre de una nueva señal al vector de señales
{
    name_signals.append(name);
}

void WidgetDisplay::add_vector(QString valores)//se agrega los valores correspondientes (1's y 0's) asociados a cada señal y se guardan en posiciones independientes
{
    vectors.append(valores);
}

void WidgetDisplay::add_vector2(QString valores)//se agrega los valores correspondientes a señales agrupadas
{
    vectors2.append(valores);
}
void WidgetDisplay::add_size_word(int size)
{
    size_word.append(size); //size_word guarda el tamaño de las señales agrupadas (ej. salida[0], salida [1]...salida [n-1], entonces size_word=n)
}

void WidgetDisplay::set_init_point(int h, int v)
{
    vi=v;
    hi=h;
}

void WidgetDisplay::pintar(QPainter *painter, int valor, QString nombre)
{
    int k;
    painter->setPen(Qt::green);

switch (valor)
    {
        case 1: //Estado alto
                if(last_value==2 || last_value==1)
                {
                    painter->drawLine(x,y-width,x+width,y-width);
                }
                else if(last_value==0)
                {
                    if(x!=after_name) painter->drawLine(x, y, x, y-width);
                    painter->drawLine(x,y-width,x+width,y-width);
                }
                last_value=valor;
                painter->setPen(Qt::gray);
                painter->drawLine(x,y+0.4*width,x+width,y+0.4*width);
                x=x+width;
                aux=x;
                break;
        case 0: //Estado bajo
                if(last_value==2 || last_value==0)
                {
                    painter->drawLine(x,y,x+width,y);
                }
                else if(last_value==1)
                {
                    if(x!=after_name) painter->drawLine(x,y,x,y-width);
                    painter->drawLine(x,y,x+width,y);
                }
                last_value=valor;
                painter->setPen(Qt::gray);
                painter->drawLine(x,y+0.4*width,x+width,y+0.4*width);
                x=x+width;
                aux=x;
                break;
        case 2: //nombre señal
                painter->setFont(QFont("Arial", 0.5*width));
                painter->setPen(Qt::white);
                painter->drawText(x,y,nombre.left(10));
                x=after_name;
                break;
        case 3: //salto de linea
                x=xo;
                y=y+width+inter_line;
                break;
        case 4:
                break;
        case 5:// valores vectores
                bool ok;
                if(temp_value!=nombre){
                painter->drawLine(x-0.1*width,y+0.3*width,x+0.1*width,y-0.8*width);
                painter->drawLine(x-0.1*width,y-0.8*width,x+0.1*width,y+0.3*width);


                painter->drawLine(x+0.1*width,y+0.3*width, x+0.9*width,y+0.3*width);
                painter->drawLine(x+0.1*width,y-0.8*width, x+0.9*width,y-0.8*width);


                painter->setPen(Qt::white);
                painter->setFont(QFont("Arial", 0.7*width));
                painter->drawText(x+0.2*width,y,QString::number(nombre.toInt(&ok,2)));
                }
                else{
                    painter->drawLine(x-0.1*width,y+0.3*width, x+0.9*width,y+0.3*width);
                    painter->drawLine(x-0.1*width,y-0.8*width, x+0.9*width,y-0.8*width);
                }
                temp_value=nombre;
                x=x+width;
                break;
        case 6: //nombre vectores
                painter->setFont(QFont("Arial", 0.5*width));
                painter->setPen(Qt::white);

                nombre.append('[');
                nombre.append(']');
                painter->drawText(x,y,nombre.left(10));
                x=after_name;
                break;
        case 7: //Lineas Guías
                painter->setPen(Qt::blue);
                k=aux/(5*width);
                for(int i=1;i<=k;i++){
                painter->drawLine(i*5*width,yo_barra, i*5*width,y);
                }
                break;
        case 8://linea tiempo
            last_value=2;//
                temp_value="initial";//
                cont_vectors=0;
                painter->setPen(Qt::white);
                painter->setFont(QFont("Arial", 0.8*width));
                painter->drawText(5,yo_barra,"SimuSie");
                painter->setFont(QFont("Arial", 0.5*width));
                x=after_name;
                y=yo_barra;
                for(int i=hi;i<hi+h_max;i++)
                {
                    painter->drawLine(x,y,x+width,y);
                    painter->drawLine(x+width,y, x+width,y-0.4*width);
                    painter->drawText(x+width,y-0.5*width,QString::number(i));
                    x=x+width;
                }
                painter->drawLine(after_name,yo_barra, after_name, 250);//barra vertical
                x=xo;
                y=yo;
               break;
    }
}


