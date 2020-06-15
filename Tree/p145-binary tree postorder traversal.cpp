/*
 * Recursion is trivial.
 *
 * Iterative method can be done by using a stack to simulate the recursion
 * For this series of problems (inorder/preorder/postorder),\ 
 * as long as the current node value should be put into the answer array,\ 
 * the node should be popped out from the stack\ 
 * since the rest of its usage is let us traverse its children\ 
 * but this is already done when the first time it becomes the top of the stack\ 
 * thus, there is nothing left for us to keep it
 *
 * Another concept is that, we should push child nodes into the stack in "reverse order" due to the FILO property of stack
 *
 * In order to avoid pushing the same child nodes twice when the second time of a node becomes stack.top()\ 
 * we can either set its child nodes to NULL or use a hash map to record whether they have been visited or not
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode (int _val): val(_val), left(NULL), right(NULL) {}
};

TreeNode* BuildTree(vector<int> &tree){
	TreeNode *root = NULL;
	if(tree.empty()) return root;
	root = new TreeNode(tree[0]);
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

vector<int> Solution(TreeNode *root){
	vector<int> ans;
	stack<TreeNode*> buf;
	if(root) buf.push(root);
	while(!buf.empty()){
		TreeNode *node = buf.top();
		if(node->right || node->left){		
			if(node->right){
				buf.push(node->right);
				node->right = NULL;
			}
			if(node->left){
				buf.push(node->left);
				node->left = NULL;
			}
		}else{
			ans.push_back(node->val);
			buf.pop();
		}
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	TreeNode *root = BuildTree(tree);
	vector<int> ans(Solution(root));
	for(auto &a: ans)
		cout << a << " ";
	cout << endl;
}
