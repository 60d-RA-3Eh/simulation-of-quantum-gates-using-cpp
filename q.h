    
#ifndef Q_H

#define Q_H

#define rt2 1.414213

struct complex
{
    float real;
    float img;
};

class qubit
{
    private:
    complex alpha;        //Probablity Amplitude of 0 i.e. |alpha|^2 = probablity of 0
    complex beta;         //Probablity Amplitude of 1 i.e. |beta|^2 = probablity of 1
    public:
    qubit()
    {
        alpha.real =1.0;
        alpha.img = 0.0;
        beta.real =0.0;
        beta.img =0.0;
    }
    qubit operator=(const qubit&);

    friend void H(qubit&);
    friend void X(qubit&);
    friend void sqrtNOT(qubit&);
    friend void Y(qubit&);
    friend void Z(qubit&);
    friend void S(qubit&);
    friend void T(qubit&);
    friend void SWAP(qubit&,qubit&);
    friend void CNOT(qubit&,qubit&);  
};

qubit qubit::operator=(const qubit& qbit)
{
    this->alpha.img = qbit.alpha.img;
    this->alpha.real = qbit.alpha.real;
    this->beta.img = qbit.beta.img;
    this->beta.real = qbit.beta.real;
    return (*this);
}



void H(qubit& qbit)
{
    float oldAlphaReal = qbit.alpha.real;
    float oldBetaReal = qbit.beta.real;
    float oldAlphaImg = qbit.alpha.img;
    float oldBetaImg = qbit.beta.img;

    qbit.alpha.real = (oldAlphaReal + oldBetaReal) / rt2;
    qbit.beta.real = (oldAlphaReal - oldBetaReal) / rt2;

    qbit.alpha.img = (oldAlphaImg + oldBetaImg) / rt2;
    qbit.beta.img = (oldAlphaImg - oldBetaImg) / rt2;
}

void X(qubit& qbit)
{
    qbit.alpha.real = qbit.alpha.real +  qbit.beta.real;
    qbit.beta.real = qbit.alpha.real - qbit.beta.real;
    qbit.alpha.real = qbit.alpha.real - qbit.beta.real;

    qbit.alpha.img = qbit.alpha.img +  qbit.beta.img;
    qbit.beta.img = qbit.alpha.img - qbit.beta.img;
    qbit.alpha.img = qbit.alpha.img - qbit.beta.img;
}

void sqrtNOT(qubit& qbit)
{
    float oldAlphaReal = qbit.alpha.real;
    float oldBetaReal = qbit.beta.real;
    float oldAlphaImg = qbit.alpha.img;
    float oldBetaImg = qbit.beta.img;

    qbit.alpha.real = (oldBetaImg + oldBetaReal - oldAlphaImg + oldAlphaReal)/2;
    qbit.alpha.img =  (oldBetaImg - oldBetaReal + oldAlphaImg + oldAlphaReal)/2;
    
    qbit.beta.real = (oldAlphaImg + oldAlphaReal + oldBetaReal - oldBetaImg)/2;
    qbit.beta.img = (oldAlphaImg - oldAlphaReal + oldBetaReal + oldBetaImg)/2;
}

void Y(qubit& qbit)
{
    float oldAlphaReal = qbit.alpha.real;
//    float oldBetaReal = qbit.beta.real;
    float oldAlphaImg = qbit.alpha.img;
 //   float oldBetaImg = qbit.beta.img;

    qbit.alpha.real = qbit.beta.img; // oldBetaImg
    qbit.alpha.img = -1*qbit.beta.real; // oldBetaReal
    qbit.beta.real = -1*oldAlphaImg;
    qbit.beta.img = oldAlphaReal;
    
}

void Z(qubit& qbit)
{
    qbit.beta.img *= -1;
}

void S(qubit& qbit)
{
    float oldBetaReal = qbit.beta.real;
    qbit.beta.real = -1*qbit.beta.img;
    qbit.beta.img = oldBetaReal;
}

void T(qubit& qbit)
{
    float oldBetaReal = qbit.beta.real;
    float oldBetaImg = qbit.beta.img;

    qbit.beta.real = (oldBetaReal - oldBetaImg)/rt2;
    qbit.beta.img = (oldBetaReal + oldBetaImg)/rt2;
}

void SWAP(qubit& qbit_first,qubit& qbit_second)
{
    qubit qbit_temp = qbit_first;
    qbit_first = qbit_second;
    qbit_second = qbit_temp;
}

void CNOT(qubit& qbit_first,qubit& qbit_second)
{
    if (fabs(qbit_first.beta.real) > 0.5 || fabs(qbit_first.beta.img) > 0.5)
    {
        X(qbit_second);
    }
}

#endif