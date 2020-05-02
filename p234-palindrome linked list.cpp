/*
	Use extra memory to store and compare the value for each symmetric position is trivial
	Try to use O(1) space complexity to solve this problem
	To do so, first, I find out the middle point of the list
	Then, reverse the second half of the linked list (by three pointers)
	The only rest of thing now is to compare the value from both sides to the center

	Time complexity: O(n)
	Space complexity: O(1)
*/
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int _val): val(_val), next(NULL){}
};

ListNode* BuildList(vector<int> &nums){
	if(nums.empty())	return NULL;
	ListNode *head = NULL, *tail = NULL;
	for(int i=0; i<nums.size(); i++){
		if(!head){
			head = new ListNode(nums[i]);
			tail = head;
		}else{
			tail->next = new ListNode(nums[i]);
			tail = tail->next;
		}
	}
	return head;
}

bool Solution(ListNode *head){
	if(!head) return false;
	ListNode *tmp = head, *mid = head;
	int len = 0;
	while(1){
		len++;
		if(!tmp->next)	break;
		tmp = tmp->next;
	}
	if(len == 1)	return true;
	for(int i=0; i<(len/2); i++)
		mid = mid->next;
	ListNode *prev = NULL, *r;
	while(1){
		r = mid->next;
		mid->next = prev;
		if(!r)	break;
		prev = mid;
		mid = r;
	}
	for(int i=0; i<len/2; i++){
		if(head->val != mid->val)
			return false;
		head = head->next;
		mid = mid->next;
	}
	return true;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cout << Solution(BuildList(nums)) << endl;
}
