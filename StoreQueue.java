import java.util.ArrayList;
import java.util.List;

/**
 * Created by zjkgf on 2017/5/22.
 */
public class StoreQueue {
    public List<String> Header;
    public List<Boolean> IsBusy;
    public List<Integer> Address;
    public Integer length;
    public StoreQueue(int len){
        length = len;
        Header = new ArrayList<>();
        IsBusy = new ArrayList<>();
        Address = new ArrayList<>();
        for (int i=0;i<len;i++){
            Header.add("Store"+(i+1));
            IsBusy.add(false);
            Address.add(-1);
        }
    }
}
