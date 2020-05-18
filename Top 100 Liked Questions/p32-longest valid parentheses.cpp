/*
 * Stack-Like Solution:
 * Record the left parentheses are matched or not\ 
 * Then find the longest continuous matched left parentheses
 * algo:
 * 		If s[i] == '(', put it into array and set the value to 0
 * 		If s[i] == ')', 
 * 			if valid (balance > 0), modify the rightmost 0 to 1 (match the rightmost left parenthesis)
 * 			if invalid (balance <= 0), put a -1 into the array to split the valid parentheses on both sides
 *		Seach for the longest continuous matched parentheses (longest '1' sequence)
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 *
 * 
 * DP (Solution2):
 * 1-step difference:
 * if a right parenthesis is valid, then current length of the valid parenthses will be\ 
 * the length of the previous valid parentheses + 2
 * 
 * Optimal substructure: 
 * Let dp[i] be the longest length of the valid parentheses ending at i
 * dp[i] = dp[i-2] + 2, if dp[i] == ')' and dp[i-1] == '('  for this case, s[i] must be valid 
 * dp[i] = dp[i-1] + dp[i - dp[i-1] - 2] + 2, if dp[i] == ')' and dp[i-1] == ')'
 * (if s[i - dp[i-1] - 1] == ')' or i - dp[i-1] - 2 < 0, then s[i] is an invalid right parenthesis)
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 *
 *
 * Optimal Solution (Solution3):
 * The longest valid parentheses must be closed (matched)\ 
 * That is, the left and right must be balanced (have equal number)
 * (the unmatched left parentheses will not be a part of the longest valid parentheses if they have not been matched in the end, and they will become invalid parentheses as well at that time)
 *
 * Also notice that for the longest valid parentheses, it will still be the longest if the string is reversed
 *
 * Therefore, we can record the current cumulated numbers of left and right parentheses\ 
 * If the numbers are equal -> closed -> update the answer if longer
 * After scan throught from left to right, we then scan through from right to left and repeat the same thing\ 
 * since some valid parentheses might not be counted due to the left parentheses are always more than the right and not be closed in the end 
 * By scanning from the right, we can early view them as invalid parentheses and count those valid parentheses
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int Solution(string s){
	int ans = 0, len = s.length();
	if(len < 2)	return 0;
	int balance = 0;
	vector<int> leftp;//-1: invalid, 0: unmatched left parenthesis, 1: matched left parenthesis
	for(int i=0; i<len; i++){//split by invalid parentheses, record matched/unmatched valid parentheses
		if(s[i] == ')'){
			if(balance > 0){//valid, matched
				balance--;
				int j = leftp.size()-1;
				while(leftp[j] != 0) j--;//the rightmost left parenthesis is matched
				leftp[j] = 1;
			}else{//invalid
				leftp.push_back(-1);
				balance = 0;
			}
		}else if(s[i] == '('){//valid, unmatched
			balance++;
			leftp.push_back(0);
		}
	}
	int N = leftp.size(), cnt = 0;
	for(int i=0; i<N; i++){//search for the longest continuous matched parentheses
		if(leftp[i] == 1) cnt++;
		else cnt = 0;
		ans = max(cnt, ans);
	}
	return ans*2;
}

int Solution2(string s){//DP
	int ans = 0, len = s.length();
	if(len < 2)	return 0;
	vector<int> dp(len);
	for(int i=1; i<len; i++){
		if(s[i] == ')'){
			if(s[i-1] == '(')
				dp[i] = (i-2 >= 0)? dp[i-2] + 2 : 2;
			else if(i-dp[i-1]-1 >= 0 && s[i - dp[i-1] - 1] == '('){
				dp[i] = dp[i-1] + 2;
				dp[i] += (i-dp[i-1]-2 >= 0)? dp[i - dp[i-1] - 2] : 0;
			}
			ans = max(ans, dp[i]);
		}
	}
	return ans;
}

int Solution3(string s){//optimal solution
	int ans = 0, len = s.length();
	if(len < 2)	return 0;
	int lp = 0, rp = 0;
	for(int i=0; i<len; i++){
		if(s[i] == '(') lp++;
		else if(s[i] == ')') rp++;
		if(rp > lp){
			lp = 0;
			rp = 0;
		}else if(lp == rp){
			ans = max(ans, lp+rp);
		}
	}
	lp = 0, rp = 0;
	for(int i=len-1; i>=0; --i){
		if(s[i] == '(') lp++;
		else if(s[i] == ')') rp++;
		if(lp > rp){
			lp = 0;
			rp = 0;
		}else if(lp == rp){
			ans = max(ans, lp+rp);
		}
	}
	return ans;
}

int main(){
	string s;
	getline(cin, s);
	cout << Solution(s) << endl;
	cout << Solution2(s) << endl;
	cout << Solution3(s) << endl;
}
