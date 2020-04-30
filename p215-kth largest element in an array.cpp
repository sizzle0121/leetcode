/*
	Sorting Approaches:
	1. Sort and access the kth number
	2. Use nth_element to sort and return the k-1 one
	3. Use partial_sort and return the k-1 one
	
	Time complexity: 1: O(nlogn), 2: O(n), 3: O(n) 
	
	Heap:
	Use Max Heap (can use priority queue ...), actually, Min Heap is also valid
	Max Heap, pop out k-1 element, then the top will be our desire answer
	
	Time complexity: O(nlogn)
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class maxHeap{
public:
	maxHeap(){
		container.push_back(-1);
	}
	void insert(int x){
		container.push_back(x);
		int i = container.size()-1;
		while(i > 1 && container[i/2] < x){
			swap(container[i], container[i/2]);
			i /= 2;
		}
	}
	void pop(){
		container[1] = container.back();
		container.pop_back();
		int maxChild, i;
		if(container.size() > 2){
			maxChild = container[2];
			i = 2;
		}
		if(container.size() > 3 && maxChild < container[3]){
			maxChild = container[3];
			i = 3;
		}
		while(i > 1 && container[i] > container[i/2]){
			swap(container[i], container[i/2]);
			int idx = i;
			if(i*2 < container.size()){
				maxChild = container[i*2];
				idx = i*2;
			}
			if(i*2+1 < container.size() && maxChild < container[i*2+1])
				idx = i*2+1;
			if(idx == i)	break;
			i = idx;
		}
	}
	int top(){
		return container[1];
	}

private:
	vector<int> container;
};

int Solution2(vector<int> &nums, int k){
	maxHeap *heap = new maxHeap();
	for(int i=0; i<nums.size(); i++)
		heap->insert(nums[i]);
	for(int i=0; i<k-1; i++){
		heap->pop();
	}
	return heap->top();
}

int Solution(vector<int> &nums, int k){
	//sort(nums.begin(), nums.end());
	//return nums[nums.size()-k];
	//nth_element(nums.begin(), nums.begin()+k, nums.end(), greater<int>());
	//return nums[k-1];
	partial_sort(nums.begin(), nums.begin()+k, nums.end(), greater<int>());
	return nums[k-1];
}

int main(){
	int T, target;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cin >> target;
	cout << Solution2(nums, target) << endl;
}
