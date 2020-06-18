/*
 * Inorder Traversal:
 * Using extra memory is trivial.
 * BST can be viewed as a sorted array if we traverse it by inorder traversal\ 
 * Therefore, we can record the count of a number until arr[i] != arr[i-1]\ 
 * then update the answer if the count >= maximum_count\ 
 * After that, set the count to 1 and continue to traverse the tree by inorder traversal
 *
 * For this problem, we should put emphasis on handling the edge cases
 *
 * Time complexity: O(n)
 * Space complexity: O(1), the answer array and the stack of recursion do not be counted as extra memory
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int _val): val(_val), left(NULL), right(NULL) {}
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

void inorder(TreeNode *node, int &cnt, int &maxi, int &prev, vector<int> &ans){
	if(!node) return;
	
	inorder(node->left, cnt, maxi, prev, ans);
	if(maxi == INT_MIN || prev != node->val){
		if(cnt > maxi){
			ans.clear();
			if(maxi == INT_MIN) ans.push_back(node->val);
			else ans.push_back(prev);
			maxi = cnt;
		}else if(cnt == maxi){
			if(prev != ans.back()) ans.push_back(prev);
		}
		cnt = 1;
		prev = node->val;
	}else if(prev == node->val){
		cnt++;
	}
	inorder(node->right, cnt, maxi, prev, ans);
}

vector<int> Solution(TreeNode *root){
	if(!root) return vector<int>();
	vector<int> ans;
	int cnt = 1, maxi = INT_MIN, prev = -1;
	inorder(root, cnt, maxi, prev, ans);
	if(cnt > maxi){
		ans.clear();
		ans.push_back(prev);
	}else if(cnt == maxi){
		if(prev != ans.back()) ans.push_back(prev);
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	vector<int> ans = Solution(BuildTree(tree));
	for(auto &a: ans)
		cout << a << " ";
	cout << endl;
}
