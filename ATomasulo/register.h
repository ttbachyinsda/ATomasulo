#ifndef REGISTER_H
#define REGISTER_H
#include <QString>
#include "rstation.h"
class Register
{
public:
    Register();
    QString Name;
    RStation* Q;
    int V;
};

#endif // REGISTER_H
