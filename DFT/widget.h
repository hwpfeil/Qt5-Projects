#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QGraphicsScene>
#include <QRect>
#include <QLine>
#include <QPoint>
#include "dft.h"
#include "plot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QVector<complex<qreal>> signal;
    void test();
    void plotDft(QVector<qreal> data);
    qreal findMax(QVector<qreal> data);
    qreal findMin(QVector<qreal> data);

public slots:
    void on_quitButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
