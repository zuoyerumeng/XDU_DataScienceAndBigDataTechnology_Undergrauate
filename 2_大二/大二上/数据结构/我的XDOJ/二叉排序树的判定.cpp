#include<iostream>
#include<malloc.h>
using namespace std;
int Tree[100001][3];
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct TreeNode TreeNode;

bool Check(TreeNode *root)
{
    if(root->left)
    {
        if(root->left->val<root->val && Check(root->left)) ;
        else return false;
    }
    if(root->right)
    {
        if(root->right->val>root->val && Check(root->right)) ;
        else return false;
    }
    return true;
}

TreeNode* Create(int head)
{
    if(!head) return NULL;
    TreeNode *root;
    root=(TreeNode*)malloc(sizeof(TreeNode));
    root->val=Tree[head][0];
    root->left=Create(Tree[head][1]);
    root->right=Create(Tree[head][2]);
    return root;
}

/*
void midorder(TreeNode *root)
{
        if(!root) return;
        midorder(root->left);
        cout<<root->val<<" ";
        midorder(root->right);
}
*/
 
int main()
{
    int n,i,head;
    cin>>n>>head;
    for(i=1;i<=n;i++) cin>>Tree[i][0]>>Tree[i][1]>>Tree[i][2];
    TreeNode *root=Create(head);
    //midorder(root);
	if(Check(root)) cout<<"true";
    else cout<<"false";  
}



