//3537. Fill a Special Grid

#include <stdlib.h>


int** specialGrid(int n, int* returnSize, int** returnColumnSizes) {
    int side = 1 << n; // 2^n
    *returnSize = side;
    
    // Allocate memory for the row pointers and column sizes
    int** grid = (int**)malloc(side * sizeof(int*));
    *returnColumnSizes = (int*)malloc(side * sizeof(int));
    
    for (int i = 0; i < side; i++) {
        (*returnColumnSizes)[i] = side;
        grid[i] = (int*)malloc(side * sizeof(int));
    }

    // Fill the grid cell by cell
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            int val = 0;
            // Traverse from the largest quadrant scale down to 1x1
            for (int k = 0; k < n; k++) {
                int row_bit = (i >> k) & 1;
                int col_bit = (j >> k) & 1;
                int quad;

                // Problem constraints: TR < BR < BL < TL
                if (row_bit == 0 && col_bit == 1)      quad = 0; // TR
                else if (row_bit == 1 && col_bit == 1) quad = 1; // BR
                else if (row_bit == 1 && col_bit == 0) quad = 2; // BL
                else                                   quad = 3; // TL (0,0)

                // Each level k contributes 2 bits to the final number
                val |= (quad << (2 * k));
            }
            grid[i][j] = val;
        }
    }

    return grid;
}