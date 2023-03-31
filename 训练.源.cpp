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
---三数之和---
int cmp(const void* pa, const void* pb){
    int a=*(int*)pa;
    int b=*(int*)pb;
    return a>b?1:-1;
}
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int base=100;//数组的初始长度，可更改
    //初始化处理返回值，二维数组的大小和保存每一个一维数组大小的数组的空间保持一致
    int** res=(int**)malloc(sizeof(int*)*base);
    *returnColumnSizes=(int*)malloc(sizeof(int)*base);
    *returnSize=0;
    int i,j,k;
    //排序
    qsort(nums,numsSize,sizeof(int),cmp);
    for(i=0;i<numsSize;i++){
        //先确定第三个数的值，再对剩下的两个数进行两数之和的操作
        //若本次的第三个数与上一次的情况相同，则跳过这个数
        if(i>0&&nums[i]==nums[i-1])
            continue;
        //给定nums[i]，以j，k作为双指针进行两数之和操作
        j=i+1;
        k=numsSize-1;
        while(j<k){
            int sum=nums[i]+nums[j]+nums[k];
            if(sum==0){//刚好遇见符合要求的三元组
                //申请返回值二维数组的空间
                res[*returnSize]=(int*)malloc(sizeof(int)*3);
                //每一个数组大小都为3
                (*returnColumnSizes)[*returnSize]=3;
                //给申请的空间赋值
                res[*returnSize][0]=nums[i];
                res[*returnSize][1]=nums[j];
                res[*returnSize][2]=nums[k];
                //二维数组的行数加1
                (*returnSize)++;
                //如果二维数组的大小达到初始设定的行数，则进行空间扩容
                if(*returnSize==base){
                    base*=2;
                    res=(int**)realloc(res,sizeof(int*)*base);
                    *returnColumnSizes=(int*)realloc(*returnColumnSizes,sizeof(int)*base);
                }
                //记录符合要求的两个数，进行去重
                int num1=nums[j],num2=nums[k];
                while(nums[j]==num1&&j<k)
                    j++;
                while(nums[k]==num2&&j<k)
                    k--;
            }
            //若三个数之和小于0，则左边的指针右移
            else if(sum<0)
                j++;
            //若三个数的之和大于0，则右边的指针往左移
            else k--;
        }
    }
    return res;
}                                                                          -------出处：leetcode.cn烟火。
这题好难，需要较长时间的琢磨。
---竞赛准备好难---
	bool isValid(char * s){
    char *a=(char*)malloc(sizeof(char)*10000);
    int top=-1;
    int n=strlen(s);
    if(n%2!=0)
    return false;
    for(int i=0;i<n;i++)
    {
        if(s[i]=='('||s[i]=='{'||s[i]=='[')
        {top++;
        switch(s[i])
        {
            case '(':a[top]=')';break;
            case '[':a[top]=']';break;
            case '{':a[top]='}';break;
        }
        }
        else
        {
            if(top<0)
            return false;
            if(s[i]!=a[top])
            return false;
            else
            top--;
        }
    }
    if(top!=-1)
    return false;
    return true;
}
初识栈，借助题解慢慢理解
---还是得靠自己啊，不然什么用都没有，要学习深搜广搜还有动规---
#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int coef;
	int expon;
	struct node* next;
}Node;
void Attach(int c, int e, node** head)
{
	node* p = (node*)malloc(sizeof(node));
	p->coef = c;
	p->expon = e;
	p->next = NULL;
	(*head)->next = p;
	*head = p;
}
node *creatnode(int num)
{
	node* P, *Rear, *t;
	int c, e;
	P = (node*)malloc(sizeof(node));
	P->next = NULL;
	Rear = P;
	while (num--)
	{
		scanf_s("%d %d", &c, &e);
		Attach(c, e, &Rear);
	}
	t = P;P = P->next;free(t);
	return P;
}
node* deal(node* p1, node* p2)
{
	node* front, * rear, * temp;
	rear = (node*)malloc(sizeof(node));
	front = rear;
	while (p1 && p2)//单循环的原因是，链表的指数是由大到小排列好的
	{
		if (p1->expon > p2->expon)
		{
			Attach(p1->coef, p1->expon, &rear);
				p1 = p1->next;
		}
		else if (p1->expon < p2->expon)
		{
			Attach(p2->coef, p2->expon, &rear);
			p2 = p2->next;
		}
		else
		{
			if (p1->coef + p2->coef != 0)
			{
				Attach(p1->coef + p2->coef, p1->expon, &rear);
					p1 = p1->next;
				p2 = p2->next;
			}

		}
	}
	for (;p1;p1->next)
		Attach(p1->coef, p1->expon, &rear);
	for (;p2;p2->next)
		Attach(p2->coef, p2->expon, &rear);
	temp = front;
	front = front->next;
	free(temp);
	return front;
}
void put(node* p)
{
	while (p)
	{
		printf("%d	%d	", p->coef, p->expon);
		p = p->next;
	}
}
int main()
{
	node* P1, * P2, * PS;
	printf("enter P1:\n");
	P1 = creatnode(5);
	printf("enter P2:\n");
	P2 = creatnode(4);
	printf("answer:\n");
	PS=deal(P1,P2);
	put(PS);
	return 0;
}
 void dealtree(struct TreeNode* root,int *a,int *Size)
 {
     if(root)
     {
         dealtree(root->left,a,Size);
         a[(*Size)++]=root->val;
         dealtree(root->right,a,Size);
     }
 }
int* inorderTraversal(struct TreeNode* root, int* returnSize){
    int *res=(int*)malloc(sizeof(int)*100);
    *returnSize=0;
    dealtree(root,res,returnSize);
    return res;
}
