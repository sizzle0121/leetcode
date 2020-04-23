/*
	**	use lower bound and upper bound to validate a node
		1. each node should be greater than lower bound && less than upper bound
		2. if so, we set new upper bound and go to validate left child
		3. then, we set new lower bound and go to validate right child
		the order of the above three step can be changed arbitrarily, because all we need is to travel through each node and check if it's in between its lower bound and upper bound
		However, it's necessary to set a infinite value to both bounds in the beginning, since the root is valid (no parents, no bounds)
		Time complexity: O(n)

	**	Inorder traversal:
		inorder traversal follows the sorted order to travel the tree, thus we can implement it and check if any node is greater than its next adjacent node. if no, the tree is valid
		Time complexity: O(n)
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* BuildTree(int *tree, int T){
	queue<TreeNode*> que;
	TreeNode *root = new TreeNode(tree[0]);
	que.push(root);
	int i=1;
	while(i < T){
		if(tree[i] != -1){
			TreeNode *tmp = new TreeNode(tree[i]);
			que.front()->left = tmp;
			que.push(tmp);
		}
		if(i+1 < T && tree[i+1] != -1){
			TreeNode *tmp = new TreeNode(tree[i+1]);
			que.front()->right = tmp;
			que.push(tmp);
		}
		que.pop();
		i += 2;
	}
	return root;
}
/*
bool isValidate(TreeNode *root, int low, int up){
	if(!root)	return true;
	if(up <= root->val || low >= root->val)	return false;
	if(!isValidate(root->left, low, root->val))	return false;
	if(!isValidate(root->right, root->val, up))	return false;
	return true;
}
*/

void inorder(TreeNode *root, vector<int> &nums){
	if(!root)	return;
	inorder(root->left, nums);
	nums.push_back(root->val);
	inorder(root->right, nums);
}

bool Solution(TreeNode *root){
	//return isValidate(root, -2147483647, 2147483647);
	vector<int> nums;
	inorder(root, nums);
	for(int i=0; i<nums.size(); i++){
		if(i+1 < nums.size() && nums[i] >= nums[i+1])
			return false;
	}
	return true;
}

int main(){
	int T;
	cin >> T;
	int tree[T];
	for(int i=0; i<T; i++)
		cin >> tree[i];
	TreeNode *root = BuildTree(tree, T);
	cout << Solution(root) << endl;
	return 0;
}
