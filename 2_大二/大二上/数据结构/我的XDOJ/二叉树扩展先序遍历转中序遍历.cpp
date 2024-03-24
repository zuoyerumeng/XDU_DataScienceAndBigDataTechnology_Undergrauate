#include<stdio.h>
#include<malloc.h> 
struct tree_node{
	char val;
	struct tree_node *left;
	struct tree_node *right;
};
typedef  struct tree_node TreeNode;

int ans=0;//????????'#'????? 

TreeNode* create()
{
	char value;
	scanf("%c", &value);
	if (value == '#')
	{
		ans++;
		return NULL;
	}
	else
	{
		TreeNode *root;
		root = (TreeNode*)malloc(sizeof(TreeNode));
		root->val = value;
		root->left = create();
		root->right = create();
		return root;
	}
}

void midorder(TreeNode *root)
{
	if(!root) return;
	midorder(root->left);
	printf("%c ",root->val);
	midorder(root->right);
}

int main()

{
	TreeNode *root=create();
	midorder(root);
}
 

