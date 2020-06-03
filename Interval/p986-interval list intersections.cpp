/*
 * Merge Intervals:
 * Still, by the opposite logic: 
 * If one is in front of the other, say A[i] is in front of B[j], then i++
 * If no one is completely in front of the other, then there must be overlapping, merge and push it into the answer array
 *  then we should fix the later one (whose end of the inverval is farther), and look up the next interval of the former
 *
 * Another way of thinking is merge sort:
 * Each time, if no overlap, remove the smallest interval (whose end of the interval is smaller) of either A or B
 * If overlap, push it into the answer array, and still, remove the smallest interval
 *
 * Time complexity: O(n + m)
 * Space complexity: O(1), answer space is generally not counted as extra memory
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > Solution(vector<vector<int> > &A, vector<vector<int> > &B){
	vector<vector<int> > ans;
	if(A.empty() || B.empty()) return ans;
	int ia = 0, ib = 0;
	while(ia < A.size() && ib < B.size()){
		if(A[ia][0] > B[ib][1]) ib++;
		else if(A[ia][1] >= B[ib][0]){
			ans.push_back(vector<int>{max(A[ia][0], B[ib][0]), min(A[ia][1], B[ib][1])});	
			if(A[ia][1] > B[ib][1]) ib++;
			else if(A[ia][1] < B[ib][1]) ia++;
			else{
				ia++;
				ib++;
			}
		}else if(A[ia][1] < B[ib][0]){
			ia++;
		}
	}
	return ans;
}

int main(){
	int ta, tb;
	cin >> ta;
	vector<vector<int> > A(ta, vector<int>(2));
	for(auto &a: A)
		cin >> a[0] >> a[1];
	cin >> tb;
	vector<vector<int> > B(tb, vector<int>(2));
	for(auto &b: B)
		cin >> b[0] >> b[1];
	
	vector<vector<int> > ans = Solution(A, B);
	for(auto &a: ans)
		cout << a[0] << " " << a[1] << endl;
}
