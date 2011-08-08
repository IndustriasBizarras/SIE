#ifndef WIDGETDISPLAY_H
#define WIDGETDISPLAY_H
#include <QWidget>


class WidgetDisplay: public QWidget
{
    Q_OBJECT
    public:
    WidgetDisplay(QWidget *parent =0);

    public slots:
    void set_init_point(int h, int v);
    void add_signal(QString name);
    void add_vector (QString valores);
    void add_vector2(QString valores);
    void add_size_word(int size);
    void pintar(QPainter *painter, int valor, QString nombre);
    void set_init(int value);

    protected:
    void paintEvent(QPaintEvent *event);

    private:

    QString temp_value;
    QString valor_vector;
    QVector <QString> name_signals;
    QVector <QString> vectors;
    QVector <QString> vectors2;
    QVector <int> size_word;

    int x;
    int y;
    int aux;
    int hi, vi;
    int h_max, v_max;
    int h_sup, v_sup;
    int init;
    int last_value;
    int cont_vectors;
    int size_name;

    int width;
    int inter_line;
    int xo;
    int yo;
    int after_name;
    int yo_barra;

};

#endif // WIDGETDISPLAY_H
