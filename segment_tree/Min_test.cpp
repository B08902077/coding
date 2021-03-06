#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <climits>
#define SIZE 1000000
using namespace std;

struct Segment_tree{
	int l, r;
	int Min;
}node[SIZE*4];

vector<int> v;

int min(int &x, int &y){
	if(x < y) return x;
	return y;
}

int Min_ans(int L, int R){
	int Min = v.at(L);
	for(int i = L+1; i <= R; i++)	if(Min > v.at(i))	Min = v.at(i);
	return Min;
}

void print_seq(int L, int R){
	for(int i = L; i <= R; i++)	cout << "i = " << v.at(i) << endl;
}

void Build_SegmentTree(int p, int L, int R){
	node[p].l = L, node[p].r = R;
	if(L == R){
		node[p].Min = v.at(L);
		return;
	}
	int mid = (L+R)/2;
	Build_SegmentTree(p*2+1, L, mid);
	Build_SegmentTree(p*2+2, mid+1, R);
	node[p].Min = min(node[p*2+1].Min, node[p*2+2].Min);
}

int query_Min(int p, int L, int R){
	if(L <= node[p].l && R >= node[p].r)	return node[p].Min;
	int mid = (node[p].l + node[p].r) / 2;
	int Min = INT_MAX;
	if(L <= mid)	Min = min(Min, query_Min(p*2+1, L, R));
	if(R > mid)	Min = min(Min, query_Min(p*2+2, L, R));
	return Min;
}

int main(){
	srand(time(NULL));
	int Command, L, R;
#ifdef TEST
	for(int i = 0; i < SIZE; i++)	v.emplace_back(rand() % 50000);
#endif
#ifndef TEST
	int n;
	for(int i = 0; i < SIZE; i++){
		cin >> n;
		v.emplace_back(n);
	}
#endif
	Build_SegmentTree(0, 0, SIZE-1);
#ifdef TEST
	while(cin >> Command >> L >> R){
		switch(Command){
		case 2:
			print_seq(L, R);
			break;
		case 3:
			cout << "query_Min = " << query_Min(0, L, R) << endl;
			break;
		}
		cout << "Min_ans = " << Min_ans(L, R) << endl;
	}
#endif
#ifdef QUERY
	while(cin >> L >> R){
		cout << query_Min(0, L, R) << endl;
	}
#endif
#ifdef ANS
	while(cin >> L >> R){
		cout << Min_ans(L, R) << endl;
	}
#endif
	return 0;
}
