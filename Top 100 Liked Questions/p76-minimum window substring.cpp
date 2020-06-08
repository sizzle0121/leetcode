/*
 * Sliding Window:
 * To be updated (wanna sleep)
 *
 * */
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

string Solution(string &s, string &t){
	if(s.empty() || t.empty()) return "";
	int lenS = s.length(), lenT = t.length();
	unordered_map<char,int> cnt;
	int total = 0;
	for(int i=0; i<lenT; ++i){
		cnt[t[i]]++;
		total++;
	}
	int l = 0, r = 0, ansl = -1, ansr = -1;
	while(r < lenS){
		if(cnt.find(s[r]) != cnt.end()){
			cnt[s[r]]--;
			if(cnt[s[r]] >= 0){	
				total--;
			}
		}

		if(total == 0){
			while(1){	
				if(cnt.find(s[l]) != cnt.end()){
					if(cnt[s[l]] == 0) break; 
					cnt[s[l]]++;
				}
				l++;
			}
			if(ansl == -1){
				ansl = l;
				ansr = r;
			}else if(r-l < ansr-ansl){
				ansl = l;
				ansr = r;
			}
			cnt[s[l]]++;
			total++;
			l++;
		}
		r++;
	}
	if(ansl == -1) return "";
	return s.substr(ansl, ansr-ansl+1);
}

int main(){
	string s, t;
	getline(cin, s);
	getline(cin, t);
	cout << Solution(s, t) << endl;
}
