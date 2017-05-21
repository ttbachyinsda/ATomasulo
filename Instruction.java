import java.util.List;

/**
 * Created by zjkgf on 2017/5/22.
 */
public class Instruction {
    public String op;
    public String F1;
    public String F2;
    public String F3;
    public RStation pointer;
    public Instruction(){
        op = "";
        F1 = "";
        F2 = "";
        F3 = "";
        pointer = null;
    }
    public boolean validate(){
        return true;
    }
}
