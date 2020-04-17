/*
**	brute-force: O(n^2)

** 	find larger h or larger w
	-> start from max w, then find larger h from left+1/right-1, depends on min(left, right)
	-> O(n)
	pf:
	smaller h must contain less water(h'*(w-1) < h*w)
	if left > right, finding larger left still contain less water(h*(w-1) < h*w) 
1, 2, 3, 2, 9, 5
*/
#include <iostream>
#include <vector>

using namespace std;

int Solution(vector<int> &height){
	int l = 0, r = height.size()-1;
	int ans = 0, area;
	while(l < r){
		if(height[l] < height[r]){
			area = height[l] * (r-l);
			l++;
		}else{
			area = height[r] * (r-l);
			r--;
		}
		if(ans < area)	ans = area;
	}
	return ans;
}

int main(){
	vector<int> height;
	int T, tmp;	//T for testing, numbers of input integers
	cin >> T;
	while(T--){
		cin >> tmp;
		height.push_back(tmp);
	}
	cout << Solution(height) << endl;

	return 0;
}
