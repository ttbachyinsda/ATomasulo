#ifndef FREGISTER_H
#define FREGISTER_H
#include <QString>
#include "rstation.h"

class FRegister
{
public:
    FRegister();
    QString Name;
    RStation* Q;
    float V;
};

#endif // FREGISTER_H
