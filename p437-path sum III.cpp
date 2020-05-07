/*
	DFS:
	Traverse the tree, for each node, return a vector containing all the possible sum from the subtree
	If the node itself, and the sum of the node itself and all possibles from the subtree match the target, ans++
	Then push them all into a vector and return to its parent

	Time complexity: O(n), go throught all the nodes once


	Prefix + hash: 
	Store all prefix into a hash table, the value of the hash[prefix] is the count of the presence of the prefix
	For each node, add it to the current sum, named curSum
	We need to find the prefix s.t. curSum - prefix = target (which means there is a segment of the tree sums to the target)
	Thus, we find if (curSum-target) exists in the hash table, if so, then ans += its count
	Then insert curSum into the hash table and go to the child node
	Initialize prefix[0] = 1, since we automatically have the prefix 0

	Time complexity: O(n), go through all the nodes once
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int _val): val(_val), left(NULL), right(NULL){}
};

TreeNode* BuildTree(vector<int> &tree){
	if(tree.empty())	return NULL;
	queue<TreeNode*> que;
	TreeNode *root = new TreeNode(tree[0]);
	que.push(root);
	int i = 1;
	while(i < tree.size()){
		if(tree[i] != -123){
			que.front()->left = new TreeNode(tree[i]);
			que.push(que.front()->left);
		}
		if(i+1 < tree.size() && tree[i+1] != -123){
			que.front()->right = new TreeNode(tree[i+1]);
			que.push(que.front()->right);
		}
		que.pop();
		i += 2;
	}
	return root;
}

vector<int> DFS(TreeNode *node, int target, int &ans){
	vector<int> l, r, cur;
	if(node->left)	l = DFS(node->left, target, ans);
	if(node->right)	r = DFS(node->right, target, ans);
	if(node->val == target)	ans++;
	cur.push_back(node->val);
	for(int i=0; i<l.size(); i++){
		if(l[i] + node->val == target)	ans++;
		cur.push_back(l[i]+node->val);
	}
	for(int i=0; i<r.size(); i++){
		if(r[i] + node->val == target)	ans++;
		cur.push_back(r[i]+node->val);
	}
	return cur;
}

int Solution(TreeNode *root, int sum){
	if(!root)	return 0;
	int ans = 0;
	DFS(root, sum, ans);	
	return ans;
}

void DFS(TreeNode *node, int target, int &ans, unordered_map<int,int> &prefix, int curSum){
	curSum += node->val;
	if(prefix.find(curSum-target) != prefix.end())	ans += prefix[curSum-target];
	prefix[curSum]++;
	if(node->left)	DFS(node->left, target, ans, prefix, curSum);
	if(node->right)	DFS(node->right, target, ans, prefix, curSum);
	prefix[curSum]--;
	return;
}

int Solution2(TreeNode *root, int sum){
	if(!root)	return 0;
	int ans = 0;
	unordered_map<int,int> prefix;
	prefix[0] = 0;
	DFS(root, sum, ans, prefix, 0);
	return ans;
}


int main(){
	int T, sum;
	cin >> T;
	vector<int> tree(T);
	for(int i=0; i<T; i++)
		cin >> tree[i];
	cin >> sum;
	TreeNode *root = BuildTree(tree);
	cout << Solution2(root, sum) << endl;
}
