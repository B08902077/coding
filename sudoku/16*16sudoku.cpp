#include <iostream>
#include "helper.h"
#include <algorithm>
#include <cstdbool>
#include <cctype>
#define board_size 256
#define section_size 16
#define grid_side 4
#define discarded_idx board_size*100000
#define Location(row,col)	(row-1)*section_size+col
#define Row(row,val)	board_size+(row-1)*section_size+val
#define Col(col,val)	2*board_size+(col-1)*section_size+val
#define Grid(row,col,val) 3*board_size+((row-1)/grid_side)*section_size*grid_side+((col-1)/grid_side)*section_size+val
#define arr_set(arr,row,col,val) \
	arr[0] = Location(row,col);\
	arr[1] = Row(row,val);\
	arr[2] = Col(col,val);\
	arr[3] = Grid(row,col,val);

using vvitr = vector<vector<int>>::iterator;
using vitr = vector<int>::iterator;
using namespace DLX;

int board[1+section_size][1+section_size] = {{0}};

void input(){
	char single_row[1+section_size];
	for(int i = 1; i <= section_size; i++){
		cin >> single_row;
		for(int j = 1; j <= section_size; j++){
			if(isdigit(single_row[j-1]))	board[i][j] = single_row[j-1]-'0';
			else	board[i][j] = single_row[j-1]-'A'+10;
		}
	}
}

void output(){
	cout << "------------------------" << '\n';
	char ans_bigger_than_10;
	for(int i=1; i<=section_size; i++){
		for(int j = 1; j <=section_size; j++){
			if(board[i][j] < 10)	cout << board[i][j];
			else	cout << (ans_bigger_than_10 = board[i][j] - 10 + 'A');
		}
		cout << '\n';
	}
}

void solve(){
	Init(board_size*grid_side);
	vector<int> arr;
	arr.resize(4);
	int unimportant_index = discarded_idx;
	for(int i = 1; i <= section_size; i++){
		for(int j = 1; j <= section_size; j++){
			if(board[i][j]){
				arr_set(arr, i, j, board[i][j]);
				AddRow(unimportant_index++, arr);
			}else{
				for(int val = 1; val <= section_size; val++){
					arr_set(arr, i, j, val);
					AddRow((i-1)*board_size+(j-1)*section_size+val, arr);
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
		if(it < discarded_idx){
			row = (--it)/board_size+1;
			it %= board_size;
			col = it/section_size+1;
			it %= section_size;
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
