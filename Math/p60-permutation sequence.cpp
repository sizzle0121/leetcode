/*
 * Backtrack (got TLE):
 * Backtrack to find permutations by order, when it's the k-th permutation, return
 *
 * Time complexity: O(n!)
 * Space complexity: O(n), for recursion
 * 
 *
 * Math:
 * Calculate k-th will be at which position
 * There are n! permutations in total, if k is between (p-1)! and p!\ 
 * 
 * Add ascending order numbers:
 * we can determine that between (n-p) and the current tail of the answer, the numbers (not in the answer yet) will be in ascending order\ 
 * For example, k = 50, n = 7
 * 50 is between 4!=24 and 5!=120
 * thus, 0(current tail of the answer is nothing) to 7-5=2 will be 1, 2
 * 
 * Skip (p-1)!:
 * Then we can caluculate how many (p-1)! k skips, for the above example, 50 skips 24*2\ 
 * and for skipping a (p-1)!, the initial digit will increase one\ 
 * so for the above example, the initial digit is originally 3, after skipping one 4! -> 3+1, after skipping two 4! -> 3+2
 * so now the answer has 1, 2, 5, and k becomes 50 % 24 = 2 remains
 * 
 * By repeating adding asending order, skip (p-1)!, and update k, we will obtain the answer when k becomes 0
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void backtrack(vector<bool> &visit, string &ans, int n, int &k){
	if(ans.length() == n){
		k--;
		return;
	}
	for(int i=1; i<=n; i++){
		if(!visit[i]){
			ans.push_back((char)(i+'0'));
			visit[i] = true;
			backtrack(visit, ans, n, k);
			if(k == 0) return;
			ans.pop_back();
			visit[i] = false;
		}
	}
}

string Solution(int n, int k){
	vector<bool> visit(n+1);
	string ans="";
	backtrack(visit, ans, n, k);
	return ans;
}

string Solution2(int n, int k){
	vector<bool> used(n+1);
	string ans = "";
	int base = 0;
	while(k){
		int tmp = 1, i;
		int cur = 1;
		for(i=1; i<=n; i++){//determine current k is between which p!, (p-1)!
			if(tmp*i < k) tmp *= i;
			else break;
		}
		int cnt = n-i;//add numbers in ascending order in front of p
		while(cnt-base){//base is the tail of the current answer
			if(!used[cur]){
				ans.push_back((char)(cur+'0'));
				used[cur] = true;
				cnt--;
			}
			cur++;
		}
		cnt = k / tmp + 1;//skip k/tmp and push k/tmp+1 into the answer
		if(k%tmp == 0) cnt--;//edge case, if remainder is zero, k cannot skip the last round of the initial digit
		cur = 1;
		while(cnt){
			if(!used[cur]) cnt--;//find the (k/tmp + 1)-th unused number
			cur++;
		}
		//can't let cnt = k/tmp and modify the below to cur+'0', since when leaving the loop, cur may not be unused
		ans.push_back((char)(cur-1+'0'));//when leaving the loop, cur has been added with an extra 1
		used[cur-1] = true;
		k %= tmp;//update k
		base = ans.size();//update the tail of the answer
	}
	for(int i=n; i>=1; --i)
		if(!used[i])
			ans.push_back((char)(i+'0'));//push the remaining into the answer
	return ans;
}

int main(){
	int n, k;
	cin >> n >> k;
	cout << Solution2(n, k) << endl;
	cout << Solution(n, k) << endl;
}
