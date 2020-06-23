/*
 * BFS:
 * Simply do BFS, push all children nodes in the same level into the queue and the same index of the answer vector\ 
 * then go to the next level and repeat the same things
 *
 * Time complexity: O(n)
 * Space complexity: O(k), k: the maximum number of nodes in the same level
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node{
	int val;
	vector<Node*> children;
	Node(int _val): val(_val) {}
};

Node* BuildTree(vector<int> &tree){
	if(tree.empty()) return NULL;
	Node *root = new Node(tree[0]);
	queue<Node*> que;
	que.push(root);
	int i = 2;
	while(i < tree.size()){
		Node *node = que.front();
		que.pop();
		while(i < tree.size() && tree[i] != -1){
			Node *child = new Node(tree[i]);
			node->children.push_back(child);
			que.push(child);
			i++;
		}
		i++;
	}
	return root;
}

vector<vector<int> > Solution(Node *root){
	vector<vector<int> > ans;
	if(!root) return ans;
	queue<Node*> que;
	que.push(root);
	ans.push_back(vector<int>{root->val});
	while(!que.empty()){
		vector<int> tmp;
		int n = que.size();
		for(int i=0; i<n; ++i){
			Node *node = que.front();
			que.pop();
			for(int j=0; j<node->children.size(); ++j){
				que.push(node->children[j]);
				tmp.push_back(node->children[j]->val);
			}
		}
		if(!tmp.empty()) ans.push_back(tmp);
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> tree(T);
	for(auto &t: tree)
		cin >> t;
	vector<vector<int> > ans(Solution(BuildTree(tree)));
	for(int i=0; i<ans.size(); ++i){
		for(int j=0; j<ans[i].size(); ++j)
			cout << ans[i][j] << " ";
		cout << endl;
	}
}
