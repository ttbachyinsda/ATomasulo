/**
 * Created by zjkgf on 2017/5/22.
 */
public class Printer {
    public static void printer(FU fu, LoadQueue loadQueue, ReservationStation reservationStation, StoreQueue storeQueue){
        System.out.println("Load Queue = ");
        System.out.println("Header\tIsBusy\tAddress");
        for (int i=0;i<loadQueue.length;i++){
            System.out.println(loadQueue.Header.get(i)+"\t"+loadQueue.IsBusy.get(i)+"\t"+loadQueue.Address.get(i));
        }
        System.out.println("Store Queue = ");
        System.out.println("Header\tIsBusy\tAddress");
        for (int i=0;i<storeQueue.length;i++){
            System.out.println(storeQueue.Header.get(i)+"\t"+storeQueue.IsBusy.get(i)+"\t"+storeQueue.Address.get(i));
        }
        System.out.println("ReservationStation = ");
        System.out.println("Time\tName\tIsBusy\tOp\tVJ\tVK\tQJ\tQK\t");
        for (int i=0;i<reservationStation.length;i++){
            System.out.println(reservationStation.Time.get(i)+"\t"+reservationStation.Name.get(i)
            +"\t"+reservationStation.IsBusy.get(i)+"\t"+reservationStation.op.get(i)+"\t"+
            reservationStation.VJ.get(i)+"\t"+reservationStation.VK.get(i)+"\t"+reservationStation.QJ.get(i)+"\t"
            +reservationStation.QK.get(i));
        }
        System.out.println("FU = ");
        for (int i=0;i<fu.length;i++){
            System.out.println(i+"\t"+fu.F.get(i));
        }
    }
    public static void main(String args[]){
        FU fu = new FU(10);
        LoadQueue loadQueue = new LoadQueue(3);
        ReservationStation reservationStation = new ReservationStation(3,2);
        StoreQueue storeQueue = new StoreQueue(3);
        printer(fu,loadQueue,reservationStation,storeQueue);
    }
}
