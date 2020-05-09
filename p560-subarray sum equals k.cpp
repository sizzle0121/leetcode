/*
 * Prefix Sum:
 * The sum of subarray[i, j] = prefix_sum[j] - prefix_sum[i-1]
 * Use hash table to store the prefix_sum[i], for 0 <= i < nums.size()
 * the value of the table is the number of the presence of the prefix
 * For each i, we look up the table to find (prefix_sum[i] - k)
 * if exisits, ans += hashTable[ prefix_sum[i]-k ]
 * After scanning through the array, we will obtain the answer
 *
 * Time complexity: O(n)
 *
 * */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int Solution(vector<int> &nums, int k){
	if(nums.empty())	return 0;
	unordered_map<int,int> prefix;
	int ans = 0, sum = 0;
	prefix[0] = 1;
	for(int i=0; i<nums.size(); i++){
		sum += nums[i];
		if(prefix.find(sum-k) != prefix.end()){
			ans += prefix[sum-k];
		}
		if(prefix.find(sum) != prefix.end()){
			prefix[sum]++;
		}else{
			prefix[sum] = 1;
		}
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
	cout << Solution(nums, k) << endl;
}
