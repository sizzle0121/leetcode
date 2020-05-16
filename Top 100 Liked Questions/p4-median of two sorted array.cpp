/*
 * Just came up with an intuitive solution, need to read the optimal one later
 * Intuitive Solution is trivial:
 * Like merge sort, skip the current least number of both array until the counter reach to the middle, then based on whether the total number of elements is even or odd to calculate the median
 * Because many comments say they have been asked to optimize the space complexity to O(1), so I didn't use extra memory to store the least numbers one by one
 *
 * Time complexity: O((n+m)/2) = O(n+m), n = nums1.size(), m = nums2.size()
 *
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

double Solution2(vector<int> &nums1, vector<int> &nums2){
	int N = nums1.size(), M = nums2.size();
	if(N > M)	return Solution2(nums2, nums1);
	bool odd = (N+M)%2;
	int k = (N+M+1)/2, l = 0, r = N, mid;
	while(l <= r){
		mid = (l+r)/2;
		if(mid < N && nums1[mid] < nums2[k-mid-1]){
			l = mid+1;
		}else if( mid > 0 && nums2[k-mid] < nums1[mid-1]){
			r = mid-1;
		}else{
			int maxL, minR;
			if(mid == 0)		maxL = nums2[k-mid-1];
			else if(k-mid == 0)	maxL = nums1[mid-1];
			else 				maxL = max(nums1[mid-1], nums2[k-mid-1]);
			if(odd)	return maxL;

			if(mid == N)		minR = nums2[k-mid];
			else if(k-mid == M)	minR = nums1[mid];
			else 				minR = min(nums1[mid], nums2[k-mid]);
			return (double)((maxL + minR)/2.0);
		}
	}
	return 0;
}

double Solution(vector<int> &nums1, vector<int> &nums2){
	int N = nums1.size(), M = nums2.size();
	bool odd = (N+M)%2;
	int mid = (N+M)/2 + 1, i=0, j=0, ans=0;
	while(i < N && j < M && mid){
		if(nums1[i] < nums2[j]){
			if(!odd && mid == 2)	ans += nums1[i];
			if(mid == 1)	ans += nums1[i];
			i++;
		}else{
			if(!odd && mid == 2)	ans += nums2[j];
			if(mid == 1)	ans += nums2[j];
			j++;
		}
		mid--;
	}
	while(mid && i < N){
		if(!odd && mid == 2)	ans += nums1[i];
		if(mid == 1)	ans += nums1[i];
		i++;
		mid--;
	}
	while(mid && j < M){
		if(!odd && mid == 2)	ans += nums2[j];
		if(mid == 1)	ans += nums2[j];
		j++;
		mid--;
	}
	if(!odd)	return (double)(ans/2.0);
	else		return (double)(ans);
}

int main(){
	int T1, T2;
	cin >> T1 >> T2;
	vector<int> nums1(T1);
	vector<int> nums2(T2);
	for(auto &num: nums1)
		cin >> num;
	for(auto &num: nums2)
		cin >> num;
	cout << Solution2(nums1, nums2) << endl;
}
