/*
 * Simulate manual multiply operation: (no intermediate integer array)
 * Every round, fix a digit of num1, pad zeros, then multiply it with num2
 * Add the above result to the answer
 * By repeating so, we can obtain the reverse order of the product\ 
 * Reverse it and return
 *
 * Time complexity: O(n*(m + n+m)) = O(n^2 * m)
 * where n is the length of the first string, m is that of the other
 *
 *
 * Use intermidiate integer array:
 * Reverse both strings first, then we have the unit digit at position 0
 * For the product of digit i and digit j, it will be at digit i+j of the answer array
 * And the carry will be at i+j+1
 * We can calculate the product of each pair of digits and update the cumulated product[i+j]
 * At last, we only need to find the first non-zero digit from the right of the answer array\ 
 * and convert all integers to char
 * (we should leave a zero if all digits are zero)
 *	
 *	Time complexity: O(n*m)
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string add(string s1, string s2){
	int i = 0, j = 0, c = 0;
	string res = "";
	while(i < s1.length() && j < s2.length()){
		int n = (s1[i++]-'0') + (s2[j++]-'0') + c;
		c = n/10;
		res += (char)('0'+n%10);
	}
	while(i < s1.length()){
		int n = (s1[i++]-'0')+c;
		c = n/10;
		res += (char)('0'+n%10);
	}
	while(j < s2.length()){
		int n = (s2[j++]-'0')+c;
		c = n/10;
		res += (char)('0'+n%10);
	}
	if(c != 0)	res += (char)('0'+c);
	return res;
}

string Solution(string num1, string num2){
	if(num1 == "0" || num2 == "0")	return "0";
	string ans = "0";
	for(int i=num1.length()-1; i>=0; --i){
		if(num1[i] == '0')	continue;
		string tmp = "";
		int c = 0;
		for(int k=0; k<num1.length()-1-i; k++)	tmp += "0";
		for(int j=num2.length()-1; j>=0; --j){
			int n = (num2[j]-'0') * (num1[i]-'0') + c;
			c = n/10;
			tmp += (char)('0'+n%10);
		}
		if(c != 0)	tmp += (char)('0'+c);
		ans = add(ans, tmp);
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

string Solution2(string num1, string num2){
	if(num1.length() <= 0 || num2.length() <= 0)	return "";
	vector<int> ans(num1.length() + num2.length());
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	for(int i=0; i<num1.length(); i++){
		for(int j=0; j<num2.length(); j++){
			ans[i+j] += (num1[i]-'0') * (num2[j]-'0');
			ans[i+j+1] += ans[i+j]/10;
			ans[i+j] %= 10;
		}
	}
	int i=ans.size()-1;
	while(i > 0 && ans[i] == 0)	i--;
	string res="";
	while(i >= 0){
		res += (char)(ans[i]+'0');
		i--;
	}
	return res;
}

int main(){
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	string ans = Solution(s1, s2);
	cout << ans << endl;
	string ans2 = Solution2(s1, s2);
	cout << ans2 << endl;
}
