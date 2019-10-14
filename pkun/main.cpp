#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <map>
#include "SimpleAI.h"

using namespace std;

map<string, int> value;

const int N = 15;       //15*15的棋盘
const char ChessBoard = ' ';
const char flag[2] = { 'X','O' };
int now = 0;

char _ChessBoard[N + 1][N + 1];  //棋盘


typedef struct Position {
	int row;        //行
	int col;        //列
}Position;

Position pos;

void put(string p, int q)
{
	pair<string, int> V(p, q);
	value.insert(V);
}

void InitChessBoard() {          //初始化棋盘
	for (int i = 0; i < N + 1; ++i) {
		for (int j = 0; j < N + 1; ++j) {
			_ChessBoard[i][j] = ChessBoard;
		}
	}
}

void PrintChessBoard()
{        //打印棋盘
	printf("     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n");
	printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
	for (int i = 1; i < N + 1; ++i)
	{
		printf("%2d ", i);
		printf("| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", _ChessBoard[i][1], _ChessBoard[i][2], _ChessBoard[i][3], _ChessBoard[i][4], _ChessBoard[i][5], _ChessBoard[i][6], _ChessBoard[i][7], _ChessBoard[i][8], _ChessBoard[i][9], _ChessBoard[i][10], _ChessBoard[i][11], _ChessBoard[i][12], _ChessBoard[i][13], _ChessBoard[i][14], _ChessBoard[i][15]);
		printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
	}
	cout << endl;
}

int Judgelegal()
{
	if (pos.row > 0 && pos.row <= N && pos.col > 0 && pos.col <= N) {
		if (_ChessBoard[pos.row][pos.col] == ChessBoard) {
			return 1;
		}
	}
	return 0;
}

void ComputerChess()
{
	// AI = 1;
	int p[15][15];
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			if (_ChessBoard[i][j] == flag[1]) p[i][j] = 1;
			if (_ChessBoard[i][j] == flag[2]) p[i][j] = 2;
			else p[i][j] = 0;
		}
	}

	int q[2] = MachineDrop(p);

}

void PlayChess()
{
	PrintChessBoard();
	while (1) {
		printf("It %d turn to input a potision: ", now);

		cin >> pos.row >> pos.col;

		if (Judgelegal())
		{
			_ChessBoard[pos.row][pos.col] = flag[now];
			break;
		}
		cout << "Your input is not legal. Please input a new position!" << endl;
	}
}

int JudgeVictory()
{
	int begin = 0;
	int end = 0;

	//judge row

	(pos.col - 4) > 0 ? begin = (pos.col - 4) : begin = 1;
	(pos.col + 4) > N ? end = N : end = (pos.col + 4);
	for (int i = pos.row, j = begin; j + 4 <= end; ++j) {
		if (_ChessBoard[i][j] == flag[now] && _ChessBoard[i][j + 1] == flag[now] &&
			_ChessBoard[i][j + 2] == flag[now] && _ChessBoard[i][j + 3] == flag[now] &&
			_ChessBoard[i][j + 4] == flag[now])
			return 1;
	}

	//judge column
	(pos.row - 4) > 0 ? begin = (pos.row - 4) : begin = 1;
	(pos.row + 4) > N ? end = N : end = (pos.row + 4);
	for (int j = pos.col, i = begin; i + 4 <= end; ++i) {
		if (_ChessBoard[i][j] == flag[now] && _ChessBoard[i + 1][j] == flag[now] &&
			_ChessBoard[i + 2][j] == flag[now] && _ChessBoard[i + 3][j] == flag[now] &&
			_ChessBoard[i + 4][j] == flag[now])
			return 1;
	}
	//judge Diagonal

	// pay attention to the increaseand decrease of rowsand columns

	int len = 0;
	int start = 0;
	int finish = 0;
	pos.row > pos.col ? len = pos.col - 1 : len = pos.row - 1;
	if (len > 4) {
		len = 4;
	}
	begin = pos.row - len;
	start = pos.col - len;

	pos.row > pos.col ? len = N - pos.row : len = N - pos.col;
	if (len > 4) {
		len = 4;
	}
	end = pos.row + len;
	finish = pos.col + len;

	for (int i = begin, j = start; (i + 4 <= end) && (j + 4 <= finish); ++i, ++j) {
		if (_ChessBoard[i][j] == flag[now] && _ChessBoard[i + 1][j + 1] == flag[now] &&
			_ChessBoard[i + 2][j + 2] == flag[now] && _ChessBoard[i + 3][j + 3] == flag[now] &&
			_ChessBoard[i + 4][j + 4] == flag[now])
			return 1;
	}



	(pos.row - 1) > (N - pos.col) ? len = N - pos.col : len = pos.row - 1;
	if (len > 4) {
		len = 4;
	}
	begin = pos.row - len;
	start = pos.col + len;

	(N - pos.row) > (pos.col - 1) ? len = pos.col - 1 : len = N - pos.row;
	if (len > 4) {
		len = 4;
	}

	end = pos.row + len;
	finish = pos.col - len;
	for (int i = begin, j = start; (i + 4 <= end) && (j - 4 >= finish); ++i, --j) {
		if (_ChessBoard[i][j] == flag[now] && _ChessBoard[i + 1][j - 1] == flag[now] &&
			_ChessBoard[i + 2][j - 2] == flag[now] && _ChessBoard[i + 3][j - 3] == flag[now] &&
			_ChessBoard[i + 4][j - 4] == flag[now])
			return 1;
	}

	//有地可下
	for (int x = 1; x < N + 1; ++x) {
		for (int y = 1; y < N + 1; ++y) {
			if (_ChessBoard[x][y] == ChessBoard) {
				return 0;
			}
		}
	}

	return -1;//和局

}

int GetVictory() {
	int result = JudgeVictory();
	if (result == 1)
	{
		PrintChessBoard();
		cout << "Player" << " " << now << " " << "win!" << endl;
		return 1;
	}
	else if (result == -1)
	{
		cout << "No one win" << endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

int ChoiceMode() {           //选择模式
	system("cls");
	//系统调用，清屏
	InitChessBoard();       //重新初始化棋盘
	cout << "*************************************************" << endl;
	cout << "******************0、退出************************" << endl;
	cout << "******************1、电脑VS玩家******************" << endl;
	cout << "******************2、玩家VS玩家******************" << endl;
	cout << "*************************************************" << endl;
	while (1) {
		int i = 0;
		cout << "请选择模式：";
		cin >> i;
		if (i == 0) {       //退出
			exit(1);
		}
		if (i == 1 || i == 2) {
			return i;
		}
		else {
			cout << "非法输入，请重新输入！" << endl;
		}
	}
}

void Play() {
	Position pos;
	int mode = ChoiceMode();
	while (1)
	{
		if (mode == 1)
		{
			while (1)
			{
				now = 1;
				ComputerChess();
				if (GetVictory()) {
					break;
				}
				now = 2;
				PlayChess();
				if (GetVictory())
				{
					break;
				}
				system("cls");
			}
		}
		else
		{
			while (1)
			{
				PlayChess();
				if (GetVictory())
				{
					break;
				}

				if (now == 0) now = 1;
				else now = 0;
				system("cls");
			}
		}
		cout << "======再来一局=======" << endl;
		cout << "yes or no :";
		char s[] = "yes";
		cin >> s;
		if (strcmp(s, "no") == 0)
		{
			return;
		}
		else
		{
			ChoiceMode();
		}
	}
}

int main()
{
	Play();
	system("pause");
	return 0;
}
