/*
	It's kinda obvious a DP problem.
	First, I thought of the one-step difference with substructures
	The new node can be add to every valid position of leaves, however, this way will be hard to identify duplicate structures
	Thus, I thought to add the new node on the top(root), and the subtrees will all be our former solutions.
	When the new node becomes the root, now we have n-1 nodes to put into our left and right subtrees; therefore, it can be (left: n-1, right: 0) or  (left: n-2, right: 1) ... to (left: 0, right: n-1)
	Eventually, we have the recursive solution with optimal substructures
		UniqueTree(n) = Sum( UniqueTree(k) * UniqueTree(n-1-k) ), with k from 0 to n-1

	Time complexity: O(n^2)

*/
#include <iostream>

using namespace std;

int Solution(int n){
	int unique_trees[n+1];
	unique_trees[0] = 1;
	unique_trees[1] = 1;
	for(int i=2; i<=n; i++){
		unique_trees[i] = 0;
		for(int j=0; j<=i-1; j++){
			unique_trees[i] += unique_trees[j]*unique_trees[i-1-j];
		}
	}
	return unique_trees[n];
}

int main(){
	int n;
	cin >> n;
	cout << Solution(n) << endl;
	return 0;
}
