/*===============================================================
*   文件名称：find_loop_string.c
*   创建日期：2016年01月29日
================================================================*/
//#include "find_loop_string.h"
#include <stdio.h>
#include <string.h>

//char *pg_test_srt[] = "babcbabcbaccba";

char *find_loop_string_max(char *p_src_str, int len)
{
    int i = 0;
    int j = 0;
    int center = 0;
    int maxnum = 0;

    if(NULL == p_src_str)
    {
        return NULL;
    }

    for(i=1; i<len; i++)
    {
        j = 1;

        while((len > (i+j)) && (0 <= (i-j)) && (p_src_str[i+j] ==  p_src_str[i-j]))
        {
            j ++;
        }

        j --;

        if((j > 1) && (j > maxnum))
        {
            maxnum = j;
            center = i;
        }

    }

    p_src_str[center + maxnum + 1] = 0;

    return (p_src_str + center - maxnum);
}

int main(void)
{
    char *p_max_loop_str = NULL;
    char pg_test_srt[] = "babcbabcbaccba";

    int len = strlen(pg_test_srt);

    p_max_loop_str = find_loop_string_max(pg_test_srt, len);

    printf("%s\n", p_max_loop_str);

    return 0;
}
