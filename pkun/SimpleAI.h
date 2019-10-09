#include<string>
#include<map>
#include<iostream>
using namespace std;

map<string, int> value;

using namespace std;

int weightArray[15][15];

void put(string p, int q)
{
	pair<string, int> V(p, q);
	value.insert(V);
}

void InitComputer() {
	put("01", 17);
	put("02", 12);
	put("001", 17);
	put("002", 12);
	put("0001", 17);
	put("0002", 12);

	put("0102", 17);
	put("0201", 12);
	put("0012", 15);
	put("0021", 10);
	put("01002", 19);
	put("02001", 14);
	put("00102", 17);
	put("00201", 12);
	put("00012", 15);
	put("00021", 10);

	put("01000", 21);
	put("02000", 16);
	put("00100", 19);
	put("00200", 14);
	put("00010", 17);
	put("00020", 12);
	put("00001", 15);
	put("00002", 10);

	put("0101", 65);
	put("0202", 60);
	put("0110", 65);
	put("0220", 60);
	put("011", 65);
	put("022", 60);
	put("0011", 65);
	put("0022", 60);

	put("01012", 65);
	put("02021", 60);
	put("01102", 65);
	put("02201", 60);
	put("00112", 65);
	put("00221", 60);

	put("01010", 75);
	put("02020", 70);
	put("01100", 75);
	put("02200", 70);
	put("00110", 75);
	put("00220", 70);
	put("00011", 75);
	put("00022", 70);

	put("0111", 150);
	put("0222", 140);

	put("01112", 150);
	put("02221", 140);

	put("01101", 1000);
	put("02202", 800);
	put("01011", 1000);
	put("02022", 800);
	put("01110", 1000);
	put("02220", 800);

	put("01111", 3000);
	put("02222", 3500);
}

int unionWeight(int a, int b) {
	//必须要先判断a,b两个数值是不是null
	if ((a == NULL) || (b == NULL)) return 0;
	//一一
	else if ((a >= 10) && (a <= 25) && (b >= 10) && (b <= 25)) return 60;
	//一二、二一
	else if (((a >= 10) && (a <= 25) && (b >= 60) && (b <= 80)) || ((a >= 60) && (a <= 80) && (b >= 10) && (b <= 25)))
		return 800;
	//一三、三一、二二
	else if (((a >= 10) && (a <= 25) && (b >= 140) && (b <= 1000)) || ((a >= 140) && (a <= 1000) && (b >= 10) && (b <= 25)) || ((a >= 60) && (a <= 80) && (b >= 60) && (b <= 80)))
		return 3000;
	//二三、三二
	else if (((a >= 60) && (a <= 80) && (b >= 140) && (b <= 1000)) || ((a >= 140) && (a <= 1000) && (b >= 60) && (b <= 80)))
		return 3000;
	else return 0;
}

int* MachineDrop(int s[15][15]) {

	//机器落子
	//先计算出各个位置的权值
	for (int i = 1; i <= 15; i++) {
		for (int j = 1; j <= 15; j++) {
			//首先判断当前位置是否为空
			if (s[i][j] == 0) {
				//往左延伸

				LR(s, i, j);
				UD(s, i, j);
				Diagonal(s, i, j);

			}
		}
	}
	//打印出权值
	for (int i = 1; i <= 15; i++) {
		for (int j = 1; j <= 15; j++) {
			cout << weightArray[i][j] << " ";
		}
		cout << endl;
	}

	//取出最大的权值
	int AIi = 0, AIj = 0;
	int weightmax = 0;
	for (int i = 1; i <= 15; i++) {
		for (int j = 1; j <= 15; j++) {
			if (weightmax < weightArray[i][j]) {
				weightmax = weightArray[i][j];
				AIi = i;
				AIj = j;
				cout << AIi << " " << AIj << endl;
			}
		}
	}

	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 15; j++)
			weightArray[i][j] = 0;

	return new int[] {AIi, AIj};
}

