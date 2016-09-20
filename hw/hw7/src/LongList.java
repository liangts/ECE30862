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
}
