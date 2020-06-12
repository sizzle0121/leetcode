/*
 * Brute-force (TLE):
 * For each bar, look through the max area (should include the current bar) from i to 0\ 
 * then update the answer if the maximum > ans
 *
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 *
 *
 * Stack:
 * For each bar, the largest rectangle with its height will be\ 
 * heights[i] * (index of first righthand side height lower than it -  index of the first lefthand side height lower than it + 1)
 * And the answer will be the largest rectangle of all heights
 *
 * for the first lefthand side height lower than the current heights[i], we can use a stack to record
 * If stack.top() > the current heights[i], we should pop it out, since it will never become the left bound of the later heights
 * When we pop the stack.top() out, we should calculate the rectangle by it,\ 
 * since the current heights[i] is actually its right bound (the first righthand side bar that is lower than it)\ 
 * and the next top of the stack is its left bound
 *
 * By scanning through the heights and doing so, we can find the largest rectangle
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 *
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int Solution(vector<int> &heights){//TLE
	if(heights.empty()) return 0;
	int ans = 0;
	for(int i=0; i<heights.size(); ++i){
		int minh = heights[i], maxi = 0;
		for(int j=i; j>=0; --j){
			minh = min(minh, heights[j]);
			maxi = max(minh * (i-j+1), maxi);
		}
		ans = max(ans, maxi);
	}
	return ans;
}

int Solution2(vector<int> &heights){
	if(heights.empty()) return 0;
	stack<int> left;
	int ans = 0, N = heights.size();
	for(int i=0; i<N; ++i){
		while(!left.empty() && heights[left.top()] > heights[i]){
			int h = heights[left.top()];
			left.pop();
			int l = left.empty()? -1 : left.top();
			ans = max(ans, (i-l-1) * h);
		}
		left.push(i);
	}
	while(!left.empty()){
		int h = heights[left.top()];
		left.pop();
		int l = left.empty()? -1: left.top();
		ans = max(ans, (N-l-1) * h);
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> heights(T);
	for(auto &h: heights)
		cin >> h;
	cout << Solution(heights) << endl;
	cout << Solution2(heights) << endl;
}
