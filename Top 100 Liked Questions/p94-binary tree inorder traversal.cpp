/*
	Recursive Solution is trivial

	Solve this with iterative solution:
	using stack to simulate recursive function, when visited all children, pop it
	visit left child first, if it exists and not visited yet, push it into stack and mark it as visited

	if already visited left child or it doesn't exist
		if right child has not yet been visited, push current node to answer
		if right child doesn't exist, current node will be popped out so we won't get back to it and push it to answer twice
		if right child exists and not yet been visited, push right child to stack and mark it as visited
	
	keep a hash table to record whether left and right children have been visited or not

	Time complexity: O(n)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* buildTree(int* tree, int T){
	if(!tree)	return 0;
	queue<TreeNode*> que;
	TreeNode *root = new TreeNode(tree[0]);
	que.push(root);
	int i = 1;
	while(i < T){
		if(tree[i] != -1){//represent null node as -1
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

void Solution(TreeNode *root){
	if(!root)	return;
	stack<TreeNode*> travel;
	map<TreeNode*, pair<bool,bool> > visited;
	vector<int> ans;
	travel.push(root);
	visited.insert(pair<TreeNode*,pair<bool,bool> >(root, pair<bool,bool>(false, false)));
	while(!travel.empty()){
		if(travel.top()->left && !visited[travel.top()].first){
			visited[travel.top()].first = true;
			visited.insert(pair<TreeNode*,pair<bool,bool> >(travel.top()->left, pair<bool,bool>(false, false)));
			travel.push(travel.top()->left);
		}else if(!travel.top()->left || visited[travel.top()].first){
			if(!visited[travel.top()].second){
				ans.push_back(travel.top()->val);
			}
			if(travel.top()->right && !visited[travel.top()].second){
				visited[travel.top()].second = true;
				visited.insert(pair<TreeNode*,pair<bool,bool> >(travel.top()->right, pair<bool,bool>(false, false)));
				travel.push(travel.top()->right);
			}else if(!travel.top()->right || visited[travel.top()].second){
				travel.pop();
			}
		}
	}

	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
}

int main(){
	int T;
	cin >> T;
	int tree[T];
	for(int i=0; i<T; i++)
		cin >> tree[i];
	TreeNode *root = buildTree(tree, T);
	Solution(root);
	return 0;
}
