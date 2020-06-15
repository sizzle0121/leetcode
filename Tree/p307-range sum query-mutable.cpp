/*
 * Segment Tree:
 * Implement typical segment tree structure
 *
 * Time complexity: 
 * Build segment tree: O(n)
 * Update: O(logn)
 * sumRange: O(logn)
 *
 * Space complexity: O(n)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

class NumArray{
public:
	NumArray(vector<int> &nums){
		int N = nums.size();
		segTree.resize(4*N);
		if(N > 0) build(0, N-1, 1, nums);
	}

	struct Node{
		int v, l, r;
		Node(): v(0), l(-1), r(-1) {}
		Node(int _v, int _l, int _r): v(_v), l(_l), r(_r) {}
	};

	void build(int l, int r, int idx, vector<int> &nums){
		if(l == r){
			segTree[idx] = new Node(nums[l], l, r);
			return;
		}
		int mid = (l+r)/2;
		build(l, mid, idx*2, nums);
		build(mid+1, r, idx*2+1, nums);
		segTree[idx] = new Node(segTree[idx*2]->v + segTree[idx*2+1]->v, segTree[idx*2]->l, segTree[idx*2+1]->r);
	}

	int query(int l, int r, int idx){
		if(l == segTree[idx]->l && r == segTree[idx]->r) return segTree[idx]->v;
		int mid = (segTree[idx]->l + segTree[idx]->r)/2;
		if(l > mid) return query(l, r, idx*2+1);
		else if(r <= mid) return query(l, r, idx*2);
		else return query(l, mid, idx*2) + query(mid+1, r, idx*2+1);
	}

	void modify(int l, int r, int idx, int val){
		if(l == segTree[idx]->l && r == segTree[idx]->r){
			segTree[idx]->v = val;
			return;
		}
		int mid = (segTree[idx]->l + segTree[idx]->r)/2;
		if(l > mid){
			modify(l, r, idx*2+1, val);
			segTree[idx]->v = segTree[idx*2]->v + segTree[idx*2+1]->v;
			return;
		}else if(r <= mid){
			modify(l, r, idx*2, val);
			segTree[idx]->v = segTree[idx*2]->v + segTree[idx*2+1]->v;
			return;
		}
	}

	void update(int i, int val){
		if(!segTree.empty() && i >= segTree[1]->l && i <= segTree[1]->r)
			modify(i, i, 1, val);
	}

	int sumRange(int i, int j){
		if(segTree.empty() || i < segTree[1]->l || i > segTree[1]->r || j < segTree[1]->l || j > segTree[1]->r) return 0;
		return query(i, j, 1);
	}

private:
	vector<Node*> segTree;

};

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	NumArray *obj = new NumArray(nums);
	cin.ignore();
	while(1){
		string s;
		getline(cin, s);
		int l = s.find("("), r = s.find(",");
		stringstream ss1, ss2;
		ss1 << s.substr(l+1, r-l-1);
		ss2 << s.substr(r+2, s.length()-r-3);
		ss1 >> l;
		ss2 >> r;
		if(s[0] == 's'){
			cout << obj->sumRange(l, r) << endl;
		}else if(s[0] == 'u'){
			obj->update(l, r);
		}
	}
}
