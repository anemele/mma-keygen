#include <iostream>
#include <string>

using namespace std;

// number for 11.2
// int magicNumbers[] = {10690, 10744, 12251, 17649, 27280, 42041, 42635, 53798, 56180, 58535, 61041};

// number for 12.0
int magicNumbers[] = { 10690, 12251, 17649, 24816, 33360, 35944, 36412, 42041, 42635, 44011, 53799, 56181, 58536, 59222, 61041 };

int f1(int n, int byte, int c)
{
	int bit;
	for (int bitIndex = 0; bitIndex <= 7; bitIndex++)
	{
		bit = (byte >> bitIndex) & 1;
		if (bit + ((n - bit) & ~1) == n)
		{
			n = (n - bit) >> 1;
		}
		else
		{
			n = ((c - bit) ^ n) >> 1;
		}
	}
	return n;
}

string genPassword(string str, int h)
{
	int hash = h;
	for (int byteIndex = str.length() - 1; byteIndex >= 0; byteIndex--)
	{
		hash = f1(hash, (int)str[byteIndex], 0x105C3);
	}
	int n1 = 0;
	while (f1(f1(hash, n1 & 0xFF, 0x105C3), n1 >> 8, 0x105C3) != 0xA5B6)
	{
		if (++n1 >= 0xFFFF)
		{
			cerr << ("Failed to find a key!");
			return "";
		}
	}
	n1 = int(((n1 + 0x72FA) & 0xFFFF) * 99999.0 / 0xFFFF);
	string n1str = "0000" + to_string(n1);
	n1str = n1str.substr(n1str.length() - 5, 5);

	int temp = stoi(n1str.substr(0, n1str.length() - 3) + n1str.substr(n1str.length() - 2, 2) + n1str.substr(n1str.length() - 3, 1));
	temp = int((temp / 99999.0) * 0xFFFF) + 1;
	temp = f1(f1(0, temp & 0xFF, 0x1064B), temp >> 8, 0x1064B);

	for (int byteIndex = str.length() - 1; byteIndex >= 0; byteIndex--)
	{
		temp = f1(temp, (int)str[byteIndex], 0x1064B);
	}

	int n2 = 0;
	while (f1(f1(temp, n2 & 0xFF, 0x1064B), n2 >> 8, 0x1064B) != 0xA5B6)
	{
		if (++n2 >= 0xFFFF)
		{
			cerr << ("Failed to find a key!");
			return "";
		}
	}
	n2 = int((n2 & 0xFFFF) * 99999.0 / 0xFFFF);
	string n2str = "0000" + to_string(n2);
	n2str = n2str.substr(n2str.length() - 5, 5);

	char pass[] = {
		n2str[3],
		n1str[3],
		n1str[1],
		n1str[0],
		'-',
		n2str[4],
		n1str[2],
		n2str[0],
		'-',
		n2str[2],
		n1str[4],
		n2str[1] };
	const string suffix = "::1";
	return string(pass).substr(0, 12) + suffix;
}

int main(int argc, const char* argv[])
{
	cout << "Mathematica 12.0 keygen" << endl;
	cout << "Please input your math ID: " << endl;
	string mathID;
	cin >> mathID;
	string activationKey = "1234-4321-123456";
	string str = mathID + "$1&" + activationKey;
	cout << "Activation Key: " << activationKey << endl;
	cout << "Pick any password from below:" << endl;
	for (auto h : magicNumbers)
	{
		cout << genPassword(str, h) << endl;
	}
	return 0;
}
