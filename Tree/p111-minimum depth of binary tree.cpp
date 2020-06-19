/*
 * BFS:
 * Simply do BFS and search for leaf node\ 
 * once we found a leaf node, return the current count of level
 *
 * Time complexity: O(n)
 * Space complexity: O(2^(logn - 1) - 2^(logn - 2))
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int _val): val(_val), left(NULL), right(NULL){}
};

TreeNode* BuildTree(vector<int> &tree){
	if(tree.empty()) return NULL;
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

int Solution(TreeNode *root){
	if(!root) return 0;
	queue<TreeNode*> que;
	que.push(root);
	int ans = 1;
	while(!que.empty()){
		int n = que.size();
		for(int i=0; i<n; ++i){
			TreeNode *tmp = que.front();
			que.pop();
			if(!tmp->left && !tmp->right) return ans;
			if(tmp->left) que.push(tmp->left);
			if(tmp->right) que.push(tmp->right);
		}
		ans++;
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	cout << Solution(BuildTree(tree)) << endl;
}
