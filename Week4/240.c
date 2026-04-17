//240. Search a 2D Matrix II
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int m = matrixSize;
    int n = matrixColSize[0];

    int row = 0;
    int col = n - 1;   // 從右上角開始

    while (row < m && col >= 0) {
        if (matrix[row][col] == target) {
            return true;
        } 
        else if (matrix[row][col] > target) {
            col--;      // 太大，往左走
        } 
        else {
            row++;      // 太小，往下走
        }
    }

    return false;
}
