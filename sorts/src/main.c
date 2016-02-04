/*===============================================================
*   文件名称：main.c
*   创建日期：2016年01月25日
================================================================*/
#include <stdio.h>
#include "insert.h"

void PrintArray(int A[], int n)
{
    int i = 0;

    for(i = 0; i < n; i ++)
    {
        printf("%d ", A[i]);
    }

    printf("\n");

    return;
}

int main(void)
{
    int Array[] = {0, 2, 3, 44, 77, 11, 33, 22, 66, 88, 21, 18};

    printf("array element are:\n");
    PrintArray(Array, 12);

    InsertionSort(Array, 12);
    printf("after sort, array element are:\n");
    PrintArray(Array, 12);

    return 0;
}


