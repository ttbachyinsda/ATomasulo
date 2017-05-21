import java.util.ArrayList;
import java.util.List;

/**
 * Created by zjkgf on 2017/5/22.
 */
public class LoadQueue {
    public List<String> Header;
    public List<Boolean> IsBusy;
    public List<Integer> Address;
    public Integer length;
    public LoadQueue(int len){
        length = len;
        Header = new ArrayList<>();
        IsBusy = new ArrayList<>();
        Address = new ArrayList<>();
        for (int i=0;i<len;i++){
            Header.add("Load"+(i+1));
            IsBusy.add(false);
            Address.add(-1);
        }
    }
}
