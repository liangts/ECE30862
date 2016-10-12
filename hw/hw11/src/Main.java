import java.util.Random;

public class Main {
    public static int[] _get_matrix_size(int[][] arr_2d){
        int[] return_array_size = new int[2];
        return_array_size[0] = arr_2d.length;
        return_array_size[1] = arr_2d[0].length;

        return return_array_size;
    }


    public static void fill(int N){
        if (N % 2 != 0){
            throw new IllegalArgumentException("N % 2 should == 0!");
        }
        int[][] A = new int[N][N];
        int[][] B = new int[N][N];
        int[][] C = new int[N][N];


        Random random = new Random(100);
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                B[i][j] = random.nextInt()%10;
                C[i][j] = random.nextInt()%10;
            }
        }

        //System.out.println("Original matrix B:");
        //_print_matrix(B);
        //System.out.println("original matrix C:");
        //_print_matrix(C);

        // Call thread calculation
        A = _calc_array_A(B, C, 4);
        A = _calc_array_A(B, C, 2);
        A = _calc_array_A(B, C, 1);
        System.out.println("Size of matrix A is: "+_get_matrix_size(A)[0]);
        //System.out.println("original matrix A:");
        //_print_matrix(A);

    }

    public static void _print_matrix(int[][] matrix){
        int n = matrix.length;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                System.out.printf("%5d", matrix[i][j]);
            }
            System.out.println("");
        }

    }

    public static Thread _thread_calc(final int[][] A, final int[][] B, final int[][] C, final int x1, final int x2, final int y1,final int y2){
        class _thread implements Runnable{
            public void run(){
                for (int i = x1; i < x2; i++){
                    for (int j = y1; j < y2; j++){
                        A[i][j] = B[i][j] * C[i][j];
                    }
                }
            }
        }
        Thread t = new Thread((new _thread()));
        t.start();

        return t;
    }

    public static int[][] _calc_array_A(int[][] B, int[][] C, int thread_num){
        int N = B.length;
        int[][] A = new int[N][N];
        System.out.println("Thread Number: "+thread_num);

        Thread t1 = null;
        Thread t2 = null;
        Thread t3 = null;
        Thread t4 = null;
        long t_start = System.currentTimeMillis();


        if (thread_num == 1) {
            t1 = _thread_calc(A, B, C, 0, N, 0, N);
        }

        if (thread_num == 2) {
            t1 = _thread_calc(A, B, C, 0, N / 2, 0, N);
            t2 = _thread_calc(A, B, C, N / 2, N, 0, N);
        }


        if (thread_num == 4) {
            t1 = _thread_calc(A, B, C, 0, N / 2, 0, N / 2);
            t2 = _thread_calc(A, B, C, 0, N / 2, N / 2, N);
            t3 = _thread_calc(A, B, C, N / 2, N, 0, N / 2);
            t4 = _thread_calc(A, B, C, N / 2, N, N / 2, N);

        }
        try {
            t1.join();
            if (thread_num == 2) {
                t2.join();
            } else if (thread_num == 4) {
                t2.join();
                t3.join();
                t4.join();
            }
        }
        catch (InterruptedException ex) {
        }
        long t_end = System.currentTimeMillis();

        System.out.println("Time used:"+(t_end - t_start)+"ms");

        return A;
    }

    /**
     * Use the fill() function will automatically show the time used
     * in thread number of 4 , 2 , 1
     * @param args
     */
    public static void main(String args[]){
        System.out.println("My test time elapsed:");
        System.out.println("java Main");
        System.out.println("65, 71, 141ms for thread number 4, 2, 1");
        System.out.println("java -Djava.compiler=NONE Main");
        System.out.println("1324, 2534, 4856ms for thread number 4, 2, 1");
        System.out.println("======Now Begin this program================");

        fill(10000);

    }


}
