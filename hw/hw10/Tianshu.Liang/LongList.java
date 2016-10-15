/**
 * Created by liang on 2016/9/19.
 */
public class LongList implements MyList {
    private LongList next;
    private long data;

    public LongList(LongList n, long data){
        this.data = data;
        next = n;
    }

    public LongList(long data){
        this.data = data;
        next = null;
    }

    public long getData(){
        return data;
    }

    public LongList next(){
        return next;
    }

    public void printNode(){
        System.out.print("IntList Node, data is: " + data);
    }

    public Object clone() throws CloneNotSupportedException{
        LongList clone_list = null;
        clone_list = (LongList) super.clone();
        if (clone_list.next != null) {
            clone_list.next = (LongList) this.next.clone();
        }
        return clone_list;
    }
}
