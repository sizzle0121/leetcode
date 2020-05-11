/*
	Prefix and Suffix Product:
	Use two arrays to store the prefix and suffix accumulated product to each position i repectively
	Then we can calculate the product of each element except itself by prefix[i-1] * suffix[i+1]
	
	Time complexity: O(n)
	Space complexity: O(n)
	This approach can be further improved by storing the prefix of 0 to i-1 in i, and then timing the suffix of N-1 to i+1 using a single variable (see solution3)
	->	Time complexity: O(n)
		Space complexity: O(1)


	Division:
	Calculate the product of all elements, and the product of each element except itself will be the total product divided by itself
	There are two special cases, the array including a zero element and the array including more than a zero element
	For case 1, we can solve it by assign zeros to all non-zero element and the product except zero to the zero element
	For case 2, all product except the element itself will be zero

	Time complexity: O(n)
	Space complexity: O(1)
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> Solution2(vector<int> &nums){
	int N = nums.size(), cnt = 0, product = 1;
	for(int i=0; i<N; i++){
		if(nums[i] == 0)	cnt++;
		if(cnt == 2)	break;
		if(nums[i] != 0)	product *= nums[i];
	}
	for(int i=0; i<N; i++){
		if(cnt == 2)	nums[i] = 0;
		else if(cnt == 1){
			if(nums[i] == 0)	nums[i] = product;
			else	nums[i] = 0;
		}else{
			nums[i] = product / nums[i];
		}
	}
	return nums;
}

vector<int> Solution3(vector<int> &nums){
	int N = nums.size();
	vector<int> ans(N);
	ans[0] = 1;
	for(int i=1; i<N; i++)
		ans[i] = nums[i-1] * ans[i-1];
	int suffix = 1;
	for(int i=N-1; i>=0; --i){
		ans[i] *= suffix;
		suffix *= nums[i];
	}
	return ans;
}

vector<int> Solution(vector<int> &nums){
	if(nums.empty())	return nums;
	int N = nums.size();
	vector<int> prefix(N);
	vector<int> suffix(N);
	for(int i=0; i<N; i++){
		if(i == 0)	prefix[i] = nums[i];
		else	prefix[i] = nums[i] * prefix[i-1];
	}
	for(int i=N-1; i>=0; --i){
		if(i == N-1)	suffix[i] = nums[i];
		else	suffix[i] = nums[i] * suffix[i+1];
	}
	for(int i=0; i<N; i++){
		nums[i] = 1;
		if(i-1 >= 0)	nums[i] *= prefix[i-1];
		if(i+1 < N)	nums[i] *= suffix[i+1];
	}
	return nums;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	vector<int> ans;
	//ans = Solution(nums);
	//ans = Solution2(nums);
	ans = Solution3(nums);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
}
