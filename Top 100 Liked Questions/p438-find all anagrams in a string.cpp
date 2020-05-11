#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<int> Solution(string s, string p){//sliding window with pruning
	if(s.length() <= 0)	return vector<int>();
	unordered_map<char, int> cnt;
	for(int i=0; i<p.length(); i++){
		if(cnt.find(p[i]) != cnt.end())
			cnt[p[i]]++;
		else
			cnt[p[i]] = 1;
	}
	vector<int> ans;
	unordered_map<char, int> cmpCnt;
	bool found;
	int curLen = 0;//current matched number of characters
	for(int start=0; start<s.length() && start+p.length()<=s.length(); start++){
		found = true;
		for(int i=start+curLen; i<start+p.length(); i++){
			if(cnt.find(s[i]) == cnt.end()){//characters not in p
				start = i;//jump to its next
				found = false;
				cmpCnt.clear();
				curLen = 0;
				break;
			}else{
				cmpCnt[s[i]]++;
				curLen++;
				if(cmpCnt[s[i]] > cnt[s[i]]){
					char target = s[i];
					while(s[start] != target){//move the starting point of the window
						cmpCnt[s[start]]--;//and reset the cmpCnt
						start++;
						curLen--;
					}
					cmpCnt[s[start]]--;
					curLen--;
					found = false;
					break;
				}
			}
		}
		if(found){
			ans.push_back(start);
			cmpCnt[s[start]]--;
			curLen--;
		}
	}
	return ans;
}

vector<int> Solution2(string s, string p){//two pointers (sliding window)
	if(s.length() <= 0)	return vector<int>();
	unordered_map<char, int> cnt;
	for(int i=0; i<p.length(); i++){
		if(cnt.find(p[i]) != cnt.end())	cnt[p[i]]++;
		else	cnt[p[i]] = 1;
	}
	int head = 0, tail = 0;
	int matchCnt = p.length();//total number of words should be matched
	vector<int> ans;
	while(tail < s.length()){
		if(cnt.find(s[tail]) != cnt.end()){
			cnt[s[tail]]--;
			if(cnt[s[tail]] >= 0){
				matchCnt--;
			}
		}
		tail++;
		while(matchCnt == 0){
			if(cnt.find(s[head]) != cnt.end()){
				cnt[s[head]]++;
				if(cnt[s[head]] > 0){
					matchCnt++;
				}
			}
			if(tail - head == p.length()){
				ans.push_back(head);
			}
			head++;
		}
	}
	return ans;
}

int main(){
	string s, p;
	getline(cin, s);
	getline(cin, p);
	vector<int> ans = Solution2(s, p);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
}
