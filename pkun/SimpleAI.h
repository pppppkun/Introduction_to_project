#include<string>
#include<map>
#include<string>
#include<iostream>

using namespace std;

void put(string p, int q);

void InitComputer();

int unionWeight(int a, int b);

int WeightAdd(string connectType, int i, int j);

int* MachineDrop(const int s[][15]);

void LR(const int s[][15], int X, int Y);

void UD(const int s[][15], int X, int Y);

void Diagonal(const int s[][15], int X, int Y);