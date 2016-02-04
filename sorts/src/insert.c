/*===============================================================
*   文件名称：insert.c
*   创建日期：2016年01月25日
================================================================*/
#include "insert.h"

void InsertionSort(int A[], int n)
{
    int j, i;

    int Tmp;

    for(i = 1; i < n; i ++)
    {
        Tmp = A[i];
        for(j = i; j > 0 && A[j -1] > Tmp; j --) //将一个记录插入到已排好的有序表中
        {
            A[j] = A[j - 1];
        }
        A[j] = Tmp;
    }

    return;
}

void InsertionSortWhile(int A[], int n)
{
    for(int i = 1; i < n; i ++)
    {
        int tmp = A[i]; //记录辅助空间
        int j = i - 1;

        while(j > -1 && A[j] > A[i])
        {
            A[j+1] = A[j];
            --j;
        }
        A[j+1] = tmp;
    }

    return ;
}
