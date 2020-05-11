/*
	Preorder traversal
	Use a pointer to connect all TreeNodes with preorder traversal
	Since we travel in preorder way, the return pointer will be the tail of the linked list which should be the preorder of the original tree
	so we only need to keep connecting nodes to its right

	Time complexity: O(n)
	Space complexity: O(1)
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x): val(x), left(NULL), right(NULL) {} 
};

TreeNode* BuildTree(vector<int> &tree){
	if(tree.empty())	return NULL;
	TreeNode *root = new TreeNode(tree[0]);
	queue<TreeNode*> que;
	que.push(root);
	int i=1;
	while(i < tree.size()){
		if(tree[i] != -1){
			que.front()->left = new TreeNode(tree[i]);
			que.push(que.front()->left);
		}
		if(i+1 < tree.size() && tree[i+1] != -1){
			que.front()->right = new TreeNode(tree[i+1]);
			que.push(que.front()->right);
		}
		i += 2;
		que.pop();
	}
	return root;
}

TreeNode* preorder(TreeNode *node, TreeNode *tail){
	TreeNode *tmp = NULL;
	if(node->right)	tmp = node->right;
	tail = node;
	if(node->left){
		tail->right = node->left;
		node->left = NULL;
		tail = preorder(tail->right, tail);
	}
	if(tmp){
		tail->right = tmp;
		tail = preorder(tail->right, tail);
	}
	return tail;
}

void Solution(TreeNode *root){
	if(!root)	return;
	preorder(root, root);
	while(root){
		cout << root->val << " ";
		root = root->right;
	}cout << endl;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(int i=0; i<T; i++)
		cin >> tree[i];
	TreeNode *root = BuildTree(tree);
	Solution(root);
	return 0;
}
