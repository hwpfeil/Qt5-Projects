#ifndef PLOT_H
#define PLOT_H

#include "widget.h"
#include <QWidget>
#include <QtDataVisualization>
#include <Q3DBars>
#include <QScreen>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBar3DSeries>
#include <QBarDataRow>
#include <QBarDataProxy>
using namespace QtDataVisualization;


class Plot : public Q3DBars
{
    Q_OBJECT

public:
    Plot();
    ~Plot();
    void plotData(QVector<qreal> data);
    qreal getMax(QVector<qreal> data);
    qreal getMin(QVector<qreal> data);
};

#endif // PLOT_H
