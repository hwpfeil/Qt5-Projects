#ifndef DATA_H
#define DATA_H

#include <QVector>
class Data : public QVector<qreal>
{
public:
    Data();
    QVector<qreal> genSineWave(int resolution);
    QVector<qreal> genTriangleWave(int resolution);
    enum {
        Sine,
        Triangle,
    };
};

#endif // DATA_H
