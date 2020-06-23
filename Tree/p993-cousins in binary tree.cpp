/*
 * BFS:
 * Simply do BFS, record parent nodes, and look if x and y present in the same level and have different parents
 * We can also insert a null pointer to split the children of different parents\ 
 * to avoid using pair
 *
 * Time complexity: O(n)
 * Space complexity: O(k), k: the maximum number of nodes in the same level
 *
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

bool Solution(TreeNode *root, int x, int y){
	if(!root) return false;
	queue<pair<TreeNode*, int> > que;
	que.push(pair<TreeNode*, int>(root, -2));
	int xpar = -1, ypar = -1;
	while(!que.empty()){
		int n = que.size();
		for(int i=0; i<n; ++i){
			pair<TreeNode*,int> node = que.front();
			que.pop();
			if(node.first->val == x) xpar = node.second;
			else if(node.first->val == y) ypar = node.second;
			if(xpar != -1 && ypar != -1) return (xpar != ypar)? true : false;
			if(node.first->left) que.push(pair<TreeNode*,int>(node.first->left, node.first->val));
			if(node.first->right) que.push(pair<TreeNode*,int>(node.first->right, node.first->val));
		}
		if(xpar != -1 || ypar != -1) return false;
	}
	return false;
}

int main(){
	int T, x, y;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	cin >> x >> y;
	cout << Solution(BuildTree(tree), x, y) << endl;
}
