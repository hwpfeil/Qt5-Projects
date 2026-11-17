#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setCoordinates();
    myScene = new QGraphicsScene(View);
    ui->graphicsView->setScene(myScene);

    drawAxes();
    genSineWave();
    plotSignal();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setCoordinates()
{
    //screen coordinates of ui->graphicsView to avoid referring to ui
    int XviewTopLeft = ui->graphicsView->geometry().topLeft().x();
    int YviewTopLeft = ui->graphicsView->geometry().topLeft().y();
    int XviewWidth = ui->graphicsView->geometry().width();
    int YviewHeight = ui->graphicsView->geometry().height();
    View.setCoords(XviewTopLeft, YviewTopLeft, XviewWidth, YviewHeight);
    // x = zero to 2pi, y = -1 to +1
    World.setCoords(0., 1., (2. * M_PI), -1.);
}

QPoint Widget::World2View(QPointF Pworld)
{
    /* View - ViewMin           World - WorldMin
 * -----------------  =     -------------------
 * ViewMax - ViewMin        WorldMax - WorldMin
 *
 *      Vmax - Vmin
 * V =  -----------  (W - Wmin) + Vmin
 *      Wmax - Wmin
 */
    QPoint Pview;
    QPointF PviewF;
    QPoint Vmax, Vmin;
    QPointF Wmax, Wmin;
    Vmax.setX(xAxis.p2().x());
    Vmax.setY(yAxis.p2().y());
    Vmin.setX(xAxis.p1().x());
    Vmin.setY(yAxis.p1().y());
    Wmax.setX(World.left() + World.width());
    Wmax.setY(World.top());
    Wmin.setX(World.left());
    Wmin.setY(World.top() + World.height());

    const qreal Sx = ( Vmax.x() - Vmin.x() ) / ( Wmax.x() - Wmin.x() );
    const qreal Sy = ( Vmax.y() - Vmin.y() ) / ( Wmax.y() - Wmin.y() );
    PviewF.setX(Sx * (Pworld.x() - Wmin.x()) + Vmin.x());
    PviewF.setY(Sy * (Pworld.y() - Wmin.y()) + Vmin.y());
    Pview = PviewF.toPoint();
    return Pview;
}

void Widget::drawAxes()
{
    //    QLine xAxis, yAxis
    // leave 10 pixel border around axes
    QPoint xleft, xright, ytop, ybottom;
    xleft.setX(View.left() + 10);
    xleft.setY(((View.top() + View.height()) - View.top()) / 2 + 10);
    xright.setX(View.left() + View.width() - 10);
    xright.setY(((View.top() + View.height()) - View.top()) / 2 + 10);
    ytop.setX(xleft.x());
    ytop.setY(View.top() + 10);
    ybottom.setX(xleft.x());
    ybottom.setY((View.top() + View.height()) - 10);

    xAxis.setP1(xleft);
    xAxis.setP2(xright);
    yAxis.setP1(ybottom);
    yAxis.setP2(ytop);
    resolution = xAxis.p2().x() - xAxis.p1().x();
    myScene->addLine(xAxis);
    myScene->addLine(yAxis);
    // add tick marks
    QPoint O = World2View(QPointF(0., 0.));
    myScene->addLine(O.x()+1, O.y()+5, O.x()+1, O.y()-5, QPen(Qt::red)); // tick at (0,0)
    QPoint halfPI = World2View(QPointF(M_PI/2, 0.));
    myScene->addLine(QLine(halfPI.x(), halfPI.y()+5, halfPI.x(), halfPI.y()-5),QPen(Qt::red));
    QPoint PI = World2View(QPointF(M_PI, 0.));
    myScene->addLine(QLine(PI.x(), PI.y()+5,PI.x(), PI.y()-5),QPen(Qt::red));
    QPoint threeHalfPI = World2View(QPointF(3*M_PI/2, 0.));
    myScene->addLine(QLine(threeHalfPI.x(), threeHalfPI.y()+5,
                           threeHalfPI.x(), threeHalfPI.y()-5),QPen(Qt::red));
    QPoint twoPI = World2View(QPointF(M_PI*2, 0.));
    myScene->addLine(QLine(twoPI.x(), twoPI.y()+5, twoPI.x(), twoPI.y()-5),QPen(Qt::red));
}

void Widget::plotSignal()
{
    QPoint Pview;

    for (int i = 0; i < resolution; ++i) {
        Pview = World2View(mySignal.at(i));
        myScene->addEllipse(Pview.x(), Pview.y(), 1, 1, QPen(Qt::blue), QBrush(Qt::SolidPattern));
    }
}

