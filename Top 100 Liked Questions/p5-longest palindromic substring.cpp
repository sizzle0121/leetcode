#include <iostream>
#include <string>

/*
1. iterate middle points, compare points mirror w.r.t the middle points
-> O(2n*n/2) = O(n^2)
*/

using namespace std;

void mirrorCmp(string &s, int &l, int &r){
	while(l >= 0 && r < s.length()){
		if(s[l] == s[r]){
			l -= 1;
			r += 1;
		}else{
			break;
		}
	}
	l += 1;
	r -= 1;
}


string Solution(string s){
	int max = 0, ansl = -1, ansr = -1;
	for(int i=0; i<s.length(); i++){
		int l = i, r = i;
		mirrorCmp(s, l, r);
		if(max < r-l+1){
			max = r-l+1;
			ansl = l;
			ansr = r;
		}			

		l = i;
		if(i+1 < s.length())	r = i + 1;
		else continue;
		mirrorCmp(s, l, r);
		if(max < r-l+1){
			max = r-l+1;
			ansl = l;
			ansr = r;
		}
	}

	string ans("");
	if(ansl >= 0 && ansr >= 0){
		for(int i=ansl; i<=ansr; i++)
			 ans.push_back(s[i]);
	}
	return ans;
}

int main(){
	string s;
	getline(cin, s);
	cout << Solution(s) << endl;
	return 0;
}
