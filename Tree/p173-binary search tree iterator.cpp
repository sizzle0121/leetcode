/*
 * Array (written in BSTIterator2):
 * This approach is trivial and intuitive.
 * Simply do inorder travrsal and store the result in an array
 *
 * Time complexity:
 * Constructor: O(n)
 * next(): O(1)
 * hasNext(): O(1)
 *
 * Space complexity: O(n)
 *
 *
 *
 * Stack (written in BSTIterator):
 * This approach is more fun.
 * Use a stack which the top of it is always the node going to be called by next() and popped out
 * Every time when we call next(), we update the stack to make its top becomes the next smallest nodes again
 *
 * As we mentioned in p145, we should push nodes in the reverse order of inorder traversal\ 
 * and set the current node's left and right pointer to NULL to avoid push its children twice
 * Therefore,
 * if both left and right == NULL, the node is ready to be returned
 * if either one of the left or right != NULL, the node should first push its children in inorder
 *
 * Time complexity: 
 * Constructor: O(n)
 * next(): O(n)
 * hasNext(): O(1)
 *
 * Space complexity: O(h), h: the height of the BST
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int _val): val(_val), left(NULL), right(NULL){}
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

class BSTIterator{
public:
	BSTIterator(TreeNode *root){
		TreeNode *node = root;
		if(node){
			buf.push(node);
			update();
		}
	}

	void update(){
		while(1){
			TreeNode *node = buf.top();
			buf.pop();
			if(!node->left && !node->right){
				buf.push(node);
				break;
			}
			if(node->right){
				buf.push(node->right);
				node->right = NULL;
			}
			buf.push(node);
			if(node->left){
				buf.push(node->left);
				node->left = NULL;
			}
		}
	}

	int next(){
		if(!hasNext()) return INT_MIN;
		int ans = buf.top()->val;
		buf.pop();	
		if(!buf.empty()) update();
		return ans;
	}

	bool hasNext(){
		return !buf.empty();
	}

private:
	stack<TreeNode*> buf;
};

class BSTIterator2{
public:
	BSTIterator2(TreeNode *root): idx(0){
		if(root) inorder(root);
	}

	void inorder(TreeNode *node){
		if(!node) return;
		inorder(node->left);
		nums.push_back(node->val);
		inorder(node->right);
	}

	int next(){
		if(!nums.empty() && idx < nums.size()){
			return nums[idx++];
		}
		return INT_MIN;
	}

	bool hasNext(){
		return (!nums.empty() && idx < nums.size());
	}
	
private:
	vector<int> nums;
	int idx;
};

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	TreeNode *root = BuildTree(tree);
	BSTIterator2 *itr = new BSTIterator2(root);
	cin.ignore();
	while(1){
		string s;
		getline(cin, s);
		if(s[0] == 'n') cout << itr->next() << endl;
		else if(s[0] == 'h') cout << itr->hasNext() << endl;
	}
}
