/*
 * Simulate manual addition operation:
 * Starting from the back (unit digit), add the digits and store the carry for the next round
 * In the end, return the reverse order of the answer string
 * (Solution2 is the more concise version, check it)
 *
 * Time complexity: O(max(n, m) + 1)
 *
 * */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string Solution2(string a, string b){
	int i = a.length()-1, j = b.length()-1, c = 0;
	string ans = "";
	while(i >= 0 || j >= 0 || c != 0){
		c += (i >= 0)? (a[i--]-'0') : 0;
		c += (j >= 0)? (b[j--]-'0') : 0;
		ans += (char)('0'+c%2);
		c /= 2;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

string Solution(string a, string b){
	int i = a.length()-1, j = b.length()-1, c = 0;
	string ans = "";
	while(i >= 0 && j >= 0){
		int n = (a[i--]-'0') + (b[j--]-'0') + c;
		c = n/2;
		ans += (char)('0'+n%2);
	}
	while(i >= 0){
		int n = (a[i--]-'0') + c;
		c = n/2;
		ans += (char)('0'+n%2);
	}
	while(j >= 0){
		int n = (b[j--]-'0') + c;
		c = n/2;
		ans += (char)('0'+n%2);
	}
	if(c != 0)	ans += (char)('0'+c);
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(){
	string a,b;
	getline(cin, a);
	getline(cin, b);
	string ans = Solution(a, b);
	cout << ans << endl;
	string ans2 = Solution2(a, b);
	cout << ans2 << endl;
}
