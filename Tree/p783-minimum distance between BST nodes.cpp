/*
 * Inorder Traversal:
 * Do inorder traversal and then either store the result in an array and iterate numbers by numbers\ 
 * or calcaulte the minimum distance during the traversal (should be the nearest two nodes)
 *
 * Time complexity: O(n)
 * Space complexity: O(n) for storing in an array, O(1) for calculating during the traversal
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
	TreeNode(int _val): val(_val), left(NULL), right(NULL) {}
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

pair<int,int> inorder(TreeNode *node, int &ans){
	pair<int,int> l = make_pair(node->val, node->val), r = l;
	if(node->left){
		l = inorder(node->left, ans);
		ans = min(ans, node->val - l.second);
	}
	if(node->right){
		r = inorder(node->right, ans);
		ans = min(ans, r.first - node->val);
	}
	return pair<int,int>(l.first, r.second);
}

int Solution(TreeNode *root){
	if(!root || (!root->left && !root->right)) return 0;
	int ans = INT_MAX;
	inorder(root, ans);
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	TreeNode *root = BuildTree(tree);
	cout << Solution(root) << endl;
}
