/*
 * DFS:
 * For each node as a root, the maximum length is the depth of its left subtree + that of its right subtree
 * And return the longer depth + 1 to its parent node to see if there is longer length
 * The leaves simply return 1 + 0 (the 1 is the edge between it and its parent, 0 cuz it donesn't have subtree)
 * By updateing our answer during DFS, we are finally able to find the diameter of the tree
 * 
 * Time complexity: O(n), we only visit every node once
 * */
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int _val): val(_val), left(NULL), right(NULL){}
};

TreeNode* BuildTree(vector<int> &tree){
	if(tree.empty())	return NULL;
	TreeNode *root = new TreeNode(tree[0]);
	queue<TreeNode*> que;
	que.push(root);
	int i = 1;
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

int DFS(TreeNode *node, int &ans){
	int l = 0, r = 0;
	if(node->left)	l = DFS(node->left, ans);
	if(node->right) r = DFS(node->right, ans);
	if(l+r > ans)	ans = l+r;
	return 1 + max(l, r);
}

int Solution(TreeNode *root){
	if(!root)	return 0;
	int ans = 0;
	DFS(root, ans);	
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(int i=0; i<T; i++)
		cin >> tree[i];
	TreeNode *root = BuildTree(tree);
	cout << Solution(root) << endl;
}
