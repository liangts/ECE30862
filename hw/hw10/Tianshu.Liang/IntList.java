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
        next = null;
    }

    public int getData(){
        return data;
    }

    public IntList next(){
        return  next;
    }

    public void printNode(){
        System.out.print("IntList Node, data is: " + data);
    }

    public Object clone() throws CloneNotSupportedException{
        IntList clone_list = null;
        clone_list = (IntList)super.clone();
        if (clone_list.next != null) {
            clone_list.next = (IntList) this.next.clone();
        }
        return clone_list;
    }
}
