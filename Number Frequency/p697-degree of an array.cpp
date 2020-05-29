/*
 * Hash Table (also can use vectors with sizeof(int*50000)):
 * One pass (Solution2)
 * Count all numbers and record their starting indices
 * If the number has not presented before, record the index and count+1
 * If the count > current max_count, update the degree and the answer
 * If the count == current max_count, update the answer if the range (i+1 - starting index) is smaller
 * 
 * Time complexity: O(n)
 * Space complexity: O(k), k is the number of different numbers
 *
 * */
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct cmp{
	bool operator()(const pair<int,pair<int,int> > &a, const pair<int,pair<int,int> > &b){
		return a.first > b.first;
	}
};

int Solution(vector<int> &nums){
	map<int,pair<int,pair<int,int> > > cnt;
	for(int i=0; i<nums.size(); i++){
		if(cnt.find(nums[i]) == cnt.end())
			cnt.insert(pair<int,pair<int,pair<int,int> > >(nums[i], pair<int,pair<int,int> >(0, pair<int,int>(i, i+1))));
		else{
			cnt[nums[i]].first++;
			cnt[nums[i]].second.second = i+1;
		}
	}
	vector<pair<int,pair<int,int> > > d;
	d.reserve(cnt.size());
	for(auto &c: cnt)
		d.push_back(c.second);
	sort(d.begin(), d.end(), cmp());
	int deg = -1, ans = 55555;
	for(auto &itr: d){
		if(deg == -1) deg = itr.first;
		else if(itr.first < deg) break;
		ans = min(ans, itr.second.second - itr.second.first);
	}
	return ans;
}

int Solution2(vector<int> &nums){
	unordered_map<int,int> cnt, left;
	int ans = 55555, deg = -1;
	for(int i=0; i<nums.size(); i++){
		if(cnt.find(nums[i]) == cnt.end()){
			cnt[nums[i]]++;
			left[nums[i]] = i;
			deg = max(deg, cnt[nums[i]]);
		}else{
			cnt[nums[i]]++;
			if(cnt[nums[i]] == deg){
				ans = min(ans, i+1 - left[nums[i]]);
			}else if(cnt[nums[i]] > deg){
				deg = cnt[nums[i]];
				ans = i+1 - left[nums[i]];
			}
		}
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	cout << Solution2(nums) << endl;
	cout << Solution(nums) << endl;
}
