/*
	Using Hash Table is trivial

	Main idea:
	Get the length of each list, say LenA and LenB, by go through the lists
	Then move the long one for abs(LenA - LenB) steps, making them start at the same distance from the intersection
	Now we can move them step by step together and they will meet at the intersection
	If they don't meet, return null pointer

	Time complexity: O(n)
	Space complexity: O(1)
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int _val): val(_val), next(NULL){}
};

pair<ListNode*,ListNode*> BuildList(vector<int> &listA, vector<int> &listB, int skipA, int skipB){
	ListNode *headA = NULL, *headB = NULL;
	ListNode *tailA = NULL, *tailB = NULL;
	for(int i=0; i<skipA; i++){
		if(!headA){
			headA = new ListNode(listA[i]);
			tailA = headA;
		}else{
			tailA->next = new ListNode(listA[i]);
			tailA = tailA->next;
		}
	}
	for(int i=0; i<skipB; i++){
		if(!headB){
			headB = new ListNode(listB[i]);
			tailB = headB;
		}else{
			tailB->next = new ListNode(listB[i]);
			tailB = tailB->next;
		}
	}
	for(int i=skipA; i<listA.size(); i++){
		if(!headA){
			headA = new ListNode(listA[i]);
			tailA = headA;
		}else{
			tailA->next = new ListNode(listA[i]);
			tailA = tailA->next;
		}
		if(!headB){
			headB = tailA;
			tailB = headB;
		}else{
			tailB->next = tailA;
			tailB = tailB->next;
		}
	}
	return pair<ListNode*,ListNode*>(headA, headB);
}

ListNode* Solution(ListNode *headA, ListNode *headB){
	//count length
	int lenA = 0, lenB = 0;
	ListNode *tailA = headA, *tailB = headB;
	while(tailA){
		lenA++;
		tailA = tailA->next;
	}
	while(tailB){
		lenB++;
		tailB = tailB->next;
	}
	tailA = headA;
	tailB = headB;
	if(lenA > lenB){
		for(int i=0; i<lenA-lenB; i++)
			tailA = tailA->next;
	}else if(lenA < lenB){
		for(int i=0; i<lenB-lenA; i++)
			tailB = tailB->next;
	}

	while(tailA && tailB){
		if(tailA == tailB){
			break;
		}
		tailA = tailA->next;
		tailB = tailB->next;
	}
	if(!tailA || !tailB)	return NULL;
	else	return tailA;
}

int main(){
	int a, b;
	cin >> a >> b;
	vector<int> listA(a);
	vector<int> listB(b);
	for(int i=0; i<a; i++)
		cin >> listA[i];
	for(int i=0; i<b; i++)
		cin >> listB[i];
	int skipA, skipB;
	cin >> skipA >> skipB;
	pair<ListNode*,ListNode*> pack = BuildList(listA, listB, skipA, skipB);
	ListNode *ans = Solution(pack.first, pack.second);
	if(!ans)	cout << "null" << endl;
	else	cout << ans->val << endl;
}
