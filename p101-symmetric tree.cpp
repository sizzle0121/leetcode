/*
	The main idea is to compare corresponding nodes in each side of the subtrees.
	Even if the string derived from DFS is palindromic, we still cannot guarantee it's symmetric, since the mirror position of the string is not the mirror position of the tree

	Therefore, we should directly travel the mirror positions and compare them.
	We still can use DFS, use inorder traversal(left, mid, right), and (right, mid, left)
	travel the tree twice, and compare both generated strings

	Another better solution is to use two pointers, traveling mirror positions and directly compare them

	Time complexity: O(n)
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* BuildTree(vector<int> &tree){
	if(tree.empty())	return NULL;
	queue<TreeNode*> que;
	TreeNode *root = new TreeNode(tree[0]);
	que.push(root);
	int i=1;
	while(i < tree.size()){
		if(tree[i] != -1){
			que.front()->left = new TreeNode(tree[i]);
			que.push(que.front()->left);
		}
		if(i+1 < tree.size() && tree[i+1] != -1){
			que.front()->right = new TreeNode(tree[i+1]);
			que.push(que.front()->right);
		}
		que.pop();
		i += 2;
	}
	return root;
}

bool mirrorTravel(TreeNode *lptr, TreeNode *rptr){
	if(!lptr && !rptr)	return true;
	if(!lptr || !rptr)	return false;
	return (lptr->val == rptr->val) && mirrorTravel(lptr->left, rptr->right) && mirrorTravel(lptr->right, rptr->left);
}

bool Solution(TreeNode *root){
	return mirrorTravel(root, root);
}

int main(){
	int T, tmp;
	cin >> T;
	vector<int> tree;
	for(int i=0; i<T; i++){
		cin >> tmp;
		tree.push_back(tmp);
	}
	TreeNode *root = BuildTree(tree);
	cout << Solution(root) << endl;
	return 0;
}
