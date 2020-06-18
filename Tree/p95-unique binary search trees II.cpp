/*
 * DP + Inorder Traversal:
 * DP like the way we do in p96-unique binary search trees\ 
 * but this time, we have to actually link the child nodes instead of just multiplying them for the numbers
 * After building the unique strutures for nth BST, then we start to assign values to each node in each kind of structure
 * This can be done by using inorder traversal and increasing the number of the values
 *
 * Notice that we have to create a copy of a node rather than just assign the value to a node\ 
 * since previously we only link the nodes and build up different structures\ 
 * not create a new set of nodes in different structures
 *
 * Time complexity: O(n*k + n*k) = O(n*k), k: the number of unique structures for BST with n nodes
 * Space complexity: O(n*k)
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int _val): val(_val), left(NULL), right(NULL) {}
};

TreeNode* inorder(TreeNode *node, int &cnt){
	if(!node) return NULL;
	TreeNode *newNode = new TreeNode(-1);
	newNode->left = inorder(node->left, cnt);
	newNode->val = cnt++;
	newNode->right = inorder(node->right, cnt);
	return newNode;
}

vector<TreeNode*> Solution(int n){
	if(n == 0) return vector<TreeNode*>();
	vector<vector<TreeNode*> > trees;
	trees.push_back(vector<TreeNode*>{NULL});
	TreeNode *a = new TreeNode(-1);
	trees.push_back(vector<TreeNode*>{a});
	for(int i=2; i<=n; ++i){//O(n*k)
		trees.push_back(vector<TreeNode*>());
		for(int j=i-1; j>=0; --j){//O(k)
			for(int l=0; l<trees[j].size(); ++l){
				for(int r=0; r<trees[i-1-j].size(); ++r){
					TreeNode *tmp = new TreeNode(-1);
					tmp->left = trees[j][l];
					tmp->right = trees[i-1-j][r];
					trees[i].push_back(tmp);
				}
			}
		}
	}
	for(int i=0; i<trees[n].size(); ++i){//O(n*k), k trees, every tree has n nodes
		int cnt = 1;
		TreeNode *newNode = inorder(trees[n][i], cnt);
		trees[n][i] = newNode;
	}
	return trees[n];
}

int main(){
	int n;
	cin >> n;
	vector<TreeNode*> ans(Solution(n));
	queue<TreeNode*> que;
	for(auto &root: ans){
		que.push(root);
		while(!que.empty()){
			int n = que.size();
			for(int i=0; i<n; ++i){
				if(que.front()){
					cout << que.front()->val << " ";
					que.push(que.front()->left);
					que.push(que.front()->right);
				}else cout << -1 << " ";
				que.pop();
			}
		}
		cout << endl;
	}
}
