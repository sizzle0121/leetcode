/*
 * DFS, preorder traversal:
 * For the position which both trees have nodes, create a new node with value = t1->val+t2->val
 * Then both go to left subtree, then right subtree
 * The return value is the completed merged binary tree
 * For the position which only one tree has node, simply return the node to its parent,\ 
 * since the node and its children are already the completed merged binary tree
 *
 * Time complexity: O(n), the worse case is when both trees completely overlap, so we will need to go through all the nodes once
 *
 * */
#include <iostream>
#include <queue>
#include <vector>
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

TreeNode* Solution(TreeNode *t1, TreeNode *t2){
	TreeNode *node = NULL;
	if(t1 && t2){
		node = new TreeNode(t1->val + t2->val);
		node->left = Solution(t1->left, t2->left);
		node->right = Solution(t1->right, t2->right);
	}else if(t1){
		node = t1;
	}else if(t2){
		node = t2;
	}
	return node;
}

int main(){
	int T1, T2;
	cin >> T1 >> T2;
	vector<int> tree1(T1);
	vector<int> tree2(T2);
	for(int i=0; i<T1; i++)
		cin >> tree1[i];
	for(int i=0; i<T2; i++)
		cin >> tree2[i];
	TreeNode *t1 = BuildTree(tree1);
	TreeNode *t2 = BuildTree(tree2);
	TreeNode *ans = Solution(t1, t2);
	queue<TreeNode*> que;
	que.push(ans);
	while(!que.empty()){
		int n = que.size();
		for(int i=0; i<n; i++){
			TreeNode *node = que.front();
			cout << node->val << " ";
			if(node->left)	que.push(node->left);
			if(node->right)	que.push(node->right);
			que.pop();
		}
		cout << endl;
	}
}
