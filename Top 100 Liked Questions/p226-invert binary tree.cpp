/*
	Simply use a queue to swap the left subtree and the right subtree level by level (BFE)
	Time complexity: O(n)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}
};

TreeNode* BuildTree(vector<int> &tree){
	if(tree.empty())	return NULL;
	TreeNode *root = new TreeNode(tree[0]);
	queue<TreeNode*> que;
	que.push(root);
	int i = 1;
	while(i < tree.size()){
		TreeNode *node = que.front();
		que.pop();
		if(tree[i] != -1){
			node->left = new TreeNode(tree[i]);
			que.push(node->left);
		}
		if(i+1 < tree.size() && tree[i+1] != -1){
			node->right = new TreeNode(tree[i+1]);
			que.push(node->right);
		}
		i += 2;
	}
	return root;
}

TreeNode* Solution(TreeNode *root){
	if(!root)	return NULL;
	queue<TreeNode*> que;
	que.push(root);
	while(!que.empty()){
		TreeNode *node = que.front();
		que.pop();
		swap(node->left, node->right);
		if(node->left)	que.push(node->left);
		if(node->right)	que.push(node->right);
	}
	return root;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(int i=0; i<T; i++)
		cin >> tree[i];
	TreeNode *root = BuildTree(tree);
	TreeNode *ans = Solution(root);
	queue<TreeNode*> que;
	que.push(ans);
	while(!que.empty()){
		int n = que.size();
		for(int i=0; i<n; i++){
			TreeNode *node = que.front();
			que.pop();
			cout << node->val << " ";
			if(node->left)	que.push(node->left);
			if(node->right)	que.push(node->right);
		}cout << endl;
	}
}
