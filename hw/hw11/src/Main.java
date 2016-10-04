public class Main {
    public int[] _get_matrix_size(int[][] arr_2d){
        int[] return_array_size = new int[2];
        return_array_size[0] = arr_2d.length;
        return_array_size[1] = arr_2d[0].length;

        return return_array_size;
    }

    public void fill(int N){
        if (N % 2 != 0){
            throw new IllegalArgumentException("N % 2 should == 0!");
        //Need to fill
        }
    }

    public void _print_matrix(int[][] matrix){
        int n = matrix.length;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                System.out.print(matrix[i][j]);
            }
            System.out.println("");
        }

    }

    public void _thread_calc(int[][] A, int[][] B, int[][] C, int x1, int x2, int y1, int y2){
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
    }

    public int[][] _calc_array_A(int[][] B, int[][] C, int thread_num){
        int N = B.length;
        int[][] A = new int[N][N];

        if (thread_num == 1){
            _thread_calc(A, B, C, 0, N, 0, N);
        }

        if (thread_num == 2){
            _thread_calc(A, B, C, 0, N / 2, 0, N);
            _thread_calc(A, B, C, N / 2, N, 0, N);
        }

        if (thread_num == 4){
            _thread_calc(A, B, C, 0, N / 2, 0, N / 2);
            _thread_calc(A, B, C, 0, N / 2, N / 2, N);
            _thread_calc(A, B, C, N / 2, N, 0, N / 2);
            _thread_calc(A, B, C, N / 2, N, N / 2, N);

        }

        return A;
    }

    public static void main(String args[]){

    }


}
