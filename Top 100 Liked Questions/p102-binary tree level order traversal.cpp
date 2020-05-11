/*
	BFS to do level order traversal
	Time complexity: O(n)
*/
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <utility>

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

void Solution(TreeNode *root){
	vector<vector<int> > ans;
	if(!root)	return;
	map<TreeNode*, int> nodeLev;
	queue<TreeNode*> que;
	nodeLev.insert(pair<TreeNode*, int>(root, 0));
	que.push(root);
	ans.push_back(vector<int>());
	int prevLev = 0;
	while(!que.empty()){
		if(nodeLev[que.front()] == prevLev){
			ans.back().push_back(que.front()->val);
		}else{
			prevLev = nodeLev[que.front()];
			ans.push_back(vector<int>());
			ans.back().push_back(que.front()->val);
		}
		if(que.front()->left){
			que.push(que.front()->left);
			nodeLev.insert(pair<TreeNode*, int>(que.front()->left, prevLev+1));
		}	
		if(que.front()->right){	
			que.push(que.front()->right);
			nodeLev.insert(pair<TreeNode*, int>(que.front()->right, prevLev+1));
		}
		que.pop();
	}

	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++)
			cout << ans[i][j] << ", ";
		cout << endl;
	}
}

//without using map
void Solution2(TreeNode* root){	
	vector<vector<int> > ans;
	if(!root)	return;
	queue<TreeNode*> que;
	que.push(root);
	while(!que.empty()){
		int N = que.size();
		ans.push_back(vector<int>());
		for(int i=0; i<N; i++){
			ans.back().push_back(que.front()->val);
			if(que.front()->left)	que.push(que.front()->left);
			if(que.front()->right)	que.push(que.front()->right);
			que.pop();
		}
	}

	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++)
			cout << ans[i][j] << ", ";
		cout << endl;
	}
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
	Solution(root);
	Solution2(root);
	return 0;
}
