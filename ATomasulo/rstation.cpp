#include "rstation.h"

RStation::RStation()
{
    Time = 0;
    Name = "";
    IsBusy = false;
    Op = "";
    VJ = 0.0;
    VK = 0.0;
    QJ = NULL;
    QK = NULL;
    A = 0;
}
