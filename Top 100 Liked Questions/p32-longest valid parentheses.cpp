#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int Solution(string s){
	int ans = 0, len = s.length();
	if(len < 2)	return 0;
	int balance = 0;
	vector<int> leftp;//-1: invalid, 0: unbounded left parenthesis, 1: bounded left parenthesis
	for(int i=0; i<len; i++){//split by invalid parentheses, record bounded/unbounded valid parentheses
		if(s[i] == ')'){
			if(balance > 0){//valid, bounded
				balance--;
				int j = leftp.size()-1;
				while(leftp[j] != 0) j--;
				leftp[j] = 1;
			}else{//invalid
				leftp.push_back(-1);
				balance = 0;
			}
		}else if(s[i] == '('){//valid, unbounded
			balance++;
			leftp.push_back(0);
		}
	}
	int N = leftp.size(), cnt = 0;
	for(int i=0; i<N; i++){//search for the longest continuous bounded parentheses
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
