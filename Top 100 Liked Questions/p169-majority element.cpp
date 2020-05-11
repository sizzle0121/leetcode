/*
	Hash Table:
	Simply go through the array and count the elements
	If the element has not yet been insert into the hash table, insert it in and set its count to one
	Otherwise, simply add 1 to the count of it
	Eventually, we can check who has the most count (the most = over a half, since the problem promise the majority always exist) by go through the hash table
	
	Time complexity: O(n)


	Boyer-Moore Voting Algorithm:
	The majority must has the most vote (over a half of votes)
	We set a counter which will plus 1 when nums[i] == current majority candidate, minus 1 when nums[i] == others
	If the counter becomes zero, we set the next nums[i] as our new majority candidate
	Since the majority will at least has 1 more vote than the minority, the counter will eventually > 0 and the majority candidate will be our true majority

	Time complexity: O(n)

*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//Boyer-Moore Voting Algorithm
int Solution2(vector<int> &nums){
	int cnt = 0, major;
	for(int i=0; i<nums.size(); i++){
		if(cnt == 0)	major = nums[i];
		cnt += (nums[i] == major)? 1 : -1;
	}
	return major;
}

//Hash Table
int Solution(vector<int> &nums){
	unordered_map<int, int> cnt;
	int half = nums.size()/2;
	for(int i=0; i<nums.size(); i++){
		if(cnt.find(nums[i]) != cnt.end()){
			cnt[nums[i]]++;
		}else{
			cnt[nums[i]] = 1;
		}
	}
	for(unordered_map<int,int>::iterator i=cnt.begin(); i != cnt.end(); i++){
		if(i->second > half){
			return i->first;
		}
	}
	return -1;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cout << Solution(nums) << endl;
	cout << Solution2(nums) << endl;
}
