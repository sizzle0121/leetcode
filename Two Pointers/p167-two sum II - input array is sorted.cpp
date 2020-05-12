/*
 * Just like 2 sum, and it's easier, since the array is already sorted
 * Use 2 pointers to search for the target
 *
 * Time complexity: O(n)
 * 
 * */
#include <iostream>
#include <vector>
using namespace std;

vector<int> Solution(vector<int> &numbers, int target){
	if(numbers.size() < 2)	return vector<int>();
	int l = 0, r = numbers.size()-1;
	while(l < r){
		if(numbers[l] + numbers[r] == target)	return vector<int>{l+1, r+1};
		else if(numbers[l] + numbers[r] < target)	l++;
		else	r--;
	}
	return vector<int>();
}

int main(){
	int T, target;
	cin >> T;
	vector<int> numbers(T);
	for(int i=0; i<T; i++)
		cin >> numbers[i];
	cin >> target;
	vector<int> ans = Solution(numbers, target);
	for(auto &i: ans)
		cout << i << " ";
	cout << endl;
}
