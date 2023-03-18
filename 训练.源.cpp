#include<stdio.h>
#include<stdlib.h>
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int i, j;
    for (i = 0; i < numsSize; i++)
    {
        for (j = i + 1; j < numsSize; j++)
        {
            if (*(nums + i) + *(nums + j) == target)
            {
                int* rear = malloc(sizeof(int) * 2);
                rear[0] = i; rear[1] = j;
                *returnSize = 2;
                return rear;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}
---------------------
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    double returndata = 0;
    int* rear = (int *)malloc(sizeof(int) * (nums1Size + nums2Size));
    for (int i = 0; i < nums1Size; i++)
    {
        *(rear + i) = *(nums1 + i);
    }
    for (int j = 0; j < nums2Size; j++)
    {
        *(rear + nums1Size + j) = *(nums2 + j);
    }
    for (int i = 1; i < (nums1Size + nums2Size); i++)
    {
        for (int j = 0; j < (nums1Size + nums2Size - i); j++)
        {
            if (*(rear + j) > *(rear + j + 1))
            {
                int temp = *(rear + j);
                *(rear + j) = *(rear + j + 1);
                *(rear + j + 1) = temp;
            }
        }
    }
    if ((nums1Size + nums2Size) % 2 == 0)
    {
        returndata = (*(rear + (nums1Size + nums2Size) / 2) + *(rear + ((nums1Size + nums2Size) / 2 )- 1)) / 2;//这一句代码执行后得不出想要的结果，为什么？
    }
    else
    {
        returndata = *(rear + (nums1Size + nums2Size - 1) / 2);
    }
    free(rear);
    return returndata;
}
