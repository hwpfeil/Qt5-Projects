#ifndef SINEBARS_H
#define SINEBARS_H

#include "data.h"
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

// using namespace Qt3DCore;

class sineBars : public Q3DBars
{
public:
    sineBars();
};

#endif // SINEBARS_H
