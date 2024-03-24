#include <stdio.h>
#include <malloc.h>
struct tree_node{
    int val;
    struct tree_node *left;
    struct tree_node *right;
};
int temp=-1;
typedef  struct tree_node TreeNode;
TreeNode* insert(TreeNode* root, TreeNode* node)
{
    if (root == NULL)
    {
        printf("%d\n",temp);
        return node;
    }
    temp=root->val;
    if (node->val > root->val)
    {
        root->right = insert(root->right, node);
    }
    else if (node->val < root->val)
    {
        root->left = insert(root->left, node);
    }
    return root;
}
int main()
{
    int n,i,t;
    scanf("%d%d",&n,&t);
    TreeNode *root;
    root=(TreeNode*)malloc(sizeof(TreeNode));
    root->val=t;
    printf("-1\n");
    for(i=1;i<n;i++)
    {
        scanf("%d",&t);
        TreeNode *p;
        p=(TreeNode*)malloc(sizeof(TreeNode));
        p->val=t;
        insert(root,p);
    }
    return 0;
}
