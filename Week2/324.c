//324. Wiggle Sort II
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void wiggleSort(int* nums, int numsSize) {
    // 1. Create a copy and sort it
    int* temp = (int*)malloc(sizeof(int) * numsSize);
    memcpy(temp, nums, sizeof(int) * numsSize);
    qsort(temp, numsSize, sizeof(int), compare);

    // 2. Point to the end of the "Small" half and "Large" half
    // This handles the duplicate median issue.
    int left = (numsSize - 1) / 2; // End of smaller half
    int right = numsSize - 1;      // End of larger half

    // 3. Interleave back into the original array
    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0) {
            nums[i] = temp[left--];
        } else {
            nums[i] = temp[right--];
        }
    }

    free(temp);
}
