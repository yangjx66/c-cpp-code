#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define DEBUG(x) printf("%d\r\n", x)

typedef struct BiTree { // basic data structure
    char data;
    BiTree *left_child;
    BiTree *right_child;
} BiTree, *BiNode;

BiNode create_node()
{
    BiNode T = NULL;
    char input = 0x00;

    printf("input character: ");
    scanf("%c", &input);

    if (input == '.')
    {
        return NULL; // empty node, no left and right child
    }
    else
    {
        T = (BiNode)malloc(sizeof(BiTree));
        T->data = input;
        T->left_child = create_node();
        T->right_child = create_node();
    }

    return T;
}

// Traverse
void pre__travers(BiNode root)
{
    if (root != NULL)
    {
        printf("%c  ", root->data);
        pre__travers(root->left_child);
        pre__travers(root->right_child);
    }
}

void mid__travers(BiNode root)
{
    if (root != NULL)
    {
        mid__travers(root->left_child);
        printf("%c  ", root->data);
        mid__travers(root->right_child);
    }
}

void post__travers(BiNode root)
{
    if (root != NULL)
    {
        post__travers(root->left_child);
        post__travers(root->right_child);
        printf("%c  ", root->data);
    }
}

void level_traver(BiNode root)
{
    BiNode queue[20] = {NULL}, pTemp = NULL;
    int cur = 0, pre = 0; // cur表示当前入队列的节点，pre表示当前出队列的节点
    queue[cur++] = root;

    while (cur != pre)
    {
        pTemp = queue[pre++];
        printf("%c  ", pTemp->data);
        if (pTemp->left_child != NULL)
        {
            queue[cur++] = pTemp->left_child;
        }
        if (pTemp->right_child != NULL)
        {
            queue[cur++] = pTemp->right_child;
        }
    }
}

int main()
{


    return 0;
}
