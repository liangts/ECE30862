/**
 * Created by liang on 2016/9/25.
 */
public class IntegerArithmetic {

    private static long getObject(Object obj){
        if (obj instanceof Integer){
            return ((Integer) obj).longValue();
        }
        else if (obj instanceof Long){
            return ((Long) obj).longValue();
        }
        else{
            throw new IllegalArgumentException("op1/op2 can only be type Long or Integer");
        }
    }


    public static long add(Object op1, Object op2){
        long l1 = getObject(op1);
        long l2 = getObject(op2);

        return l1 + l2;
    }

    public static long substract(Object op1, Object op2){
        long l1 = getObject(op1);
        long l2 = getObject(op2);

        return l1 - l2;
    }

    public static long multiply(Object op1, Object op2){
        long l1 = getObject(op1);
        long l2 = getObject(op2);

        return l1 * l2;
    }

    public static long divide(Object op1, Object op2){
        long l1 = getObject(op1);
        long l2 = getObject(op2);
        if (l2 == 0) throw new ArithmeticException("op2 cannot be 0");
        return l1 / l2;
    }




}

