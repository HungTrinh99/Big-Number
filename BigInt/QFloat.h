#pragma once
#include"stdafx.h"
#include"QInt.h"
#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
class QFloat
{
private:
	short int data[8];// data[7] and data[6] save exponent and sign
public:
	void Nhap();
	void Xuat();
	QFloat binToDec(string);
	string decToBin(QFloat);
	QFloat();
	~QFloat();
};
string numToString(int k);
int countSkip(string s, int k);
string myFivePow(int n);
string multiple5(string s);
string myTenPow(int n);

