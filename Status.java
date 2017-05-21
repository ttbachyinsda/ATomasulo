import com.sun.org.apache.xpath.internal.operations.Mult;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by zjkgf on 2017/5/22.
 */
public class Status {
    public List<RStation> LoadBuffer;
    public List<RStation> StoreBuffer;
    public List<RStation> AddReservation;
    public List<RStation> MultiplyReservation;
    public List<Instruction> InstructList;
    public RStation LoadBufferPointer;
    public RStation StoreBufferPointer;
    public RStation AddReservationPointer;
    public RStation MultiplyReservationPointer;
    public List<Register> IntRegister;
    public List<FRegister> FloatRegister;
    public List<Double> Memory;
    public int CurrentInstruction;
    public int NowCycle;
    public boolean Isdone;
    public boolean Lock;
    static final int loadbufferlen = 3;
    static final int storebufferlen = 3;
    static final int addreservation = 3;
    static final int multireservation = 2;
    static final int memorylen = 4096;
    static final int registerlen = 11;

    static final int ILLEGALINSTRUCT = 101;
    static final int DIVZERO = 102;
    static final int RIGHT = 0;

    public Status(){
        LoadBuffer = new ArrayList<>(loadbufferlen);
        StoreBuffer = new ArrayList<>(storebufferlen);
        AddReservation = new ArrayList<>(addreservation);
        MultiplyReservation = new ArrayList<>(multireservation);
        InstructList = new ArrayList<>();
        LoadBufferPointer = null;
        StoreBufferPointer = null;
        AddReservationPointer = null;
        MultiplyReservationPointer = null;
        IntRegister = new ArrayList<>(registerlen);
        FloatRegister = new ArrayList<>(registerlen);
        Memory = new ArrayList<>(memorylen);
        for (int i=0;i<addreservation;i++){
            AddReservation.get(i).Name = "ADD"+(i+1);
        }
        for (int i=0;i<multireservation;i++){
            MultiplyReservation.get(i).Name = "MULT"+(i+1);
        }
        for (int i=0;i<loadbufferlen;i++){
            LoadBuffer.get(i).Name = "LOAD" + (i+1);
        }
        for (int i=0;i<storebufferlen;i++){
            StoreBuffer.get(i).Name = "STORE" + (i+1);
        }
        for (int i=0;i<registerlen;i++){
            IntRegister.get(i).Name = "R" + i;
        }
        for (int i=0;i<registerlen;i++){
            FloatRegister.get(i).Name = "F" + i;
        }
        CurrentInstruction = 0;
        Isdone = false;
        NowCycle = 0;
        Lock = false;
    }
    public int updateinstruct(String instruction){
//        LD R1 3
//        ADDD R1 R2 R3
//        MULTD R3 R4 R5
        if (Lock){}
        int errorcode = RIGHT;
        return errorcode;
    }
    public int nextstep(){
        int errorcode = RIGHT;
        for (int i=0;i<InstructList.size();i++){
            if (!InstructList.get(i).validate()){
                errorcode = ILLEGALINSTRUCT;
                return errorcode;
            }
        }

        return errorcode;
    }

    public void LOCKER(boolean lockstatus){
        Lock = lockstatus;
    }
}
