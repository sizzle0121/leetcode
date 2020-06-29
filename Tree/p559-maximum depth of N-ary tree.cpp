/*
 * BFS:
 * Simply do BFS and count how many levels(depth) are there in the tree
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
	Node(int _val):val(_val){}
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
		while(tree[i] != -1){
			Node *tmp = new Node(tree[i]);
			node->children.push_back(tmp);
			que.push(tmp);
			i++;
		}
		i++;
	}
	return root;
}

int Solution(Node *root){
	if(!root) return 0;
	queue<Node*> que;
	que.push(root);
	int ans = 0;
	while(!que.empty()){
		ans++;
		int n = que.size();
		for(int i=0; i<n; ++i){
			Node *node = que.front();
			que.pop();
			for(auto &child: node->children){
				que.push(child);
			}
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
	cout << Solution(BuildTree(tree)) << endl;
}
