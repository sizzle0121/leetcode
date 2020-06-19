/*
 * BFS:
 * Simply do BFS and store nodes level by level\ 
 * then reverse the answer array and return
 *
 * Time complexity: O(n)
 * Space complexity: O(2^(logn - 1) - 2^(logn - 2))
 *
 * DFS:
 * Simply do DFS(inorder traversal) and count the current level when enter the next level of recursion\ 
 * then push nodes into answer[i] which i is its corresponding level
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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

vector<vector<int> > Solution(TreeNode *root){
	vector<vector<int> > ans;
	if(!root) return ans;
	queue<TreeNode*> que;
	que.push(root);
	while(!que.empty()){
		int n = que.size();
		ans.push_back(vector<int>());
		for(int i=0; i<n; ++i){
			TreeNode *tmp = que.front();
			que.pop();
			ans.back().push_back(tmp->val);
			if(tmp->left) que.push(tmp->left);
			if(tmp->right) que.push(tmp->right);
		}
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	vector<vector<int> > ans(Solution(BuildTree(tree)));
	for(int i=0; i<ans.size(); ++i){
		for(int j=0; j<ans[i].size(); ++j)
			cout << ans[i][j] << " ";
		cout << endl;
	}
}
