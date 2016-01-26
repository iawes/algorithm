/*===============================================================
*   文件名称：tree.c
*   创建日期：2016年01月26日
================================================================*/
//#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

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
int inc = 0;

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

    printf("%c ", T->data);

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

    printf("%c ", T->data);

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

    printf("%c ", T->data);

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
        printf("**********************************************\n");

        printf("please input your choice:");
        scanf("%d", &i);

        switch(i)
        {
            case 1:
            {
                printf("----->The Preorder is :\n");
                pre_order_traverse(test_tree);
                printf("\n");

                break;
            }

            case 2:
            {
                printf("----->The midorder is :\n");
                in_order_traverse(test_tree);
                printf("\n");

                break;
            }

            case 3:
            {
                printf("----->The postorder is :\n");
                post_order_traverse(test_tree);
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

            default:
                break;
        }

        printf("please input any char to go on\n");
        getchar();
    }while((1<=i) && (6 > i));

    getchar();

//    endwin();
    return 0;
}
