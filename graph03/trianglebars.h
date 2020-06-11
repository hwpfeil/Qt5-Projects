#ifndef TRIANGLEBARS_H
#define TRIANGLEBARS_H

#include "data.h"
#include <QtDataVisualization>
#include <QtDataVisualization>
#include <QApplication>
#include <Q3DBars>
#include <QWidget>
#include <QScreen>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include <QBar3DSeries>
#include <QBarDataRow>
#include <QBarDataProxy>

using namespace QtDataVisualization;

class triangleBars : public Q3DBars
{
public:
    triangleBars();
};

#endif // TRIANGLEBARS_H
