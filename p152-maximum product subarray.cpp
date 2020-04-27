/*
	DP:
	SubarrayProduct[L ... R] = prefix[R] / prefix[L-1], where prefix[L-1] != 0
	Main idea:
	Everytime we calculate the prefix(i), we divide it with the maximum Negative prefix or minimum Positive prefix in [0...i-1], then compare to the answer value
	If we meet zero, we view the rest of the array as a new array, and do the above things (remember to compare the answer to zero in the end)
	
	Time complexity: O(n)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<int> &nums){
	int prefix = 1, maxNeg = 1, minPos = -1;
	int ans = nums[0];
	bool hasZero = false;
	for(int i=0; i<nums.size(); i++){
		prefix *= nums[i];
		if(prefix > 0){
			if(minPos < 0){
				minPos = prefix;
				ans = max(ans, prefix);
			}else{
				int tmp = max(prefix, prefix/minPos);
				ans = max(ans, tmp);
				minPos = min(prefix, minPos);
			}
		}else if(prefix < 0){
			if(maxNeg > 0){
				maxNeg = prefix;				
			}else{
				ans = max(ans, prefix/maxNeg);
				maxNeg = max(prefix, maxNeg);
			}
		}else{
			hasZero = true;
			prefix = 1;
			maxNeg = 1;
			minPos = -1;
		}
	}
	if(hasZero)	return max(ans, 0);
	else	return ans;
	
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cout << Solution(nums) << endl;
}
