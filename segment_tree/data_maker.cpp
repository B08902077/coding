#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main(){
	srand(time(NULL));
	int x, y, Size;
	cin >> Size;
	cout << Size << endl;
	for(int i = 0; i < Size; i++){
		cout << rand() % (5*Size);
		if(i != Size-1)	cout << ' ';
		else	cout << endl;
	}
	for(int i = 0; i < 3*Size; i++){
		x = rand() % Size, y = rand() % Size;
		if(x > y){
			swap(x, y);
			cout << "2 " << x << ' ' << y << ' ' << rand() % 1000 - 500 << endl;
		}else{
			cout << "1 " << x << ' ' << y << endl;
		}
	}
	return 0;
}
