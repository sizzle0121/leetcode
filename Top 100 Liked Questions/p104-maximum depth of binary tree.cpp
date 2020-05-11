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

void DFS(TreeNode *node, int lev, int &maxi){
	if(!node)	return;
	if(lev > maxi)	maxi = lev;
	DFS(node->left, lev+1, maxi);
	DFS(node->right, lev+1, maxi);
}

int Solution(TreeNode *root){
	int maxi = 0;
	DFS(root, 1, maxi);
	return maxi;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(int i=0; i<T; i++)
		cin >> tree[i];
	TreeNode *root = BuildTree(tree);
	cout << Solution(root) << endl;
	return 0;
}
