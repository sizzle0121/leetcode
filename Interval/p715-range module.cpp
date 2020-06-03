/*
 * Linked List:
 * Implement linked list to maintain sorted disjoint intervals
 *
 * Time complexity:
 * addRange: O(k), k is the number of intervals in the linked list
 * removeRange: O(k)
 * queryRange: O(k)
 *
 *
 * Optimal Solution is Segment Tree (wil be updated later)
 *
 * */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class RangeModule{
public:
	struct ListNode{
		int l, r;
		ListNode *next;
		ListNode(int _l, int _r): l(_l), r(_r), next(NULL) {}
	};
	
	RangeModule(): head(NULL){}

	void addRange(int left, int right){
		right = right-1;
		ListNode *tail = head;
		if(!head){
			head = new ListNode(left, right);
		}else{
			ListNode *prev = NULL;
			while(tail && tail->r < left){
				prev = tail;
				tail = tail->next;
			}
			bool first = true;
			while(tail && tail->l <= right){
				left = min(left, tail->l);
				right = max(right, tail->r);
				if(first){
					first = false;
					tail = tail->next;
				}else{
					ListNode *tmp = tail;
					tail = tail->next;
					delete tmp;
				}
			}
			if(!first){
				if(prev){//normal merge
					prev = prev->next;
					prev->l = left;
					prev->r = right;
					prev->next = tail;	
				}else{//merge at head
					prev = new ListNode(left, right);
					prev->next = tail;
					delete head;
					head = prev;
				}
			}else{
				if(prev){//insert to the middle
					prev->next = new ListNode(left, right);
					prev = prev->next;
					prev->next = tail;
				}else{//insert to the front
					head = new ListNode(left, right);
					head->next = tail;
				}
			}
		}
	}

	bool queryRange(int left, int right){
		right = right-1;
		if(!head) return false;
		ListNode *tail = head;
		while(tail && tail->r < left) tail = tail->next;
		while(tail && tail->l <= right){
			if(left >= tail->l && right <= tail->r){
				return true;
			}else if(left >= tail->l){
				left = tail->r + 1;
			}else if(right <= tail->r){
				right = tail->l - 1;
			}
			tail = tail->next;
		}
		return false;
	}

	void removeRange(int left, int right){
		right = right-1;
		if(!head) return;
		ListNode *tail = head, *prev = NULL;
		while(tail && tail->r < left){
			prev = tail;
			tail = tail->next;
		}
		while(tail && tail->l <= right){
			ListNode *tmp = tail->next;
			if(tail->l >= left){
				if(tail->r > right){
					tail->l = right+1;
					prev = tail;
				}else{
					if(prev) prev->next = tmp;
					else{
						head = tmp;
					}
					delete tail;
				}
			}else{
				if(tail->r <= right){
					tail->r = left-1;
					prev = tail;
				}else{
					ListNode *part = new ListNode(right+1, tail->r);
					tail->r = left-1;
					tail->next = part;
					part->next = tmp;
					prev = part;
				}
			}
			tail = tmp;
		}
	}

	void print(){
		if(head){
			ListNode *tail = head;
			while(tail){
				cout << tail->l << " " << tail->r << endl;
				tail = tail->next;
			}
		}
	}

private:
	ListNode *head;
};

int main(){
	RangeModule *obj = new RangeModule();
	while(1){
		string ipt;
		getline(cin, ipt);
		int i = ipt.find("("), j = ipt.find(","), l, r;
		if(i != string::npos && j != string::npos){
			stringstream ss1, ss2;
			ss1 << ipt.substr(i+1, j-i-1);
			ss1 >> l;
			ss2 << ipt.substr(j+2, ipt.length()-1-j-2);
			ss2 >> r;
			if(ipt[0] == 'a'){
				obj->addRange(l, r);
				obj->print();
			}else if(ipt[0] == 'r'){
				obj->removeRange(l, r);		
				obj->print();
			}else if(ipt[0] == 'q'){
				cout << obj->queryRange(l, r) << endl;
			}
		}
		if(ipt == "exit"){
			break;
		}
	}	
}
