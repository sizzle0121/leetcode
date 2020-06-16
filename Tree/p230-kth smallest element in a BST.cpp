/*
 * Inorder traversal:
 * Simply do inorder traversal and count for the kth element
 *
 * Time complexity: O(k)
 * Space complexity: O(1)
 *
 * For the follow-up:
 * The solution provided by leetcode still need O(h + k), h: height of the tree, k: kth\ 
 * to achieve returning the kth element while the BST may be frequently inserted/deleted
 * Therefore, it is nearly the same as we just do inorder traversal each time and count for the kth element
 * (O(h) for insert/delete, then do inorder traversal, which is O(k) -> O(h + k))
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

bool inorder(TreeNode *root, int &k, int &ans){
	if(!root) return false;
	if(inorder(root->left, k, ans)) return true;
	if(--k == 0){
		ans = root->val;
		return true;
	}
	if(inorder(root->right, k, ans)) return true;
	return false;
}

int Solution(TreeNode *root, int k){
	int ans = 0;
	inorder(root, k, ans);
	return ans;
}

int main(){
	int T, k;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	cin >> k;
	TreeNode *root = BuildTree(tree);
	cout << Solution(root, k) << endl;
}
