#include "data.h"
#include <QtMath>

Data::Data()
{

}

QVector<qreal> Data::genSineWave(int resolution)
{
    QVector<qreal> data;
    qreal dataPoint, theta;
    qreal dx = (2. * M_PI) / resolution;
    for (int i = 0; i < resolution; ++i) {
        theta = i * dx;
        dataPoint = qSin(theta);
        data.append(dataPoint);
    }
    return data;
}

QVector<qreal> Data::genTriangleWave(int resolution)
{
    //trigonometric fourier series
    //a0 + a1sin(x) + b1cos(x) + a2sin(2x) + b2cos(2x) + a3sin(3x) + b3cos(3x) + ...
    //sin(x) - 1⁄2sin(2x) + 1⁄3sin(3x) - 1⁄4sin(4x) + 1⁄5sin(5x) - 1⁄6sin(6x) + ...
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

    QVector<qreal> data;
    qreal dataPoint, theta;

    for (int i = 0; i < resolution; ++i) {
        theta = m2PIdx * static_cast<qreal>(i);
        dataPoint = qSin(theta) -
                half * qSin(2. * theta) +
                third * qSin(3. * theta) -
                fourth * qSin(4. * theta) +
                fifth * qSin(5. * theta) -
                sixth * qSin(6. * theta) +
                seventh * qSin(7. * theta) -
                eighth * qSin(8. * theta) +
                ninth * qSin(9. * theta) -
                tenth * qSin(10. * theta);
        data.append(dataPoint);
    }
    return data;
}
