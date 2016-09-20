/**
 * Created by liang on 2016/9/19.
 */
public class IntList implements MyList {
    private IntList next;
    private int data;

    public IntList(IntList n, int data){
        this.data = data;
        next = n;
    }

    public IntList(int data){
        this.data = data;
    }

    public int getData(){
        return data;
    }

    public IntList next(){
        return  next;
    }

    public  void printNode(){
        System.out.print("IntList Node, data is: " + data);
    }
}
