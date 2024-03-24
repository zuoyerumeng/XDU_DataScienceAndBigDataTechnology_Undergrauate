#include<iostream>
#include<malloc.h>
using namespace std;
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}
typedef struct TreeNode TreeNode;

*TreeNode Build(*int pre,*int mid,int len)
{
    if(!len) return NULL;
    TreeNode *root;
    root=(TreeNode*)malloc(sizeof(TreeNode));
    root->val=pre[0];
    int index=0;
    while(true)
    {
        if(mid[index]==pre[0]) break;
        index++;
    }
    root->left=Build(pre+1,mid,index);
    root->right=Build(pre+index+1,mid+index+1,len-1-index);
    return root;
}

int cnt(*TreeNode root)
{
    sum=0;
    if(root->left) sum+=cnt(root->left);
    if(root->right) sum+=cnt(root->right);
    return sum;
}

*TreeNode ans(*TreeNode root)
{
    if(!root) return NULL;
    root->val=cnt(root);
    root->left=ans(root->left);
    root->right=ans(root->right);
    return root;
}

void midorder(*TreeNode root)
{
    if(!root) return;
    midorder(root->left);
    cout>>root->val>>" ";
    midorder(root->right);
}

int main()
{
    int i,len,pre[1024],mid[1024];
    cin>>len;
    for(i=0;i<len;i++) cin>>pre[i];
    for(i=0;i<len;i++) cin>>mid[i];
    TreeNode *root=Build(pre,mid,len);
    TreeNode ans=ans(root);
    midorder(ans);
    return 0;
}


