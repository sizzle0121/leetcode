/*
	The problem can be interpreted as\ 
	"determine if we can obtain a specific number by adding the numbers in the given array"
	since moving a number from group A to group B = total(group A) - num, total(group B) + num
	so the original difference of both groups will reduce 2*num
	thus, we can view the initial case as group A = all numbers in the array, group B is empty, we have to reduce the total sum of A
	-> adding the numbers from A to (total sum of A / 2)

	Changing making problem:
	First we count the number of coins, and sort the pair<type, count> by types
	Base case dp[0] = true, since we can add to zero by doing nothing
	Starting from the smallest coin $, we iterate all $+$, $+$+$, ..., $*n until > the target(total/2)
	if dp[$ * n] is false, we then set it to true, and count[$]-1
	if dp[$ * n] is already true, we then set the count[$] back to the original count[$]\ 
	since we can use it as the base to add to $*n + $
	In the end, dp[target] will be our answer

	If we know $*5 can be added to, but we have only 4 $, why we won't miss it in this way?
	ans: if it can be added to without 5 $, it must consist of other types of coins to make the other $, let's say A+B = the other $
	Therefore, even in the round of $, dp[5*$] is false (no enough count of $)
	but in the following rounds of A and B, we will update dp[$+A] to true, and then dp[$+A+B] to true, so we won't miss it

	Time complexity: O(k * (N/c)*c) = O(k * N), k: types of coins, N: the target number, c:the value of the smallest coin


	0/1 knapsack problem:
	Can a knapsack with {target} capacity be full?
	dp[i] is denoted as whether capacity i can be full by our objects
	Starting from the first object(no need to sort), if dp[i] is true, then it's true, if it's not, then we try the current object
	dp[i-object's weight] means if we put the object in, it will be full or not, since i - object's weight (+ object's weight(put it in)) = i, so dp[i] including the object will be equal to dp[i-object's weight]
	The optimal substructure: dp[i] = dp[i] || dp[i-object's weight]
	By starting from the max weight(target number) to 0, we can consider the number of each objects\ 
	(If we have two objects with weight 5, the first on will set dp[5] to true, the second one will set dp[5+5=10] to true)
	(Starting fomr 0 to max weight will reuse every object infinite times)

	Time complexity: O(n*N), n: number of coins(input size), N: the target number
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

bool Solution(vector<int> &nums){
	if(nums.empty() || nums.size() < 2)	return false;
	int N = nums.size();
	int cap = 0;
	map<int, int, less<int> > volume;//first: type of coins, second: its count
	for(int i=0; i<N; i++){
		cap += nums[i];
		if(volume.find(nums[i]) == volume.end())	volume[nums[i]] = 1;
		else	volume[nums[i]]++;
	}
	if(cap % 2 == 1)	return false;
	cap /= 2;
	map<int,int,less<int> >::iterator itr;
	vector<bool> dp(cap+1);
	dp[0] = true;
	for(itr=volume.begin(); itr != volume.end(); itr++){//for every kind of coins
		for(int i=0; i<itr->first; i++){//start from all of its remainder 0 to $-1
			if(dp[i]){//if the base is false, then we don't need to check (base + $*n)
				int cnt = itr->second;
				for(int j=(i+itr->first); j<=cap; j+=itr->first){//iterate base + $*n
					if(dp[j])	cnt = itr->second;//already true -> use it as new base, set count back to original count
					else if(cnt > 0){//if false, then we need to spend a coin to make it true
						cnt--;
						dp[j] = true;
					}
				}
			}
		}
	}
	return dp[cap];
}

bool Solution2(vector<int> &nums){
	if(nums.empty() || nums.size() < 2)	return false;
	int target = 0;
	for(int i=0; i<nums.size(); i++)
		target += nums[i];
	if(target % 2 == 1)	return false;
	target /= 2;
	vector<bool> dp(target+1);
	dp[0] = true;
	for(int i=0; i<nums.size(); i++){
		for(int j=target; j>=nums[i]; --j){
			dp[j] = dp[j] || dp[j-nums[i]];
		}
	}
	return dp[target];
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cout << Solution(nums) << endl;
	cout << Solution2(nums) << endl;
}
