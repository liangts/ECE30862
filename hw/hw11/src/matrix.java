public class matrix {
    public int[][] matrix(int a){
        int[][] array = new int[a][a];

        return array;
    }

    public int[] _get_matrix_size(int[][] arr_2d){
        int[] return_array_size = new int[2];
        return_array_size[0] = arr_2d.length;
        return_array_size[1] = arr_2d[0].length;

        return return_array_size;
    }
}
