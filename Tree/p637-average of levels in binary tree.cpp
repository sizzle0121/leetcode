/*
 * BFS:
 * Simply do BFS and calculate the average level by level
 *
 * Time complexity: O(n)
 * Space complexity: O(k), k: the maximum number of nodes in a level
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

vector<double> Solution(TreeNode *root){
	vector<double> ans;
	if(!root) return ans;
	queue<TreeNode*> que;
	que.push(root);
	while(!que.empty()){
		int n = que.size();
		double sum = 0.0;
		for(int i=0; i<n; ++i){
			TreeNode *node = que.front();
			que.pop();
			sum += node->val;
			if(node->left) que.push(node->left);
			if(node->right) que.push(node->right);
		}
		ans.push_back((double)(sum/n));
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	vector<double> ans(Solution(BuildTree(tree)));
	for(auto &avg: ans)
		cout << avg << " ";
	cout << endl;
}
