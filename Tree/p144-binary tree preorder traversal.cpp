/*
 * Recursion is trivial.
 *
 * Iterative method can use a stack and push child nodes in reverse order to complete
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 *
 * */
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left, *right;
	TreeNode(int _val): val(_val), left(NULL), right(NULL) {}
};

TreeNode* BuildTree(vector<int> &tree){
	TreeNode *root = NULL;
	if(tree.empty()) return root;
	root = new TreeNode(tree[0]);
	int i = 1;
	queue<TreeNode*> que;
	que.push(root);
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

vector<int> Solution(TreeNode *root){
	vector<int> ans;
	stack<TreeNode*> buf;
	if(root) buf.push(root);
	while(!buf.empty()){
		TreeNode *node = buf.top();
		buf.pop();
		ans.push_back(node->val);
		if(node->right) buf.push(node->right);
		if(node->left) buf.push(node->left);
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &v: tree)
		cin >> v;
	TreeNode *root = BuildTree(tree);
	vector<int> ans(Solution(root));
	for(auto &a: ans)
		cout << a << " ";
	cout << endl;
}
