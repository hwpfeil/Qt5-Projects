
#include "sinebars.h"
#include "trianglebars.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    sineBars *m_sineBars = new sineBars;
    m_sineBars;

    triangleBars *m_triangleBars = new triangleBars;
    m_triangleBars;

    return a.exec();
}

