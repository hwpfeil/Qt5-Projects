#include "plot.h"

Plot::Plot()
{
}

Plot::~Plot()
{
}

void Plot::plotData(QVector<qreal> data)
{
    qreal dataMin, dataMax;
    dataMin = floor(getMin(data));
    dataMax = ceil(getMax(data));

    Q3DBars *bars = new Q3DBars();
    bars->setBarThickness(0.5);
    bars->setFlags(bars->flags() ^ Qt::FramelessWindowHint);
    bars->rowAxis()->setRange(dataMin, dataMax);
    bars->columnAxis()->setRange(dataMin, dataMax);
    bars->setBarThickness(0.5);
    bars->valueAxis()->setRange(dataMin, dataMax);

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
    QBarDataRow *dataRow = new QBarDataRow;  // typedef vector of QBarDataItem objects

    for (int i = 0; i < data.size(); ++i ) {
        *dataRow << data.at(i);
    }

    series->dataProxy()->addRow(dataRow);
    bars->addSeries(series);

    widget->show();
}

qreal Plot::getMax(QVector<qreal> data)
{
    qreal max(0);
    for (int i = 0; i < data.size(); ++i) {
        if (data.at(i) > max) max = data.at(i);
    }
    return max;
}

qreal Plot::getMin(QVector<qreal> data)
{
    qreal min(0);
    for (int i = 0; i < data.size(); ++i) {
        if (data.at(i) < min) min = data.at(i);
    }
    return min;
}
