/*
 * Deque:
 * Simply use deque and traverse from left to right and from right to left level by level
 *
 * Time complexity: O(n)
 * Space complexity: O(2^(logn - 1) - 2^(logn - 2)), which is the maximum number of nodes in the last level
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
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

vector<vector<int> > Solution(TreeNode *root){
	vector<vector<int> > ans;
	if(!root) return ans;
	bool lr = false;//false: left to right, true: right to left
	deque<TreeNode*> dq;
	dq.push_front(root);
	while(!dq.empty()){
		int n = dq.size();
		ans.push_back(vector<int>());
		for(int i=0; i<n; ++i){
			if(lr){
				TreeNode *tmp = dq.back();
				dq.pop_back();
				ans.back().push_back(tmp->val);
				if(tmp->right) dq.push_front(tmp->right);
				if(tmp->left) dq.push_front(tmp->left);
			}else{
				TreeNode *tmp = dq.front();
				dq.pop_front();
				ans.back().push_back(tmp->val);
				if(tmp->left) dq.push_back(tmp->left);
				if(tmp->right) dq.push_back(tmp->right);
			}
		}
		lr = !lr;
	}
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
