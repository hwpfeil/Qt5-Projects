#ifndef DFT_H
#define DFT_H

#include <QtGlobal>
#include <QVector>
#include <QtMath>  // M_PI
#include <complex>
using std::complex;

// Input: QVector containing qreal data samples
// Output: Discrete Fourier Transform of the data

class DFT
{
public:
    DFT();
    ~DFT();
    const complex<qreal> pi2 = (M_PI * 2.);
    QVector<complex<qreal>> dft(QVector<complex<qreal>> &data);
};

#endif // DFT_H
