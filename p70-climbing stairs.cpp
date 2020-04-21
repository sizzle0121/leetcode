/*
	DP:
	Opimal Substructure: way(i) = way(i-1) + way(i-2)
	way(1) = 1
	way(2) = 2
	Time complexity: O(n)
*/

#include <iostream>

using namespace std;

int Solution(int n){
	long long way[n+1];
	way[1] = 1;
	if(n > 1)	way[2] = 2;
	for(int i=3; i<=n; i++)
		way[i] = way[i-1] + way[i-2];
	return way[n];
}

int main(){
	int n;
	cin >> n;
	cout << Solution(n) << endl;
	return 0;
}