void Widget::genSineWave()
{
    qreal dataPoint, theta;
    QPointF p;
    qreal dx = (2. * M_PI) / resolution;
    for (int i = 0; i < resolution; ++i) {
        theta = i * dx;
        dataPoint = qSin(theta);
        p.setX(theta); p.setY(dataPoint);
        mySignal.append(p);
    }
}

void Widget::on_cosineButton_clicked()
{
    ui->graphicsView->setScene(nullptr);
    delete myScene;
    mySignal.clear();
    cosinePlot();
}

void Widget::genCosineWave()
{
    qreal dataPoint, theta;
    QPointF p;
    qreal dx = (2. * M_PI) / resolution;
    for (int i = 0; i < resolution; ++i) {
        theta = i * dx;
        dataPoint = qCos(theta);
        p.setX(theta); p.setY(dataPoint);
        mySignal.append(p);
    }
}

void Widget::cosinePlot()
{
    myScene = new QGraphicsScene(View);
    ui->graphicsView->setScene(myScene);

    setCoordinates();
    drawAxes();
    genCosineWave();
    plotSignal();
}

void Widget::on_sawtoothButton_clicked()
{
    ui->graphicsView->setScene(nullptr);
    delete myScene;
    mySignal.clear();
    sawtoothPlot();
}

void Widget::genSawtoothWave()
{
    //trigonometric fourier series
    // sawtooth(x) = 2/pi*[sin(x) - 1⁄2sin(2x) + 1⁄3sin(3x) - 1⁄4sin(4x) + 1⁄5sin(5x) - 1⁄6sin(6x) + ...]

    qreal half = 1./2.;
    qreal third = 1./3.;
    qreal fourth = 1./4.;
    qreal fifth = 1./5.;
    qreal sixth = 1./6.;
    qreal seventh = 1./7.;
    qreal eighth = 1./8.;
    qreal ninth = 1./9.;
    qreal tenth = 1./10.;
    qreal my2PI = 2. * M_PI;
    qreal m2PIdx = my2PI / static_cast<qreal>(resolution);

    qreal dataPoint, theta;
    QPointF p;
    qreal dx = (2. * M_PI) / resolution;
    for (int i = 0; i < resolution; ++i) {
        theta = m2PIdx * static_cast<qreal>(i);
        dataPoint = 2. / M_PI * (
                        qSin(theta) -
                        half * qSin(2. * theta) +
                        third * qSin(3. * theta) -
                        fourth * qSin(4. * theta) +
                        fifth * qSin(5. * theta) -
                        sixth * qSin(6. * theta) +
                        seventh * qSin(7. * theta) -
                        eighth * qSin(8. * theta) +
                        ninth * qSin(9. * theta) -
                        tenth * qSin(10. * theta) +
                        qSin(11. * theta)/11.
                        );
        p.setX(theta);
        p.setY(dataPoint*0.9); //kludge prevent clipping
        mySignal.append(p);      // need verticle scrollbar
    }                            // or adjust viewport
}

void Widget::sawtoothPlot()
{
    myScene = new QGraphicsScene(View);
    ui->graphicsView->setScene(myScene);

    setCoordinates();
    drawAxes();
    genSawtoothWave();
    plotSignal();
}

void Widget::on_squareButton_clicked()
{
    ui->graphicsView->setScene(nullptr);
    delete myScene;
    mySignal.clear();
    squarePlot();
}

void Widget::genSquareWave()
{
    // square(t) = 4⁄π [sin(t) + 1⁄3 sin(3t) + 1⁄5 sin(5t) + 1⁄7 sin(7t) + …]

    qreal third = 1./3.;
    qreal fifth = 1./5.;
    qreal seventh = 1./7.;
    qreal ninth = 1./9.;
    qreal my2PI = 2. * M_PI;
    qreal m2PIdx = my2PI / static_cast<qreal>(resolution);

    qreal dataPoint, theta;
    QPointF p;
    qreal dx = (2. * M_PI) / resolution;
    for (int i = 0; i < resolution; ++i) {
        theta = i * dx;
        dataPoint = 4./ M_PI * (
                        qSin(theta) +
                        third * qSin(3. * theta) +
                        fifth * qSin(5. * theta) +
                        seventh * qSin(7. * theta) +
                        ninth * qSin(9. * theta) +
                        qSin(11. * theta)/11.
                        );
        p.setX(theta); p.setY(dataPoint*0.8);
        mySignal.append(p);
    }
}

void Widget::squarePlot()
{
    myScene = new QGraphicsScene(View);
    ui->graphicsView->setScene(myScene);

    setCoordinates();
    drawAxes();
    genSquareWave();
    plotSignal();
}
