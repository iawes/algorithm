/*===============================================================
*   文件名称：tree.c
*   创建日期：2016年01月26日
================================================================*/
//#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct struc_node
{
    char data;
    struct struc_node *l_child;
    struct struc_node *r_child;
}TREENODE,*P_TREENODE;


int node_num = 0;
int leaf_num = 0;
//char ch[] = {'a', 'b', 'c', ' ', ' ', 'd', ' ', ' ', 'e', 'f', ' ', ' ', 'g', ' ', ' '};
char ch[] = "ABC##DE#G##F###";
char g_pre_tree[32] = {0};
char g_in_tree[32] = {0};
char g_post_tree[32] = {0};
int inc = 0;
int g_len = 0;

/* 按先序次序输入二叉树中节点的值，以空字符表示空树  */
int create_bitree(P_TREENODE *T)
{
    char i;

    if('#' == ch[inc++])
    {
        *T = NULL;
    }
    else
    {
// printf("%c ", ch[inc-1]);

        if(NULL == (*T = (P_TREENODE)malloc(sizeof(TREENODE))))
        {
            return -1;
        }

        (*T)->data = ch[inc - 1];
        printf("%c ", (*T)->data);

        create_bitree(&((*T)->l_child));
        create_bitree(&((*T)->r_child));
    }

    return 0;
}

/* 先序遍历二叉树  */
int pre_order_traverse(P_TREENODE T)
{
    if(NULL == T)
    {
        return -1;
    }

//    printf("%c ", T->data);

    //存储到数组中
    g_pre_tree[g_len] = T->data;
    g_len ++;

    pre_order_traverse(T->l_child);
    pre_order_traverse(T->r_child);

    return 0;
}

/* 中序遍历二叉树  */
int in_order_traverse(P_TREENODE T)
{
    if(NULL == T)
    {
        return -1;
    }

    in_order_traverse(T->l_child);

 //   printf("%c ", T->data);
    //存储到数组中
    g_in_tree[g_len] = T->data;
    g_len ++;

    in_order_traverse(T->r_child);

    return 0;
}

/* 后序遍历二叉树  */
int post_order_traverse(P_TREENODE T)
{
    if(NULL == T)
    {
        return -1;
    }

    post_order_traverse(T->l_child);

    post_order_traverse(T->r_child);

  //  printf("%c ", T->data);
    //存储到数组中
    g_post_tree[g_len] = T->data;
    g_len ++;

    return 0;
}

/* 先序遍历计算树中的节点数  */
int count_node_num(P_TREENODE T)
{
    if(NULL == T)
    {
        return -1;
    }

    node_num ++;

    count_node_num(T->l_child);
    count_node_num(T->r_child);

    return 0;
}

/* 先序遍历计算树中的叶子节点数  */
int count_leaf_num(P_TREENODE T)
{
    if(NULL == T)
    {
        return -1;
    }

    if((NULL != T->l_child) && (NULL != T->r_child))
    {
        leaf_num ++;
    }

    count_leaf_num(T->l_child);
    count_leaf_num(T->r_child);

    return 0;
}

//根据先序和中序求后序
P_TREENODE  post_by_pre_and_in(char *preorder, char *inorder, int len)
{
    int i = 0;
    int j = 0;
    char c = 0;

    if(0 >= len)
    {
        return NULL;
    }

    c = preorder[0];

    for(i=0; i<len; i++)
    {
        if(c == inorder[i])
            break;
    }
    j = i + 1;

    P_TREENODE T = (P_TREENODE)malloc(sizeof(TREENODE));

    T -> data = c;

    T->l_child = post_by_pre_and_in(preorder + 1, inorder, i);
    T->r_child = post_by_pre_and_in(preorder + j, inorder + j, len - j);

    return T;
}

//根据后序和中序求先序
P_TREENODE pre_by_post_and_in(char *postorder, char *inorder, int len)
{
    int i = 0;
    int j = 0;
    char c = 0;

    if(0 >= len)
    {
        return NULL;
    }

    c = postorder[len - 1];

    for(i=0; i<len; i++)
    {
        if(c == inorder[i])
            break;
    }
    j = i + 1;

    P_TREENODE T = (P_TREENODE)malloc(sizeof(TREENODE));

    T -> data = c;

    T -> l_child = pre_by_post_and_in(postorder, inorder, i);
    T -> r_child = pre_by_post_and_in(postorder + i, inorder + j, len - j);

    return T;
}

