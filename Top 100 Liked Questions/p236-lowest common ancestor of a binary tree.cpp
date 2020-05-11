/*
	Use DFS to find the nodes (p and q)
	Once we found the node, we push it into the vector used to store all the ancestors of it, since the node itself is also its ancestor
	When the boolean value of the DFS is true, it represents that we are able to find our target node from this node down to the subtree, that is, this node is one of the ancestor of the target node; therefore, we should push it into the vector as well
	By doing so, we will obtain two vectors containing the ancestors of both target node
	Now, we can simply search for the first common node from left to right (equals to looking for common ancestor from the bottom to the root) in the vectors

	Time complexity: O(2n + (logn)^2) = O(n)
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int _val):val(_val), left(NULL), right(NULL){}
};

TreeNode* BuildTree(vector<int> &tree){
	if(tree.empty())	return NULL;
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

bool DFS(TreeNode *node, int target, vector<TreeNode*> &ancestor){
	if(!node) return false;
	if(node->val == target){
		ancestor.push_back(node);
		return true;
	}
	if(DFS(node->left, target, ancestor)){
		ancestor.push_back(node);
		return true;
	}else if(DFS(node->right, target, ancestor)){
		ancestor.push_back(node);
		return true;
	}
	return false;
}

TreeNode* Solution(TreeNode *root, TreeNode *p, TreeNode *q){
	if(!root)	return NULL;
	vector<TreeNode*> ap;
	vector<TreeNode*> aq;
	DFS(root, p->val, ap);
	DFS(root, q->val, aq);
	TreeNode *ans = NULL;
	for(int i=0; i<ap.size() && !ans; i++)
		for(int j=0; j<aq.size(); j++)
			if(ap[i]->val == aq[j]->val){
				ans = ap[i];
				break;
			}
	return ans;
}

int main(){
	int T, P, Q;
	cin >> T;
	vector<int> tree(T);
	for(int i=0; i<T; i++)
		cin >> tree[i];
	cin >> P >> Q;
	TreeNode *p = new TreeNode(P);
	TreeNode *q = new TreeNode(Q);
	TreeNode *root = BuildTree(tree);
	cout << Solution(root, p, q)->val << endl;
}
