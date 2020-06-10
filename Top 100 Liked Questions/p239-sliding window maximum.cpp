/*
 * Map (Solution1):
 * Trivial.
 *
 * Time complexity: O(nlogn)
 * Space complexity: O(n)
 *
 *
 * Deque (Solution2, Optimal):
 * Main idea:
 * When a larger number shows up, the smaller number before it will never become the Max until it expires\ 
 * (expire: the window slide over it)
 * Therefore, we can discard those smaller numbers and keep the larger one
 * When a smaller number shows up , we should keep it, since when all the larger numbers in front of it expires, it may become the Max
 *
 * To sum up, we need a structure which is able to push and pop from the same side, and extract the Max from the other side -> deque
 *
 * In the deque, the numbers are in decreasing order, and the leftmost one has the earliest expried time
 * At position i, we put nums[i] to its appropiate position\ 
 * and if deque.front() == nums[i-k], pop it out (expired)
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 *
 * */
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

vector<int> Solution(vector<int> &nums, int k){
	map<int,int,greater<int> > window;
	int N = nums.size(), total = 0;
	vector<int> ans;
	for(int i=0; i<N; ++i){
		if(total < k){
			window[nums[i]]++;
			total++;
		}else{
			if(window[nums[i-k]] - 1 == 0) window.erase(nums[i-k]);
			else window[nums[i-k]]--;
			window[nums[i]]++;
		}

		if(total == k){
			ans.push_back(window.begin()->first);
		}
	}
	return ans;
}

vector<int> Solution2(vector<int> &nums, int k){
	int N = nums.size(), total = 0;
	vector<int> ans;
	deque<int> window;
	for(int i=0; i<N; ++i){
		
		while(!window.empty() && window.back() < nums[i]) window.pop_back();
		window.push_back(nums[i]);

		if(i+1 >= k){
			if(i-k >= 0 && nums[i-k] == window.front()) window.pop_front();
			ans.push_back(window.front());
		}
	}
	return ans;
}

int main(){
	int T, k;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	cin >> k;
	vector<int> output = Solution(nums, k);
	for(auto &opt: output)
		cout << opt << " ";
	cout << endl;

	output = Solution2(nums, k);
	for(auto &opt: output)
		cout << opt << " ";
	cout << endl;

}
