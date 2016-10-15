/**
 * Created by liang on 2016/9/19.
 */

public interface MyList extends Cloneable{
    MyList next();
    void printNode();
    public Object clone() throws CloneNotSupportedException;
}
