/*
 * Brute-force:
 * Enumerate all starting points i, add all numbers from i+1 to the hash table until reaching the limit (K different numbers)\ 
 * Then update the ans and keep iterate through the array until meeting another different number (then break) 
 *
 * Time complexity: O(n^2)
 *
 *
 * Sliding Window (Solution 3):
 * The general steps of solving sliding window problems
 * What we need?
 * usually two pointers and a hash table to record info. of the current contents in the window
 * 
 * 1. Extend the window until meet the requirements
 * (the problem may want maximum number of elements or exact number of elements)
 *
 * 2. Once meeting the requirements, now we have two jobs to do
 * 		1) update the answer
 * 		2) decide how to move the window
 * For 2),  * some have conditions for the left pointer to skip through array (pruning)
 *			* the right pointer usually just ++ (scan one by one)
 *			* since the right pointer always moves,\ 
 *			  the left pointer may need to move for meeting the requirements\ 
 *			  especially for those problems asking for exact number of elements
 * 			* for asking exact number of elements, the window size ususlly should just\ 
 * 			  match the size that can meet the requirement
 * For 1),	consider after adding the current element the right pointer points to\ 
 * 			how many the answer should update
 *
 * For this problem, the left pointer should always point to the element that only has one count in the window
 * Because by doing so, from the base to the left pointer, all elements will be already included in the window
 * The window is the smallest size that contains current A[r] and has exactly K distinct elements (just match the size that can meet the requirement)
 * Therefore, adding each element from the base to the left pointer will also have exactly K distinct elements, and it will be the subarray that we've not yet add to the answer before (due to A[r])
 * If now A[r] is a new number, we should maintain the window, so we delete a number from the window, which is just the element that the left pointer points to, since it only has one count, thus, the distinct numbers in the window = K + 1 - 1 = K
 * Then keep the window be as small as possible again
 * The answer is just the extention of all smallest window which meet the requirement
 *
 *
 * */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int Solution(vector<int> &A, int K){//Brute-force
	if(A.size() < K)	return 0;
	int ans = 0;
	for(int i=0; i<A.size(); i++){
		unordered_map<int,int> exist;
		int cnt = 1;
		if(cnt == K)	ans++;
		exist[A[i]]++;
		for(int j=i+1; j<A.size(); j++){
			if(cnt < K){
				if(exist[A[j]] == 0)	cnt++;
				exist[A[j]]++;
				if(cnt == K)	ans++;
			}else if(cnt == K && exist[A[j]] > 0){
				exist[A[j]]++;
				ans++;
			}else{
				break;
			}
		}
	}
	return ans;
}

int Solution2(vector<int> &A, int K){//TLE, the leftmost part needs to be more efficient
	if(A.size() < K)	return 0;
	int ans = 0, base = 0, cnt = 0;
	unordered_map<int,int> right;//number, rightmost position of the number
	for(int i=0; i<A.size(); i++){
		if(cnt < K){
			if(right.find(A[i]) == right.end())	cnt++;
			right[A[i]] = i;
		}
		if(cnt == K && right.find(A[i]) != right.end()){
			right[A[i]] = i;
			int leftmost = A.size();
			for(auto &r: right){
				leftmost = min(r.second, leftmost);
			}
			ans += leftmost-base+1;
		}else if(cnt == K && right.find(A[i]) == right.end()){
			right[A[i]] = i;
			int leftmost = A.size(), num;
			for(auto &r: right){
				if(r.second < leftmost){
					num = r.first;
					leftmost = r.second;
				}
			}
			base = leftmost+1;
			right.erase(num);
			leftmost = A.size();
			for(auto &r: right)
				leftmost = min(leftmost, r.second);
			ans += leftmost-base+1;
		}
	}
	return ans;
}

int Solution3(vector<int> &A, int K){
	if(A.size() < K)	return 0;
	int l = 0, r = 0, base = 0, uniq = 0, ans = 0;
	bool flag = false;//note the first time uniq == K
	unordered_map<int,int> cnt;//counts of elements inside the window
	while(r < A.size()){
		flag = false;
		if(uniq < K){//extend window to meet the requirement
			if(cnt[A[r]] == 0)	uniq++;
			cnt[A[r]]++;
			flag = true;
		}
		if(uniq == K){//once meet the requirement
			if(cnt[A[r]] == 0){//new number cause uniq > K, make the window contain exactly K
				cnt[A[l]]--;// = 0
				l++;
				base = l;//update the base, since < base, uniq will > K
			}
			if(!flag)	cnt[A[r]]++;
			while(cnt[A[l]] - 1 > 0){//shrink to minimum size
				cnt[A[l]]--;
				l++;
			}
			ans += l-base+1;
		}
		r++;//continue to move the window
	}
	return ans;
}

int main(){
	int T, K;
	cin >> T;
	vector<int> A(T);
	for(auto &a: A)
		cin >> a;
	cin >> K;
	cout << Solution3(A, K) << endl;
}
