#include "status.h"

Status::Status()
{
    for (int i=0;i<loadbufferlen;i++){
        RStation load;
        load.Name="Load"+QString::number(i+1);
        LoadBuffer.append(load);
    }
    for (int i=0;i<storebufferlen;i++){
        RStation store;
        store.Name="Store"+QString::number(i+1);
        StoreBuffer.append(store);
    }
    for (int i=0;i<registerlen;i++){
        Register reg;
        reg.Name="R"+QString::number(i);
        IntRegister.append(reg);
    }
    for (int i=0;i<registerlen;i++){
        FRegister reg;
        reg.Name="F"+QString::number(i);
        FloatRegister.append(reg);
    }
    for (int i=0;i<addreservation;i++){
        RStation res;
        res.Name = "ADD"+QString::number(i+1);
        AddReservation.append(res);
    }
    for (int i=0;i<multireservation;i++){
        RStation res;
        res.Name = "MULT"+QString::number(i+1);
        MultiplyReservation.append(res);
    }
    for (int i=0;i<memorylen;i++){
        Memory.append(0);
    }
    LoadBufferPointer = NULL;
    StoreBufferPointer = NULL;
    AddReservationPointer = NULL;
    MultiplyReservationPointer = NULL;
    CurrentInstruction = 0;
    Isdone = false;
    NowCycle = 0;
}
int Status::updateinstruct(QString instruction)
{
    if (Lock){}
    int errorcode = RIGHT;
    return errorcode;
}
int Status::nextstep()
{
    int errorcode = RIGHT;
    return errorcode;
}
void Status::LOCKER(bool lockstatus)
{
    Lock = lockstatus;
}
