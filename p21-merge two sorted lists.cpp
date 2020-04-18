#include <iostream>

using namespace std;

struct ListNode {
     int val;
	 ListNode *next;
	 ListNode(int x) : val(x), next(NULL) {}
};

ListNode* Solution(ListNode *l1, ListNode *l2){
	ListNode *ans = NULL, *itr = NULL;
	while(l1 || l2){
		if(!ans){
			ans = new ListNode(-1);
			itr = ans;
		}else{
			itr->next = new ListNode(-1);
			itr = itr->next;
		}

		if(!l1){
			itr->val = l2->val;
			l2 = l2->next;
		}else if(!l2){
			itr->val = l1->val;
			l1 = l1->next;
		}else{
			if(l1->val < l2->val){
				itr->val = l1->val;
				l1 = l1->next;
			}else{
				itr->val = l2->val;
				l2 = l2->next;
			}
		}
	}
	return ans;
}

ListNode* preprocess(int T){
	bool first = true;
	int tmp;
	ListNode *l, *itr;
	while(T--){
		cin >> tmp;
		if(first){
			l = new ListNode(tmp);
			itr = l;
			first = false;
		}else{
			itr->next = new ListNode(tmp);
			itr = itr->next;
		}
	}
	return l;
}

int main(){
	int T1, T2, tmp;
	cin >> T1 >> T2;
	
	ListNode *l1 = preprocess(T1);
	ListNode *l2 = preprocess(T2);

	ListNode *ans = Solution(l1, l2);
	while(ans){
		cout << ans->val << " ";
		ans = ans->next;
	}cout << endl;

	return 0;
}
