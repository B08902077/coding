#include <iostream>
#include "helper.h"
#include <algorithm>
#include <cstdbool>
#define Location(row,col)	(row-1)*9+col
#define Row(row,val)	81+(row-1)*9+val
#define Col(col,val)	162+(col-1)*9+val
#define Grid(row,col,val) 243+((row-1)/3)*27+((col-1)/3)*9+val
#define arr_set(arr,row,col,val) \
	arr[0] = Location(row,col);\
	arr[1] = Row(row,val);\
	arr[2] = Col(col,val);\
	arr[3] = Grid(row,col,val);

using vvitr = vector<vector<int>>::iterator;
using vitr = vector<int>::iterator;
using namespace DLX;

int board[10][10] = {{0}};

void input(){
	char single_row[10];
	for(int i = 1; i < 10; i++){
		cin >> single_row;
		for(int j = 1; j < 10; j++){
			board[i][j] = single_row[j-1]-'0';
		}
	}
}

void output(){
	cout << "------------------------" << '\n';
	for(int i=1; i<10; i++){
		for(int j = 1; j < 10; j++){
			cout << board[i][j];
		}
		cout << '\n';
	}
}

void solve(){
	Init(324);
	vector<int> arr;
	arr.resize(4);
	int unimportant_index = 1000;
	for(int i = 1; i < 10; i++){
		for(int j = 1; j < 10; j++){
			if(board[i][j]){
				arr_set(arr, i, j, board[i][j]);
				AddRow(unimportant_index++, arr);
			}else{
				for(int val = 1; val < 10; val++){
					arr_set(arr, i, j, val);
					AddRow((i-1)*81+(j-1)*9+val, arr);
				}
			}
		}
	}
	vector<int> ans = Solver();
	if(ans.empty()){
		cout << "No answer!!\n";
		exit(0);
	}
	int row, col;
	for(auto it : ans){
		if(it < 1000){
			row = (--it)/81+1;
			it %= 81;
			col = it/9+1;
			it %= 9;
			board[row][col] = it+1;
		}
	}
}

int main(){
	input();
	solve();
	output();
	return 0;
}
