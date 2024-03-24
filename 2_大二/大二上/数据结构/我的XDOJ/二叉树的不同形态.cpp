#include<iostream> 
#include<malloc.h>
#include<string.h>
using namespace std;
struct tree_node{
    int val;
    struct tree_node *left;
    struct tree_node *right;
};
typedef  struct tree_node TreeNode;

TreeNode* create(int *lev,int *mid,int len)
{
    int i;
    if(!len) return NULL;
    TreeNode *root;
    root=(TreeNode*)malloc(sizeof(TreeNode));
    root->val=lev[0];//由前序遍历的特点递归
    for(i=0;i<len;i++)
    {
        if(lev[0]==mid[i]) break;
    }
    int lev1[1024],lev2[1024],l1=0,l2=0,index=i;
    for(i=1;i<len;i++)
    {
        int flag=0;
        for(int j=0;j<index;j++)
        {
            if(mid[j]==lev[i])
            {
                lev1[l1++]=lev[i];
                flag=1;
                break;
            }
        }
        if(!flag)lev2[l2++]=lev[i];
    }
    root->left=create(lev1,mid,index);
    root->right=create(lev2,mid+index+1,len-index-1);
    if(len==1) cout<<lev[0]<<" ";
    return root;
}

void preorder(TreeNode *root)
{
    if(!root) return;
    cout<<root->val<<" ";
    preorder(root->left);
    preorder(root->right);
}


void postorder(TreeNode* root)//后序遍历
{
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->val<<" ";
    return;
}

int main()
{
    int lev[1024],mid[1024],len,i;
	cin>>len;
    for(i=0;i<len;i++) cin>>lev[i];
    for(i=0;i<len;i++) cin>>mid[i];
    TreeNode *root=create(lev,mid,len);
    cout<<""<<endl;
    preorder(root);
    cout<<""<<endl;
    postorder(root);
    return 0;
}
