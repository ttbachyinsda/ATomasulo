/**
 * Created by zjkgf on 2017/5/22.
 */
public class RStation {
    public Integer Time;
    public String  Name;
    public Boolean IsBusy;
    public String Op;
    public Double VJ;
    public Double VK;
    public RStation QJ;
    public RStation QK;
    public Integer A;
    public RStation(){
        Time = 0;
        Name = "";
        IsBusy = false;
        Op = "";
        VJ = 0.0;
        VK = 0.0;
        QJ = null;
        QK = null;
        A = 0;
    }
}
