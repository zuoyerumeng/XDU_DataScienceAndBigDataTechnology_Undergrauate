#include<stdio.h>
#include<malloc.h>
#include<string.h> 

struct tree_node{
        char val;
        struct tree_node *left;
        struct tree_node *right;
};
typedef  struct tree_node TreeNode;

TreeNode* create(char *pre,char *mid,int len)
{
	int i;
	if(!len) return NULL;
	TreeNode *root;
	root=(TreeNode*)malloc(sizeof(TreeNode));
	root->val=pre[0];//??????????????? 
	for(i=0;i<len;i++)
	{
		if(pre[0]==mid[i]) break;
	}
	root->left=create(pre+1,mid,i);
	root->right=create(pre+i+1,mid+i+1,len-i-1);
	return root;
}

 void postorder(TreeNode* root)//??????? 
 {
 	if(!root) return;
 	postorder(root->left);
 	postorder(root->right);
 	printf("%c",root->val);
 	return;
 }

int main()
{
	char *pre,*mid;
	pre=(char*)malloc(sizeof(char));
	mid=(char*)malloc(sizeof(char));
	scanf("%s",pre);
	scanf("%s",mid);
	TreeNode *root=create(pre,mid,strlen(pre));
	postorder(root);
	return 0;
}

