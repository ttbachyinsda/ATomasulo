#ifndef STATUS_H
#define STATUS_H
#include "rstation.h"
#include "fregister.h"
#include "register.h"
#include "instruction.h"
#include <QVector>
#define loadbufferlen 3
#define storebufferlen 3
#define addreservation 3
#define multireservation 2
#define memorylen 4096
#define registerlen 11
#define ILLEGALINSTRUCT 101
#define DIVZERO 102
#define RIGHT 0
class Status
{
public:
    Status();
    QVector<RStation> LoadBuffer, StoreBuffer, AddReservation, MultiplyReservation;
    QVector<Instruction> InstructList;
    RStation* LoadBufferPointer, *StoreBufferPointer, *AddReservationPointer, *MultiplyReservationPointer;
    QVector<Register> IntRegister;
    QVector<FRegister> FloatRegister;
    QVector<float> Memory;
    int CurrentInstruction, NowCycle;
    bool Isdone, Lock;
    int updateinstruct(QString instruction);
    int nextstep();
    void LOCKER(bool lockstatus);
};

#endif // STATUS_H
