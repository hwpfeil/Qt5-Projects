#include "surfacegraph.h"

#include <QValue3DAxis>
#include <Q3DTheme>
#include <QImage>
#include <QtMath>

using namespace QtDataVisualization;

SurfaceGraph::SurfaceGraph(Q3DSurface *surface)
    : m_graph(surface)
{

}

SurfaceGraph::~SurfaceGraph()
{

}
