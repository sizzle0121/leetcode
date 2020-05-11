/*
	Bit Manipulation:
	For every number in [0, num]
	Apply AND operator to it with 1 (pick the unit digit of it)
	If it's '1', counter++, then shift it one digit right
	By repeating the above process and push each count of the number into array, we will have the answer
	Time complexity: O(n*S), where S is the number of the digits of num

	DP:
	We can observe that for an odd number i, count(i) is count(i-1) + 1\ 
	since i-1 must be an even number, and the unit digit of an even number must be zero\ 
	thus, we are able to put an additional '1' to it
	For an even number j, count(j) must be the same as count(j/2)\ 
	since the unit digit of j must be zero (as mentioned above)\ 
	we divide it by 2 equals to shift it one digit right (shift the zero out, which won't affect the count of it)
	After that, it will become a number that we have already calculated before, so we get the count

	Time complexity: O(n)
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> Solution(int num){
	vector<int> ans(num+1);
	for(int i=0; i<ans.size(); i++){
		int k = i, tmp = 0;
		while(k != 0){
			if(1 & k)	tmp++;
			k >>= 1;
		}
		ans[i] = tmp;
	}
	return ans;
}

vector<int> Solution2(int num){
	vector<int> ans(num+1);
	for(int i=0; i<ans.size(); i++){
		if(i % 2 == 0)	ans[i] = ans[i/2];
		else	ans[i] = ans[i-1]+1;
	}
	return ans;
}

int main(){
	int num;
	cin >> num;
	vector<int> ans = Solution2(num);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
}
