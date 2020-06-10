/*
 * Sliding Window (optimal):
 * Why?
 * 1. The problem asks for subarray not subsequence
 * 2. There are conditions for the contents of the subarray
 *
 * Extending the window:
 * Here, the condition is "the sum should >= s"
 * Thus, we extend the window until the contents satisfy the condition
 *
 * Update the answer:
 * Once the sum >= s, we should minimize the current window size\ 
 * since we only need the minimum size and compare it to the answer (previous minimum size we've found)
 * Also, since we scan from left to right, the only possible way to minimize the window is move the left bound to right, until sum - nums[l] < s
 *
 * Maintain the window:
 * After updating the answer, we can discard the nums[l] by l++
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * 
 * Find Prefix (Solution2, not optimal but another way of thinking):
 * For the sum of subarray[j...i] = prefix_sum[i] - prefix_sum[j-1]
 * Therefore, for each prefix_sum[i], we are looking for the rightmost prefix_sum[j] which <= prefix_sum[i] - s
 * and update the answer by comparing it with i-(j+1)+1
 * Why j+1?
 * Since prefix_sum[i] - prefix_sum[j] is the sum of the subarray [j+1 to i]
 *
 * In other words, we are looking for the index of the first prefix_sum that is > prefix_sum[i] - s
 * Thus, here we can use upper_bound to find it O(logn)
 *
 * Time complexity: O(nlogn)
 * Space complexity: O(n)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(int s, vector<int> &nums){
	int N = nums.size();
	if(N == 0) return 0;
	int l = 0, r = 0, sum = 0, ans = -1;
	while(r < N){
		if(sum < s){
			sum += nums[r];
		}

		if(sum >= s){
			while(sum - nums[l] >= s){
				sum -= nums[l];
				l++;
			}
			if(ans == -1) ans = r-l+1;
			else ans = min(ans, r-l+1);
			sum -= nums[l];
			l++;
		}
		r++;
	}
	return (ans == -1)? 0 : ans;
}

int Solution2(int s, vector<int> &nums){
	int N = nums.size();
	if(N == 0) return 0;
	vector<int> prefix_sum(N);
	prefix_sum[0] = nums[0];
	for(int i=1; i<N; ++i)
		prefix_sum[i] = nums[i] + prefix_sum[i-1];
	int ans = -1;
	for(int i=0; i<N; ++i){
		if(prefix_sum[i] >= s){
			int j = upper_bound(prefix_sum.begin(), prefix_sum.end(), prefix_sum[i] - s) - prefix_sum.begin();
			if(i-j >= 0){	
				if(ans == -1) ans = i-j+1;
				else ans = min(ans, i-j+1);
			}
		}
	}
	return (ans == -1)? 0 : ans;
}

int main(){
	int T, s;
	cin >> s >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	cout << Solution(s, nums) << endl;
	cout << Solution2(s, nums) << endl;
}
