/*
 * Backtrack:
 * For each digit, we can either light it up or light it off
 * I use the digit >= 6 as hour digit, and < 6 as minute digit
 * For minute digit, if adding the current digit to minute will greater than 59, we can only light it off
 * Similarly, for hour digit, if adding the current digit to hour will greater than 11, we can only light off
 * If the current digit is already > 9 and the num has not been used up yet, then we should just return (no need to continue)
 * By these rules, explore all possibles and push them into our answer if num is used up
 *
 * O(9!/(n!(9-n)!))
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

void backtrack(int num, vector<string> &ans, int hour, int minute, int digit){
	if(num == 0){
		stringstream ss;
		ss << hour;
		ss << ":";
		if(minute < 10)	ss << "0";
		ss << minute;
		ans.push_back(ss.str());
		return;
	}else if(digit > 9){
		return;
	}
	
	if(digit < 6){
		if(minute + (1<<digit) < 60){
			minute += (1<<digit);
			backtrack(num-1, ans, hour, minute, digit+1);
			minute -= (1<<digit);
		}
		backtrack(num, ans, hour, minute, digit+1);
	}else{
		if(hour + (1<<(digit-6)) < 12){
			hour += (1<<(digit-6));
			backtrack(num-1, ans, hour, minute, digit+1);
			hour -= (1<<(digit-6));
		}
		backtrack(num, ans, hour, minute, digit+1);
	}
}

vector<string> Solution(int num){
	vector<string> ans;
	backtrack(num, ans, 0, 0, 0);
	return ans;
}

int main(){
	int num;
	cin >> num;
	vector<string> ans = Solution(num);
	for(auto &t: ans)
		cout << t << " ";
	cout << endl;
}
