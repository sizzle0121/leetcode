/*
**	enumerate all and print the valid combs

**	backtrack and prune?

*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void enumerate(vector<string> &ans, int maxLen, int l, int r, int balance, string curStr){
	if(maxLen <= curStr.length()){
		ans.push_back(curStr);
		return;
	}
	if(l > 0)	enumerate(ans, maxLen, l-1, r, balance+1, curStr+'(');
	if(r > 0 && balance-1 >= 0)	enumerate(ans, maxLen, l, r-1, balance-1, curStr+')');
	return;
}


vector<string> Solution(int n){
	vector<string> ans;
	enumerate(ans, n*2, n, n, 0, "");
	return ans;
}

int main(){
	int n;
	cin >> n;
	
	vector<string> ans;
	ans = Solution(n);
	for(int i=0; i<ans.size(); i++){
		cout << ans[i] << endl;
	}
	if(!ans.size())
		cout << "" << endl;
	return 0;
}
