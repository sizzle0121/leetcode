/*
	DFS + Divide and Conquer:
	For a node, if we rob it, the maximum amount we can get is\ 
	node->val
	+ maximum amount of the left subtree (without robbing the direct left child)
 	+ maximum amount of the right subtree (without robbing the direct right child)

	If we choose not to rob the node, the maximum amount we can get is\ 
	maximum amount of the left subtree (with or wihtout robbing the direct left child)
	+ 
	maximum amount of the right subtree (with or wihtout robbing the direct right child)

	By DFS and determine the above "to rob or not to rob the current node" to get the maximum amount til the current node,
	we can finally get the answer of the root

	The first value of the pair in the following code represents choosing to rob the current node
	The second value of the pair in the following code represents choosing not to rob the current node
	
	Time complexity: O(n), since we just go through all the nodes once
*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int _val): val(_val), left(NULL), right(NULL) {}
};

TreeNode* BuildTree(vector<int> &tree){
	if(tree.empty())	return NULL;
	queue<TreeNode*> que;
	TreeNode *root = new TreeNode(tree[0]);
	que.push(root);
	int i = 1;
	while(i < tree.size()){
		if(tree[i] != -1){
			que.front()->left = new TreeNode(tree[i]);
			que.push(que.front()->left);
		}
		if(i+1 < tree.size() && tree[i+1] != -1){
			que.front()->right = new TreeNode(tree[i+1]);
			que.push(que.front()->right);
		}
		i += 2;
		que.pop();
	}
	return root;
}

pair<int,int> DFS(TreeNode *node){
	if(!node) return pair<int,int>(0, 0);
	pair<int,int> p = make_pair(node->val, 0);
	pair<int,int> L = DFS(node->left);
	pair<int,int> R = DFS(node->right);
	p.first += L.second + R.second;
	p.second += max(L.first, L.second) + max(R.first, R.second);
	return p;
}

int Solution(TreeNode *root){
	pair<int,int> p = DFS(root);//maximum; p.first: choose itself, p.second: not choose itself
	return max(p.first, p.second);
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(int i=0; i<T; i++)
		cin >> tree[i];
	TreeNode *root = BuildTree(tree);
	cout << Solution(root) << endl;
}
