/*
 * Heap:
 * Obviously, we need to pick at least one number from each list, and then calculate the range
 * Start from picking all leftmost number of all lists\ 
 * The range will be max - min, then pop out the smallest one\ 
 * since the smallest range using it as the left bound is composed of all the leftmost numbers\ 
 * If we add any righthand side number, the range will be larger, which is impossible to become the smallest range\ 
 * 
 * Then we add the next number of the list being popped, and get a new range
 * Similarly, the new range is new max - new min\ 
 * then, we need to pop out the smallest number, and add the next number of the list again to look up the next possible smallest range
 *
 * By repeating so, we can look through all possible smallest ranges and find the smallest one
 *
 * Time complexity: O(nlogk), n: the length of the first terminated list
 * Space complexity: O(k)
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

struct cmp{
	bool operator()(const pair<int,int> &a, const pair<int,int> &b){
		return a.first > b.first;
	}
};

vector<int> Solution(vector<vector<int> > &nums){
	int k = nums.size();
	vector<int> idx(k);
	vector<int> ans{-111111, 111111};
	priority_queue<pair<int,int>, vector<pair<int,int> >, cmp> pq;
	int r = -111111;
	for(int i=0; i<k; ++i){
		pq.push(pair<int,int>(nums[i][idx[i]], i));
		r = max(nums[i][idx[i]], r);
	}
	while(1){
		int l = pq.top().first, i = pq.top().second;
		pq.pop();
		if(r - l < ans[1] - ans[0]){
			ans[0] = l;
			ans[1] = r;
		}
		idx[i]++;
		if(idx[i] >= nums[i].size()) break;
		pq.push(pair<int,int>(nums[i][idx[i]], i));
		r = max(nums[i][idx[i]], r);
	}
	return ans;
}

int main(){
	int k;
	cin >> k;
	vector<vector<int> > nums(k);
	for(int i=0; i<k; ++i){
		int T;
		cin >> T;
		for(int j=0; j<T; ++j){
			int tmp;
			cin >> tmp;
			nums[i].push_back(tmp);
		}
	}
	vector<int> ans = Solution(nums);
	cout << ans[0] << " " << ans[1] << endl;
}
