#include "widget.h"
#include "ui_widget.h"

#include <QRandomGenerator>
#include <QFile>
#include <complex>
using std::complex;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    test();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::test()
{
    //  see https://www.youtube.com/watch?v=mkGsMWi_j4Q
    // this 1Hz sine wave with sampling frequency=8Hz
    // should return k(2)=8
    signal.append(0.0);
    signal.append(0.707);
    signal.append(1.0);
    signal.append(0.707);
    signal.append(0.0);
    signal.append(-0.707);
    signal.append(-1.0);
    signal.append(-0.707);

    DFT *data = new DFT();
    QVector<complex<qreal>> my_dft = data->dft(signal);
    quint32 size = static_cast<quint32>(my_dft.size());
    QVector<qreal> magnitude(size, 0.);
    QVector<qreal> phase(size, 0.);

    for (quint32 n = 0; n < size; ++n) {
        magnitude[n] = sqrt( pow(my_dft[n].real(), 2) + pow(my_dft[n].imag(),2) );
        phase[n] = atan( my_dft[n].imag() / my_dft[n].real() );
    }
    plotDft(magnitude);
    delete data;
}

void Widget::plotDft(QVector<qreal>data)
{
    Plot *plotter = new Plot();
    plotter->plotData(data);
}

void Widget::on_quitButton_clicked()
{
    QApplication::quit();
}
