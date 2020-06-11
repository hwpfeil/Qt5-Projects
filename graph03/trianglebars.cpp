#include "trianglebars.h"

triangleBars::triangleBars()
{
    Q3DBars *bars = new Q3DBars();
    bars->setBarThickness(0.5);
    bars->setFlags(bars->flags() ^ Qt::FramelessWindowHint);
    bars->rowAxis()->setRange(0, 4);
    int resolution = 1000;
    bars->columnAxis()->setRange(0, resolution);
    bars->setBarThickness(0.5);
    bars->valueAxis()->setRange(-1., 1.);
    QWidget *container = QWidget::createWindowContainer(bars);

    QSize screenSize = bars->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    QBar3DSeries *series = new QBar3DSeries;
    QBarDataRow *data = new QBarDataRow;

    QVector<qreal> barData;
    Data *myData = new Data;
    barData = myData->genTriangleWave(resolution);
    for (int i = 0; i < barData.size(); ++i) {
        *data << barData.at(i);
    }
    series->dataProxy()->addRow(data);
    bars->addSeries(series);

    widget->show();
}
