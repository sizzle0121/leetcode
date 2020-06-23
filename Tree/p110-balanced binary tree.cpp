/*
 * DFS + DC:
 * Every node return its height to its parent\ 
 * For parent nodes, check if the difference of its subtrees' heights is greater than one\ 
 * or if one of its subtree is already NOT height-balanced
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
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

int traverse(TreeNode *node){
	if(!node) return 0;
	int l = traverse(node->left), r = traverse(node->right);
	if(l == -1 || r == -1) return -1;
	if(abs(l - r) > 1) return -1;
	return max(l, r) + 1;
}

bool Solution(TreeNode *root){
	return !root || (traverse(root) != -1);
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	cout << Solution(BuildTree(tree)) << endl;
}
