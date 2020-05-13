/*
 * Simulate manual addition operation
 * Just keep the main idea of this sort of problems in mind:
 * 1.	add the current least digit and the carry
 * 2.	put the unit digit to the result and set the carry to the ten's digit
 *
 * For this problem, the least digit of K can be extracted by k%10\ 
 * then k /= 10 to update the least digit
 *
 * Time complexity: O(max_digit(A, k))
 *
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> Solution(vector<int> &A, int K){
	int i = A.size()-1, k = K, c = 0;
	vector<int> ans;
	while(i >= 0 || k != 0 || c != 0){
		c += (i >= 0)? A[i--] : 0;
		c += k%10;
		ans.push_back(c%10);
		c /= 10;
		k /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(){
	int T, K;
	cin >> T;
	vector<int> A(T);
	for(auto &a: A)
		cin >> a;
	cin >> K;
	vector<int> ans = Solution(A, K);
	for(auto &i: ans)
		cout << i << " ";
	cout << endl;
}
