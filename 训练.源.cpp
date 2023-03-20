#include<stdio.h>
#include<stdlib.h>
-----找出数组里两元素和为目标值得两个数字-----
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
-----合并两个数组，使其成为正序表（从小到大），求出该数组中位数-----
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
}只能通过部分测试
样例：[1,2],[3,4]
     会得出得结果是2.00000.
    这是错误的。
找到错误了，第48行，虽然我定义了returndata为双精度类型数据，但是在计算的时候，等号右边的数据为整型导致数据部分丢失，得出的结果也以整型的数据变为双精度。
---
revamp.48：returndata=(*(rear + (nums1Size + nums2Size) / 2) + *(rear + ((nums1Size + nums2Size) / 2 )- 1)) / 2.0;
---
-----盛水容器-----
int maxArea(int* height, int heightSize) {
	int returndata = 0, m = heightSize;
	int temp = 0;//作为辅助
	int* rear = height;
	int i = 0, j = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 1; j < m; j++)
		{
			int length = j - i;
			if (*(rear + i) < *(rear + j))
			{
				returndata = *(rear + i) * length;
			}
			else
			{
				returndata = *(rear + j) * length;
			}
			if (returndata < temp)
			{
				int num = temp;
				temp = returndata;
				returndata = num;
			}
			temp = returndata;
		}
	}
	return returndata;
}
---
如果是个填空题就随随便便写完了，可惜是编程题，要看时间复杂度，我写的这串太粗暴了，数据一多就直接崩了。
---
int maxArea(int* height, int heightSize){
    int m=heightSize-1;
    int n=0;
    int smaller=0;
    int returndata=0;
    while(n<m)
    {
        smaller=height[n]<height[m]?height[n]:height[m];
        if(returndata<(smaller*(m-n)))
        returndata=(smaller*(m-n));
        if(height[n]<height[m])
        n++;
        else
        m--;
    }
    return returndata;
}
//修改成了双指针法，算是通过提交了。
