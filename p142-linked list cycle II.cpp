/*
	Same concept as Linked List Cycle
	Let the distance from the beginning to the start of the loop be N
	Let the distance from the start of the loop to the position where two pointers meet be K
	Let the distance from the position where two pointers meet to the start of the loop (the rest of the cycle) be M
	We can infer that (N + K + M + K) = 2*(N + K)	->	the fast one moves two times of the distance the slow one has moved
	Therefore, M = N	->	when the slow one meet the fast one, the slow one continues to moves one unit per timestep
							meanwhile, a pointer from the beginning moves one unit per timestep as well
							they will meet at the start of the loop, which is our answer
	Time complexity: O(N+K+N) = O(N+K)
	Space complexity: O(1)
*/
#include <iostream>
#include <vector>

using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int _val): val(_val), next(NULL) {}
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

ListNode* Solution(ListNode *head){
	ListNode *ptr1 = head, *ptr2 = head, *ptr3 = head;
    while(ptr1 && ptr2){
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
		if(ptr2)	ptr2 = ptr2->next;
        if(ptr2 && ptr1 == ptr2){
			while(ptr1 != ptr3){
        		ptr1 = ptr1->next;
        		ptr3 = ptr3->next;
			}
        	return ptr1;
		}
	}
	return NULL;
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
	ListNode *p = Solution(head);
	if(p){
		ListNode *tmp = head;
		int i=0;
		while(tmp != p){
			tmp = tmp->next;
			i++;
		}
		cout << "tail connects to node index " << i << endl;
	}
	else	cout << "no cycle" << endl;
	return 0;
}
