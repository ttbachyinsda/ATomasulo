#ifndef RSTATION_H
#define RSTATION_H
#include <QString>

class RStation
{
public:
    RStation();
    int Time;
    QString Name;
    bool IsBusy;
    QString Op;
    float VJ;
    float VK;
    RStation* QJ;
    RStation* QK;
    int A;
};

#endif // RSTATION_H
