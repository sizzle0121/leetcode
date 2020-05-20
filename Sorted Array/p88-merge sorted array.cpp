/*
 * Using extra memory is trivial
 *
 * Without extra memory:
 * Like merge sort, starting from the greatest number of both array
 * Each time, put the greater one to the current back of nums1
 *
 * Starting from the least number can be difficult, since the greatest number of nums1 won't move when we put the smaller numbers in the back
 * Even if we put the least number from the front of nums1, the greatest number of nums1 still need to be moved when its position is processed
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void Solution(vector<int> &nums1, int m, vector<int> &nums2, int n){
	if(n == 0)	return;
	else if(m == 0){
		for(int i=0; i<n; i++)
			nums1[i] = nums2[i];
		return;
	}
	int icur = nums1.size()-1, i1 = m-1, i2 = n-1;
	while(i2 >= 0){
		if(i1 >= 0 && i2 >= 0){
			if(nums1[i1] >= nums2[i2]){
				nums1[icur] = nums1[i1--];
			}else{
				nums1[icur] = nums2[i2--];
			}
		}else if(i2 >= 0){
			nums1[icur] = nums2[i2--];	
		}
		icur--;
	}
}

int main(){
	int m, n;
	cin >> m >> n;
	vector<int> nums1(m+n);
	vector<int> nums2(n);
	for(int i=0; i<m; i++)
		cin >> nums1[i];
	for(int i=0; i<n; i++)
		cin >> nums2[i];
	
	Solution(nums1, m, nums2, n);
	for(auto &num: nums1)
		cout << num << " ";
	cout << endl;
}
