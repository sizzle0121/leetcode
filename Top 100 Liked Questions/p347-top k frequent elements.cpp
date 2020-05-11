/*
	I think the restriction of this problem might be impossible

	HashMap + Max Heap:
	Use hash map to count the frequent of each element
	Then insert them into max heap, and pop out the first k element
	
	Time complexity: O(n + nlogn + k) = O(nlogn)

	HashMap + Sorting:
	Actually, this way runs faster than the above one
	After count the frequent for each element by using hash map
	We simply sort the map in decreasing order and pick the top k elements

	Time complexity: O(n + nlogn + k) = O(nlogn)

*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

struct cmp{
	bool operator() (const pair<int,int> &a, const pair<int,int> &b){
		return a.second < b.second;
	}
};
vector<int> Solution(vector<int> &nums, int k){
	unordered_map<int,int> hashTab;
	for(int i=0; i<nums.size(); i++){
		if(hashTab.find(nums[i]) != hashTab.end())
			hashTab[nums[i]]++;
		else
			hashTab.insert(pair<int,int>(nums[i], 0));
	}
	priority_queue<pair<int,int>, vector<pair<int,int> >, cmp> pq(hashTab.begin(), hashTab.end());
	//for(unordered_map<int,int>::iterator itr=hashTab.begin(); itr!=hashTab.end(); itr++){
	//	pair<int,int> p = make_pair(itr->first, itr->second);
	//	pq.push(p);
	//}
	vector<int> ans;
	for(int i=0; i<k; i++){
		ans.push_back(pq.top().first);
		pq.pop();
	}
	return ans;
}

int main(){
	int T, k;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cin >> k;
	vector<int> ans = Solution(nums, k);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
}