int main(void)
{
//    initscr();

    P_TREENODE test_tree;
    int i;

    create_bitree(&test_tree);

    do
    {
        printf("\n");
        printf("**********************************************\n");
        printf("*     you can choose:     \n");
        printf("*  1:  Traverse the Binary tree by pre order     *\n");
        printf("*  2:  Traverse the Binary tree by mid order     *\n");
        printf("*  3:  Traverse the Binary tree by back order    *\n");
        printf("*  4:  Count the node num of the Binary tree     *\n");
        printf("*  5:  Count the leaf node num of the Binary tree*\n");
        printf("*  6:  find postorder by preorder and inorder*\n");
        printf("*  7:  find preorder by postorder and inorder*\n");
        printf("**********************************************\n");

        printf("please input your choice:");
        scanf("%d", &i);

        switch(i)
        {
            case 1:
            {
                printf("----->The Preorder is :\n");
                g_len = 0;
                memset(g_pre_tree, 0, sizeof(g_pre_tree));

                pre_order_traverse(test_tree);

                printf("\ng_pre_tree is: %s\n", g_pre_tree);
                printf("\n");

                break;
            }

            case 2:
            {
                printf("----->The midorder is :\n");
                g_len = 0;
                memset(g_in_tree, 0, sizeof(g_in_tree));

                in_order_traverse(test_tree);

                printf("\ng_in_tree is: %s\n", g_in_tree);
                printf("\n");

                break;
            }

            case 3:
            {
                printf("----->The postorder is :\n");
                g_len = 0;
                memset(g_post_tree, 0, sizeof(g_post_tree));

                post_order_traverse(test_tree);

                printf("\ng_post_tree is: %s\n", g_post_tree);
                printf("\n");

                break;
            }

            case 4:
            {
                count_node_num(test_tree);
                printf("----->The node num of the tree is %d\n", node_num);
                break;
            }

            case 5:
            {
                count_leaf_num(test_tree);
                printf("----->The leaf num of the tree is %d\n", leaf_num);
                break;
            }

            case 6:
            {
                // 求出preorder 序列
                g_len = 0;
                memset(g_pre_tree, 0, sizeof(g_pre_tree));
                pre_order_traverse(test_tree);
                printf("\ng_pre_tree is: %s\n", g_pre_tree);

                // 求出inorder 序列
                g_len = 0;
                memset(g_in_tree, 0, sizeof(g_in_tree));
                in_order_traverse(test_tree);
                printf("\ng_in_tree is: %s\n", g_in_tree);

                // 构建新的二叉树
                P_TREENODE new_tree = NULL;

                new_tree = post_by_pre_and_in(g_pre_tree, g_in_tree, strlen(g_in_tree));

                g_len = 0;
                memset(g_post_tree, 0, sizeof(g_post_tree));
                printf("\ng_post_tree is: %s\n", g_post_tree);
                post_order_traverse(new_tree);
                printf("\ng_post_tree is: %s\n", g_post_tree);

                break;
            }

            case 7:
            {
                // 求出postorder 序列
                g_len = 0;
                memset(g_post_tree, 0, sizeof(g_post_tree));
                post_order_traverse(test_tree);
                printf("\ng_post_tree is: %s\n", g_post_tree);

                // 求出inorder 序列
                g_len = 0;
                memset(g_in_tree, 0, sizeof(g_in_tree));
                in_order_traverse(test_tree);
                printf("\ng_in_tree is: %s\n", g_in_tree);

                // 构建新的二叉树
                P_TREENODE post_tree = NULL;

                post_tree = pre_by_post_and_in(g_post_tree, g_in_tree, strlen(g_in_tree));

                // 求出preorder 序列
                g_len = 0;
                memset(g_pre_tree, 0, sizeof(g_pre_tree));
                printf("\ng_pre_tree is: %s\n", g_pre_tree);
                pre_order_traverse(post_tree);
                printf("\ng_pre_tree is: %s\n", g_pre_tree);

                break;
            }
            default:
                break;
        }

        printf("please input any char to go on\n");
        getchar();
    }while((1<=i) && (8 > i));

    getchar();

//    endwin();
    return 0;
}
