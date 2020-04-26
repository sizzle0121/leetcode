/*
	Using hash table is easy

	Two pointers: (a.k.a Floyd's Tortoise and Hare Algorithm)
	Let two pointers travel the list with different volacity
	One moves one position ahead at each timestep, and the other moves two positions ahead
	If two pointers meet, then there is a cycle in the list, otherwise, there is no cycle
	Proof of they will meet:
		Consider the fast one is one step behind the slow one, at next timestep, they will meet
		Consider the fast one is two steps behind the slow one, they will become the above condition at next timestep and eventaully meet
		3, 4, ... steps behind will become the above condition as well (the fast one catches up the slow one a unit of distance a time)
	
	If no cycle, the fast one will become the NULL pointer first

	Time complexity: O(n+k), where n is the non-cycle part of the list, k is the cycle length (there are at most k units of distance should be catched up by the fast one)
	Space complexity: O(1)

*/
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode* BuildList(vector<int> &nums, int pos){
	if(nums.empty())	return NULL;
	ListNode *head = NULL, *tail = NULL;
	vector<ListNode*> idx;
	for(int i=0; i<nums.size(); i++){
		if(!head){
			head = new ListNode(nums[i]);
			tail = head;
		}else{
			tail->next = new ListNode(nums[i]);
			tail = tail->next;
		}
		idx.push_back(tail);
	}
	if(pos != -1)	tail->next = idx[pos];
	return head;
}

bool Solution(ListNode *head){
	if(!head)	return false;
	ListNode *ptr1 = head, *ptr2 = head;
	while(ptr1 && ptr2){
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
		if(ptr2)	ptr2 = ptr2->next;
		if(ptr1 && ptr2 && ptr1 == ptr2)	return true;
	}
	return false;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	int pos;
	cin >> pos;
	ListNode *head = BuildList(nums, pos);
	cout << Solution(head) << endl;
	return 0;
}
