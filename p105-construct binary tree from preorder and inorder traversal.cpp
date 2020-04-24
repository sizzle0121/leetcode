/*
	Divide and Conquer:
	The first node of preorder is the root, and we can use it to divide the inorder array into left and right subtrees
	After that, we can calculate the number of nodes in the left and right subtrees repectively, and then we can also divide the righthand side of the preorder array into two subtrees, the first numbers in both subarray of preorder are also root

	Repeat the above steps until we only have one node left (iHead == iEnd)

	Time complexity: O(n^2)

*/

#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <utility>

using namespace std;

struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x): val(x), left(NULL), right(NULL) {}
}
;
/*	==TLE==
void DFS(TreeNode *node, vector<int> &preorder, vector<int> &inorder, map<int, pair<int,int> > &pos, int low, int up){
	for(int i=pos[node->val].first+1; i<preorder.size(); i++){
		if(pos[preorder[i]].second > low && pos[preorder[i]].second < pos[node->val].second){
			node->left = new TreeNode(preorder[i]);
			DFS(node->left, preorder, inorder, pos, low, pos[node->val].second);
			break;
		}
	}
	for(int i=pos[node->val].first+1; i<preorder.size(); i++){
		if(pos[preorder[i]].second < up && pos[preorder[i]].second > pos[node->val].second){
			node->right = new TreeNode(preorder[i]);
			DFS(node->right, preorder, inorder, pos, pos[node->val].second, up);
			break;
		}
	}
}
void Solution(vector<int> &preorder, vector<int> &inorder){
	if(preorder.empty())	return;
	map<int,pair<int,int> > pos;
	for(int i=0; i<preorder.size(); i++){
		pos[preorder[i]].first = i;
		pos[inorder[i]].second = i;
	}
	TreeNode *root = new TreeNode(preorder[0]);	
	DFS(root, preorder, inorder, pos, -1, preorder.size());
	
	queue<TreeNode*> que;
	que.push(root);
	while(!que.empty()){
		for(int i=0, n=que.size(); i<n; i++){
			if(!que.front())	cout << -1 << " ";
			else{
				cout << que.front()->val << " ";
				que.push(que.front()->left);
				que.push(que.front()->right);
			}
			que.pop();
		}
		cout << endl;
	}
}
*/

TreeNode* DC(vector<int> &preorder, vector<int> &inorder, int pHead, int iHead, int iEnd){
	if(pHead >= preorder.size() || iHead >= inorder.size() || iEnd < 0 || iEnd < iHead)	return NULL;
	TreeNode *node = new TreeNode(preorder[pHead]);
	if(iHead == iEnd)	return node;
	int pos;
	for(int i=iHead; i<=iEnd; i++){
		if(node->val == inorder[i]){
			pos = i;
			break;
		}
	}
	node->left = DC(preorder, inorder, pHead+1, iHead, pos-1);
	node->right = DC(preorder, inorder, pHead+pos-iHead+1, pos+1, iEnd);
	return node;
}

void Solution(vector<int> &preorder, vector<int> &inorder){
	TreeNode *root = DC(preorder, inorder, 0, 0, inorder.size()-1);

	queue<TreeNode*> que;
	que.push(root);
	while(!que.empty()){
		for(int i=0, n=que.size(); i<n; i++){
			if(!que.front())	cout << "# ";
			else{
				cout << que.front()->val << " ";
				que.push(que.front()->left);
				que.push(que.front()->right);
			}
			que.pop();
		}
		cout << endl;
	}
}


int main(){
	int T;
	cin >> T;
	vector<int> preorder(T);
	vector<int> inorder(T);
	for(int i=0; i<T; i++)
		cin >> preorder[i];
	for(int i=0; i<T; i++)
		cin >> inorder[i];
	Solution(preorder, inorder);
	return 0;
}
