#include "stdafx.h"
#include "QFloat.h"
#include<math.h>
//Input
void QFloat::Nhap()
{
	//Nhập một số lớn dạng chuỗi
	string s;
	cout << "Nhap so:";
	cin >> s;
	//Tiến hành đổi chuỗi s sang dạng dấu chấm động rồi lưu vào data
	int i = 0;
	if (s[0] == '-')
		i++;
	string strTemp;
	while (s[i] != '.')
	{
		strTemp += s[i];
		i++;
	}
	string result1;// lưu khi đổi về nhị phân
	if (strTemp.empty() == false)// nếu phần nguyên là 0 thì chuỗi strTemp rỗng, nên ta kiểm tra nếu chuỗi không rỗng thì mới làm công việc bên dưới
	{
		while (strTemp != "0")
		{
			//Xét số cuối cùng của chuỗi, nếu là số chẵn khi chia cho 2 sẽ dư 0
			if ((strTemp[strTemp.length() - 1] - 48) % 2 == 0)
			{
				result1 += "0";
				i++;
			}
			//Nếu là sổ lẻ, chia 2 sẽ dư 1
			else
			{
				result1 += "1";
				i++;
			}
			//Chia chuỗi cho 2
			strTemp = chia2(strTemp);
			/*if (i > 16)
			{
				throw"Stack Overflow";
			}*/
		}
		reverse(result1.begin(), result1.end());// đảo chuỗi cho đúng thự tự của hệ nhị phân sau khi chia 2
	}
	//--------------------------------------------------
	// đổi phần sau dấu chấm sang dạng nhị phân
	string res;// lưu phần thập phần của số nhập vào
	int countRes = 0;
	while (s[countRes] != '.')
	{
		countRes++;
	}
	countRes++;// Vị trí đầu tiên của phần thập phân ví dụ 0.125 thì countRes ở vị trí của số 1
	for (int i = countRes; i < s.length(); i++)
	{

		res += s[countRes];
		countRes++;
	}
	string temp = "1";
	string result2 = "";
	for (int i = 0; i < res.length(); i++)
	{
		temp += "0";
	}
	bool check = false;
	//kiem tra xem cac phan tu trong chuoi co bang khong ko
	for (int i = 0; i < res.length(); i++)
	{
		if (res[i] != '0')
		{
			check = true;
			break;
		}
	}
	//neu cac phan tu trong chuoi khong cung bang 0 thi thuc hien
	if (check == true)
	{
		int tam = 0;
		int dem = 0;
		for (int i = 0; i < (112 - result1.length()); i++)
		{
			while (res != temp)
			{//nhân 2 cho ph?n th?p phân
				res = multiple2(res);
				if (res.length() < temp.length())
				{
					result2 += "0";
				}
				else
				{
					if (res != temp)
					{
						string tmp = "";
						for (int i = 0; i < res.length() - 1; i++)
						{
							tmp += res[i + 1];//luu bao chuoi tmp cac phan tu cua significand theo thu tu tu phan tu thu 2 den het.
						}
						res = tmp;
						result2 += "1";
					}
				}
				i++;
				if (i == (112 - result1.length()))
				{
					tam = 1;
					break;
				}
			}
			if (res == temp && dem == 0)
			{
				result2 += "1";
				dem = 1;
			}
			if (tam == 1)
				break;
			if (tam != 1)
			{
				result2 += "0";
			}
		}
	}
	else
		result2 += "0";

	int E = 0;
	int position = 0;
	if (result1.empty())
	{
		while (result2[position] != '1')
		{
			position++;
		}
		position++;
		E -= position;
	}
	else
	{
		E = result1.length() - 1;
	}
	int K = 16383;// số thừa K =(2^(15-1))-1
	short int exponent = K + E;//phần mũ
	//Bật bit cho phần Exponent
	if (s[0] == '-')
		data[0] = data[0] | (1 << 15);// nếu là số âm thì sign=1
	for (int i = 0; i < 15; i++)
	{
		data[0] = data[0] | (((exponent >> i) & 1) << i);
	}

	// Phần Significand
	string significand;
	int arrayTemp[112] = { 0 };
	if (result1.empty())
	{
		for (int i = position; i < result2.length(); i++)
			significand += result2[i];
		for(int i=0;i<significand.length();i++)
			arrayTemp[i] = (significand[i] - '0');
	}
	else
	{
		significand += result1 + result2;
		for (int i = 0; i < significand.length() - 1; i++)
		{
			arrayTemp[i] = (significand[i + 1] - '0');
		}
	}
	int count = 0;
	int dataSize = 1;// dataSize[1..7] chứa phần significand=112 bits
	for (int i = 0; i < 112; i++)
	{
		data[dataSize] = data[dataSize] | ((arrayTemp[i]) << (16 - 1 - count));// bật bit cho phần significand
		count++;
		if (count == 16)
		{
			count = 0;
			dataSize++;
		}	

	}
	/*int arrResult[128] = { 0 };
	dataSize = 0;
	count = 0;
	for (int i = 0; i < 128; i++)
	{
		arrResult[i] = (data[dataSize] >> (16 - 1 - count)) & 1;
		count++;
		if (count == 16)
		{
			count = 0;
			dataSize++;
		}
	}
	for (int i = 0; i < 128; i++)
		cout << arrResult[i] << " ";*/
}
//Output
void QFloat::Xuat()
{
	string result;
	int E = 0;// lưu số mũ;
	int exponent = 0;
	int count = 0;
	int dataSize = 0;
	for (int i = 0; i < 15; i++)
	{
		int temp = ((data[0] >> count) & 1);
		if (temp == 1)
			exponent += pow(2, i);
		count++;
	}
	E = exponent - 16383;
	if ((data[0] >> 15) & 1 == 1)// kiểm tra bit đầu để xem là số âm hay dương, âm sign=1, dương sign =0
		result += "-";
	//Xử lý phần nguyên
	count = 0;
	dataSize = 1;
	string temp;
	for (int i = 0; i < 112; i++)
	{
		temp += ((data[dataSize] >> (16 - 1 - count)) & 1) + '0';
		count++;
		if (count == 16)
		{
			count = 0;
			dataSize++;
		}
	}
	if (exponent >= 16383)
	{
		int k = 0;// k giữ giá trị phần nguyên.
		string temp1;// giữ chuỗi nhị phân của phần nguyên
		temp1 += '1';
		for (int i = 0; i < E; i++)
			temp1 += temp[i];// lưu dãy bit của phần nguyên, bên trái dấu chấm.
		reverse(temp1.begin(), temp1.end());
		for (int i = 0; i < temp1.length(); i++)
		{
			if (temp1[i] == '1')
				k += pow(2, i);
		}
		result += numToString(k);
		result += ".";
		string significand;// mảng lưu phần thập phân
		for (int i = E; i < temp.length(); i++)
		{
			significand += temp[i];
		}
		string decimal;// chứa phần thập phân;
		int pos = 1;
		int finalPos = 0;//Vị trí 1 xuất hiện cuối cùng
		for (int i = 0; i < significand.length(); i++)
		{
			if (significand[i] == '1')
			{
				int skip = countSkip(significand, i);
				for (int j = 0; j < skip; j++)
					decimal += "0";
				decimal = plusNumInStr(decimal, myFivePow(pos));
				finalPos = pos;
			}
			pos++;
		}

		int tmp = decimal.length();
		int flag = finalPos - tmp;// tinh số con 0 phía sau dấu chấm  vd0.009375 có 2 con 0.
		if (flag > 0)
			for (int i = 1; i <= flag; i++)
				result += "0";
		result += decimal;
	}
	
	else//E<0
	{
		E *= -1;
		result += "0";
		result += ".";
		string temp1;
		for (int i = 0; i < E - 1; i++)
			temp1 += "0";
		temp1 += "1";
		if (temp[0] !='0')
		{
			for (int i = 0; i < temp.length(); i++)
				temp1 += temp[i];
		}
		string significand;// mảng lưu phần thập phân
		for (int i = 0; i < temp1.length(); i++)
		{
			significand += temp1[i];
		}
		string decimal ;// chứa phần thập phân;
		int pos = 1;
		int finalPos = 0;//Vị trí 1 xuất hiện cuối cùng
		for (int i = 0; i < significand.length(); i++)
		{
			if (significand[i] == '1')
			{
				int skip = countSkip(significand, i);
				for (int j = 0; j < skip; j++)
					decimal += "0";
				decimal =plusNumInStr(decimal, myFivePow(pos));
				finalPos = pos;
			}
			pos++;
		}
		
		int tmp = decimal.length();
		int flag = finalPos - tmp ;// tinh số con 0 phía sau dấu chấm  vd0.009375 có 2 con 0.
		if (flag > 0)
			for (int i = 1; i <= flag; i++)
				result += "0";
		result += decimal;
	}
	cout << result << endl;
}
//Bin to Dec
QFloat QFloat::binToDec(string s)
{
	int count = 0;
	int dataSize = 0;// dataSize[1..7] ch?a ph?n significand=112 bits
	for (int i = 0; i < 128; i++)
	{
		data[dataSize] = data[dataSize] | ((s[i] - '0') << (16 - 1 - count));// b?t bit cho ph?n significand
		count++;
		if (count == 16)
		{
			count = 0;
			dataSize++;
		}
	}
	return *this;
}
//Dec to Bin
string QFloat::decToBin(QFloat x)
{
	string result;
	int arrResult[128] = { 0 };
	int xSize = 0;
	int count = 0;
	for (int i = 0; i < 128; i++)
	{
		result += ((x.data[xSize] >> (16 - 1 - count)) & 1) + '0';
		count++;
		if (count == 16)
		{
			count = 0;
			xSize++;
		}
	}
	return result;
}
//Support funciton
string numToString(int k)
{
	string res;
	while (k != 0)
	{
		int temp = k % 10;
		res += (temp + '0');
		k /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}
int countSkip(string s, int k)
{
	int flag = 1;
	if (k == 0)
		return 0;
	for (int i = k - 1; i >= 0; i--)
	{
		if (s[i] == '1')
			return (k - i);
	}
	return 0;
}
string myTenPow(int n)
{
	string temp = "10";
	if (n == 0)
		return "1";
	if (n == 1)
		return "10";
	for (int i = 0; i < n - 1; i++)
	{
		temp += "0";
	}
	return temp;
}
string myFivePow(int n)
{

	string temp = "5";
	if (n == 0)
		return "1";
	if (n == 1)
		return "5";
	for (int i = 0; i < n - 1; i++)
	{
		temp = multiple5(temp);
	}
	return temp;
}
string multiple5(string s)
{
	int temp = 0, carry = 0;;
	int _length = s.length();
	int a_size = _length + 1;
	int *a = new int[a_size];
	string result;
	for (int i = 0; i < a_size; i++)
		a[i] = 0;
	for (int i = _length - 1; i >= 0; i--)
	{
		temp = (s[i] - '0') * 5;
		if (carry != 0)
			temp+=carry;
		if (temp > 9)
			carry = temp / 10;
		else
			carry = 0;
		a[i + 1] += temp % 10;

	}
	if (carry != 0)
	{
		a[0] =carry;
	}
	else
	{
		for (int i = 0; i < a_size - 1; i++)
			a[i] = a[i + 1];
		a_size--;
	}
	for (int i = 0; i < a_size; i++)
	{
		result += (a[i] + '0');
	}
	return result;
}
QFloat::QFloat()
{
	for (int i = 0; i < 8; i++)
		data[i] = 0;
}
QFloat::~QFloat()
{

}
