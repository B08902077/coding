#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <climits>
#define SIZE 1000000
using ll = int64_t;
using namespace std;

struct Segment_tree{
	int l, r;
	ll Sum;
	ll tag;
}node[SIZE*4];

vector<int> v;

ll Sum_ans(int L, int R){
	ll Sum = v.at(L);
	for(int i = L+1; i <= R; i++)	Sum += v.at(i);
	return Sum;
}

void Sum_add(int L, int R, int n){
	for(int i = L; i <= R; i++){
		v.at(i) += n;
	}
}

void print_seq(int L, int R){
	for(int i = L; i <= R; i++)	cout << v.at(i) << ' ';
	cout << endl;
}

void Build_SegmentTree(int p, int L, int R){
	node[p].l = L, node[p].r = R, node[p].tag = 0;
	if(L == R){
		node[p].Sum = v.at(L);
		return;
	}
	int mid = (L+R)/2;
	Build_SegmentTree(p*2+1, L, mid);
	Build_SegmentTree(p*2+2, mid+1, R);
	node[p].Sum = node[p*2+1].Sum + node[p*2+2].Sum;
}

void pushdown(int p){
	if(node[p].tag != 0){
		node[p*2+1].tag += node[p].tag;
		node[p*2+2].tag += node[p].tag;
		node[p*2+1].Sum += node[p].tag * (node[p*2+1].r - node[p*2+1].l+1);
		node[p*2+2].Sum += node[p].tag * (node[p*2+2].r - node[p*2+2].l+1);
		node[p].tag = 0;
	}
}

ll query_Sum(int p, int L, int R){
	if(L <= node[p].l && R >= node[p].r)	return node[p].Sum;
	pushdown(p);
	int mid = (node[p].l + node[p].r) / 2;
	ll Sum = 0;
	if(L <= mid)	Sum += query_Sum(p*2+1, L, R);
	if(R > mid)	Sum += query_Sum(p*2+2, L, R);
	return Sum;
}

void query_add(int p, int L, int R, int n){
	if(L <= node[p].l && R >= node[p].r){
		node[p].tag += n;
		node[p].Sum += n * (node[p].r - node[p].l + 1);
		return;
	}
	pushdown(p);
	int mid = (node[p].l + node[p].r) / 2;
	if(L <= mid)	query_add(p*2+1, L, R, n);
	if(R > mid)	query_add(p*2+2, L, R, n);
	node[p].Sum = node[p*2+1].Sum + node[p*2+2].Sum;
}

int main(){
	srand(time(NULL));
	int Command, L, R;
	int n, N;
	cin >> N;
#ifdef TEST
	for(int i = 0; i < N; i++)	v.emplace_back(rand() % (5*N));
#endif
#ifndef TEST
	for(int i = 0; i < N; i++){
		cin >> n;
		v.emplace_back(n);
	}
#endif
	Build_SegmentTree(0, 0, N-1);
#ifdef TEST
	while(cin >> Command >> L >> R){
		switch(Command){
		case 2:
			print_seq(L, R);
			break;
		case 3:
			cout << "query_Sum = " << query_Sum(0, L, R) << endl;
			break;
		case 4:
			cin >> n;
			cout << "before query_adding: " << query_Sum(0, L, R) + n * (R-L+1) << endl;
			query_add(0, L, R, n);
			cout << "after query_adding: " << query_Sum(0, L, R) << endl;
			Sum_add(L, R, n);
		}
		cout << "Sum_ans = " << Sum_ans(L, R) << endl;
	}
#endif
#ifdef QUERY
	while(cin >> Command >> L >> R){
		if(Command == 1)	cout << query_Sum(0, L, R) << endl;
		else{
			cin >> N;
			query_add(0,L,R,N);
		}
	}
#endif
#ifdef ANS
	while(cin >> Command >> L >> R){
		if(Command == 1)	cout << Sum_ans(L, R) << endl;
		else{
			cin >> N;
			Sum_add(L,R,N);
		}
	}
#endif
	return 0;
}
