/*
 * Sliding Window:
 * Extending window:
 * The initial window (single number is already a valid window), no need to extend to valid window first
 * 
 * Maintain valid window:
 * If the sign (> or <) is different than the last one -> valid -> r++
 * If the sign is the same as the last one or is '=' -> invalid -> move l until valid\ 
 * for this problem, l should move to the left of the same > or < sign, or to the right of the '=' sign
 *
 * Update the answer anytime if current length is longer
 *
 * Time complexity: O(n)
 * Space Complexity: O(1)
 *
 *
 * DP (Solution2):
 * When we want to use DP to solve a "subarray problem", we should consider dp[i] as\ 
 * "the (length/sum depending on the problem) of a valid subarray ends at i"
 * Therefore, for this problem, dp[i] is the max length of a valid (different sign) subarray ends at i
 * 
 * The one step difference:
 * dp[i] = dp[i-1] + 1
 *
 * The optimal substructure:
 * dp[i] = dp[i-1] + 1 or 2 or 1, if valid, or same sign, or '='
 *
 * Time complexity: O(n)
 * Space complexity: O(1), can be O(1) if we implement it as "Maximum sum subarray"
 * (Here I implement dp as an array for easier understanding)
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

int Solution(vector<int> &A){
	int l =0, r = 0, ans = 1, flag = -1;//flag: -1(none), 0(>), 1(<)
	for(int i=0; i<A.size()-1; i++){
		if(A[i] < A[i+1] && (flag == 0 || flag == -1)){
			r++;
			flag = 1;
		}else if(A[i] > A[i+1] && (flag == 1 || flag == -1)){
			r++;
			flag = 0;
		}else{
			if(A[i] == A[i+1]){
				l = i+1;
				r = i+1;
				flag = -1;
			}else{
				l = i;
				r = i+1;
				if(A[i] < A[i+1]) flag = 1;
				else flag = 0;
			}
		}
		ans = max(ans, r-l+1);
	}
	return ans;
}

int Solution2(vector<int> &A){
	vector<int> dp(A.size(), 1);
	int ans = 1, flag = -1;
	for(int i=1; i<A.size(); i++){
		if(A[i] > A[i-1] && (flag == 1 || flag == -1)){
			dp[i] += dp[i-1];
			flag = 0;
		}else if(A[i] < A[i-1] && (flag == 0 || flag == -1)){
			dp[i] += dp[i-1];
			flag = 1;
		}else{
			if(A[i] == A[i-1]) flag = -1;
			else if(A[i] > A[i-1]){
				flag = 0;
				dp[i] = 2;
			}else{
				flag = 1;
				dp[i] = 2;
			}
		}
		ans = max(ans, dp[i]);
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> A(T);
	for(auto &a: A)
		cin >> a;
	cout << Solution2(A) << endl;
	cout << Solution(A) << endl;
}
