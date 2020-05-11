#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };

ListNode* Solution(ListNode *head, int n){
	vector<ListNode*> pos;
	while(head){
		ListNode *tmp = head;
		pos.push_back(tmp);
		head = head->next;
	}
	if(n == pos.size()){
		delete pos[pos.size()-n];
		if(pos.size() > 1)	return pos[1];
		else	return 0;
	}else if(n == 1){
		pos[pos.size()-n-1]->next = NULL;
		delete pos[pos.size()-n];
		return pos[0];
	}else{
		pos[pos.size()-n-1]->next = pos[pos.size()-n+1];
		delete pos[pos.size()-n];
		return pos[0];
	}
}

void OutputList(ListNode *head){
	while(head){
		cout << head->val << " ";
		head = head->next;
	}cout << endl;
}

int main(){
	int T, ipt, n;//T: numbers of input
	cin >> T;

	ListNode *head;
	ListNode *tail;
	bool first = true;
	while(T--){
		cin >> ipt;
		if(first){
			first = false;
			head = new ListNode(ipt);
			tail = head;
		}else{
			tail->next = new ListNode(ipt);
			tail = tail->next;
		}
	}
	cin >> n;
	OutputList(Solution(head, n));

	return 0;
}
