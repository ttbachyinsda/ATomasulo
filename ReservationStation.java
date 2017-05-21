import java.util.ArrayList;
import java.util.List;

/**
 * Created by zjkgf on 2017/5/22.
 */
public class ReservationStation {
    public List<Integer> Time;
    public List<String> Name;
    public List<Boolean> IsBusy;
    public List<String> op;
    public List<Integer> VJ;
    public List<Integer> VK;
    public List<String> QJ;
    public List<String> QK;
    public Integer length;
    public ReservationStation(int addlen, int multilen){
        length = addlen + multilen;
        Name = new ArrayList<>();
        IsBusy = new ArrayList<>();
        Time = new ArrayList<>();
        op = new ArrayList<>();
        VJ = new ArrayList<>();
        VK = new ArrayList<>();
        QJ = new ArrayList<>();
        QK = new ArrayList<>();
        for (int i=0;i<addlen+multilen;i++){
            if (i < addlen) {
                Name.add("Add" + (i + 1));
            } else{
                Name.add("Mult" + (i  - addlen + 1));
            }
            IsBusy.add(false);
            Time.add(0);
            op.add("");
            VJ.add(0);
            VK.add(0);
            QJ.add("");
            QK.add("");
        }
    }
}
