#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class QInt
{
private:
	unsigned int data[4];
public:
	QInt();
	~QInt();
	void Nhap();
	void Xuat();
	QInt operator~();
	QInt operator&(QInt b);
	QInt operator^(QInt b);
	QInt operator|(QInt b);
	QInt operator<<(int n);
	QInt operator >> (int n);
	void rol();
	void ror();
	string decToBin();
	QInt binToDec(string s);
	string binToHex(string s);
	string decToStr();
	string decToHex();
	QInt operator+(QInt B);
	QInt operator-(QInt B);
	bool operator>(QInt B);
	bool operator<(QInt B);
	bool operator<=(QInt B);
	bool operator==(QInt B);
	bool operator>=(QInt B);
	QInt& operator=(QInt B);
	QInt &operator=(string s);
	QInt hexToDec(string s);
	QInt operator/(QInt B);
	QInt operator*(QInt B);
};

string chia2(string s);
string plusNumInStr(string a, string b);
string multiple2(string s);
string myPow(int n);
int strToNum(string s);

