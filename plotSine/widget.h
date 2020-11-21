#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QRect>
#include <QRectF>
#include <QSize>
#include <QLine>
#include <QPoint>
#include <QPointF>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QGraphicsScene *myScene;
    QRect View;
    QRectF World;

    QLine xAxis, yAxis;
    QVector<QPointF> mySignal;
    int resolution;

    void setCoordinates();
    void drawAxes();
    void genSineWave();
    void plotSignal();
    QPoint World2View(QPointF Pworld);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
