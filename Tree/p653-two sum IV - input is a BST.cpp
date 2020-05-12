/*
 * Two ways of thinking
 * 1. 	Traverse all nodes once and obtain the array of all numbers,\ 
 * 		then solve it as 2 sum
 * 2.	Utilize the structure of BST
 *
 * The first one is trivial, and I think if a HR test you with this problem, he/she won't like you to do so, since it's a little bit like memorizing the solution you've done before
 *
 * Thus, I try to utilize the structure of BST
 * First approach: DFS + Binary Search
 * Use DFS to traverse all the nodes, when visit to a node, do BST to check if its pair (k - node->val) exists in the tree
 *
 * Time complexity: O(nlogn)
 *
 *
 * Second approach: Inorder Traversal of BST + Two Pointers
 * I think this is the best way, since it not only utilize the BST, but also combines the solution we've done before
 * The inorder traversal of a BST is a sorted array
 * Therefore, we first do inorder traversal to get the array, then use two pointers to find whether the pair summing to k exists in the array as we've done before
 *
 * Time complexity: O(n)
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

TreeNode* BuildTree(vector<int> &tree){
	if(tree.empty())	return NULL;
	TreeNode *root = new TreeNode(tree[0]);
	queue<TreeNode*> que;
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

bool BST(TreeNode *cur, int target, TreeNode *self){
	if(target == cur->val && cur != self)	return true;
	else if(cur->right && target > cur->val)	return BST(cur->right, target, self);
	else if(cur->left && target < cur->val)	return BST(cur->left, target, self);
	return false;
}

bool Solution(TreeNode *root, int k, TreeNode *node){
	if(BST(root, k - node->val, node))	return true;		
	if(node->left && Solution(root, k, node->left))	return true;
	if(node->right && Solution(root, k, node->right))	return true;
	return false;
}

void inorder(TreeNode *node, vector<int> &sorted_nums){
	if(node->left)	inorder(node->left, sorted_nums);
	sorted_nums.push_back(node->val);
	if(node->right)	inorder(node->right, sorted_nums);
}

bool Solution2(TreeNode *root, int k){
	vector<int> sorted_nums;
	inorder(root, sorted_nums);
	int l = 0, r = sorted_nums.size()-1;
	while(l < r){
		if(sorted_nums[l] + sorted_nums[r] == k)	return true;
		else if(sorted_nums[l] + sorted_nums[r] < k)	l++;
		else	r--;
	}
	return false;
}

int main(){
	int T, k;
	cin >> T;
	vector<int> tree(T);
	for(int i=0; i<T; i++)
		cin >> tree[i];
	cin >> k;
	TreeNode *root = BuildTree(tree);
	cout << Solution(root, k, root) << endl;
	cout << Solution2(root, k) << endl;
}
