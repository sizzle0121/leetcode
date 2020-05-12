/*
 * Simulate manual addition operation
 * Have done this many times...
 *
 * Time complexity: O(max_length(num1, num2))
 *
 * */
#include <iostream>
#include <string>
using namespace std;

string Solution(string num1, string num2){
	string ans = "";
	int i = num1.length()-1, j = num2.length()-1, c = 0;
	while(i >= 0 || j >= 0 || c != 0){
		c += (i >= 0)? (num1[i--]-'0') : 0;
		c += (j >= 0)? (num2[j--]-'0') : 0;
		ans += (char)('0'+c%10);
		c /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(){
	string num1, num2;
	getline(cin, num1);
	getline(cin, num2);
	cout << Solution(num1, num2) << endl;
}
