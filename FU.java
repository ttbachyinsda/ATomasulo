import java.util.ArrayList;
import java.util.List;

/**
 * Created by zjkgf on 2017/5/22.
 */
public class FU {
    public List<String> F;
    public Integer length;
    public FU(int len){
        F = new ArrayList<>();
        length = len;
        for (int i=0;i<len;i++){
            F.add("");
        }
    }
}
