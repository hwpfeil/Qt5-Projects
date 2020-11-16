#include "dft.h"

DFT::DFT()
{
}

DFT::~DFT()
{
}

// Direct computation using discrete fourier transform formula
//  Xk == k-th frequency
//  Sum evaluated at n of N samples
//  x-sub-n == n-th data sample
//  exponent of e == -j * 2pi * k/N * n
//  Xk = Sum from n=0 to N[ x-sub-n * exp(-j2pikn/N) ]

QVector< complex<qreal> > DFT::dft(QVector< complex<qreal> > &data)
{
    const quint32 size = data.size();
    const complex<qreal> inverseSize(1.0 / static_cast<qreal>(size), 0.); // 1/N
    QVector<complex<qreal>> frequency(size, 0.);
    complex<qreal> exponent, temp;
    for(quint32 k = 0; k < size; ++k) {
        for(quint32 n = 0; n < size; ++n) {
            temp = pi2 * static_cast<qreal>(k);
            temp *= static_cast<qreal>(n);
            temp *= inverseSize;
            exponent = static_cast<complex<qreal>>(-1.i) * temp;
            frequency[k] += data[n] * exp(exponent);
        }
    }
    return frequency;
}
