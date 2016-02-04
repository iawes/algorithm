/*===============================================================
*   文件名称：palindrome.c
*   创建日期：2016年02月01日
================================================================*/
//#include "palindrome.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_palindrome(const char *p_src_str, char *p_output_str, int src_len, int *p_output_len)
{
    int max = 0;
    int max_right = 0;
    int pos = 0;
    int i = 0;
    int rl_max = 0;

    char *p_str_tmp = NULL;
    int *RL = NULL;

    //判断输入是否合法
    if((NULL == p_src_str) || (NULL == p_output_str))
    {
        return NULL;
    }

    //数据初始化
    int temp = (src_len << 1) + 1;
    p_str_tmp = (char *)malloc(temp);
    if(NULL == p_src_str)
    {
        return NULL;
    }
    memset(p_str_tmp, 0, temp);
    RL = (int *)malloc(temp*sizeof(int));
    if(NULL == RL)
    {
        return NULL;
    }
    memset(RL, 0, temp*sizeof(int));

//    p_str_tmp[0] = '#';

    //转换原字符串
    for(i=0; i<temp; i+=2)
    {
        p_str_tmp[i] = '#';
        p_str_tmp[i+1] = p_src_str[i/2];
    }

//    for(i=0; i<temp; i++)
//    {
//        if(0 != (i % 2))
//        {
//            p_str_tmp[i] = p_src_str[i/2];
//        }
//        else
//        {
//            p_str_tmp[i] = '#';
//        }
//    }

//    RL[0] = 1;
//    RL[1] = 2;
//    pos = 1;
//    max_right = 2;
//    rl_max = 1;

    //核心算法
    for(i=0; i<temp; i++)
    {
        if(i < max_right)
        {
            RL[i] = ((RL[2*pos-i])<(max_right-i+1))?(RL[2*pos-i]):(max_right-i+1);
        }
        else
        {
            RL[i] = 1;
        }

        //确定查找边界
        while((0 <= (i-RL[i])) && (temp > (i+RL[i])) && (p_str_tmp[i+RL[i]] == p_str_tmp[i-RL[i]]))
        {
            RL[i] ++;
        }

        //更新触及到的最右字符
        if((RL[i]+i) > max_right)
        {
            max_right = RL[i] + i - 1;
            pos = i;
        }

        //记录最大回文长度所在的位置
        if(RL[i] > RL[rl_max])
        {
            rl_max = i;
        }

        //当超过可能的最大长度时就停止
        if((i >= src_len) && (RL[rl_max] >= (temp - i)))
        {
            break;
        }
    }

    for(i=0; i<temp; i++)
    {
        printf("%d ", RL[i]);
    }
    printf("\n");

    *p_output_len = RL[rl_max] - 1;

    memcpy(p_output_str, p_src_str + ((rl_max-*p_output_len)/2), *p_output_len);
    p_output_str[*p_output_len] = 0;

    free(p_str_tmp);
    p_str_tmp = NULL;
    free(RL);
    RL = NULL;

    return p_output_str;
}

int main(void)
{
//    char *p_str = "abba";
    //char *p_str = "abbacabbaefghijklmnopq";
    char *p_str = "efghijklmnopqabbacabba";
    char *p_output = NULL;
    int len = 0;

    p_output = (char *)malloc(strlen(p_str));
    if(NULL == p_output)
    {
        return -1;
    }

    get_palindrome(p_str, p_output, strlen(p_str), &len);

    printf("%s\n", p_output);

    free(p_output);

    return 0;
}
