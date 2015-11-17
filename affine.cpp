#include <iostream>
#include <string>		// string
#include <algorithm>	// transform
#include <fstream>		// file operation
#include <cctype>		// isalpha
#include <map>			// map
#include <iomanip>		// setprecision
using namespace std;

std::map<char, int> pcounter;
std::map<char, int> ccounter;
int total = 0;

int gcd(int n1, int n2) {
	if ( n2 == 0 )
		return n1;
	else
		return gcd(n2, n1 % n2);
}

bool checkKey(int a, int b) {
	if (a < 0 || a > 25 || b < 0 || b > 25)
		return false;
	if ( gcd(a, 26) != 1 )
		return false;
	return true;
}

int reverse(const int a) {
	int c;
	for (int i = 1; i <= 25; i += 2) {
		if ( (i * a) % 26 == 1 ) {
			c = i;
			break;
		}
	}
	return c;
}

void encrpt(const string& pt, string& ct, const int a, const int b) {
	for (int i = 0; i < pt.size(); i++) {
		// 判断当前字符是否是字母
		if ( !isalpha(pt[i]) ) {
			ct += pt[i];
			continue;
		}
		else {
			total++;	// 记录字符个数
			pcounter[pt[i]] += 1;	// 记录明文中的字母频数
			char c = (a * (pt[i] - 'a') + b) % 26 + 'a';
			ccounter[c] += 1;		// 记录明文中的字母频数
			ct += c;
		}
	}
}

void decrpt(const string& ct, string& pt, const int a, const int b) {
	// 求a的逆
	int c = reverse(a);
	for (int i = 0; i < ct.size(); i++) {
		// 判断当前字符是否是字母
		if ( !isalpha(ct[i]) ) {
			pt += ct[i];
			continue;
		}
		else {
			char t;
			int n = (c * ((ct[i] - 'a') - b)) % 26;
			// 出现负值，加上26
			if (n < 0)
				t = n + 26 + 'a';
			else
				t = n + 'a';
			pt += t;
		}
	}
}

int main () {
	// 打开相应的文件
	ifstream pt;	// 明文
	pt.open("plaintext.txt", fstream::in);
	ofstream ct;	// 密文
	ct.open("cipher.txt", fstream::out);
	// 接收用户输入的密钥对
	int a, b;
	do {
		cin >> a >> b;
	} while ( !checkKey(a, b) );

	while (pt) {
		string p;
		string plainText;
		string cipherText;
		// 从文件中读取字符，并转成小写
		getline(pt, p);
		plainText.resize(p.size());
		transform(p.begin(), p.end(), plainText.begin(), ::tolower);
		// 加密信息，并输入到文件中
		encrpt(plainText, cipherText, a, b);
		ct << cipherText << "\r\n";
	}

	pt.close();
	ct.close();

	// 打开密文和result.txt文件
	ifstream ct1;
	ct1.open("cipher.txt", fstream::in);
	ofstream result;
	result.open("result.txt", fstream::out);
	while (ct1) {
		string plainText;
		string cipherText;
		// 从密文中读取字符，解密，然后存入result.txt文件中
		getline(ct1, cipherText);
		decrpt(cipherText, plainText, a, b);
		result << plainText << "\r\n";
	}

	ct1.close();
	result.close();

	// 输出统计结果
	cout << "total number: " << total << endl;

	cout << "--------------------" << endl;
	for (char c = 'a'; c <= 'z'; c++) {
		cout << c << "-" << pcounter[c] << '\t' << \
			setprecision(3) << float(pcounter[c])/total * 100 << '\t';
		if ( (c-'a'+1) % 3 == 0 )
			cout << endl;
	}

	cout << "\n--------------------" << endl;
	for (char c = 'a'; c <= 'z'; c++) {
		cout << c << "-" << ccounter[c] << '\t' << \
			setprecision(3) << float(ccounter[c])/total * 100 << '\t';
		if ( (c-'a'+1) % 3 == 0 )
			cout << endl;
	}
	return 0;
}

/*
class CryptoSys {
public:
	//CryptoSys() = default;
	CryptoSys(const string& pt): plainText(pt) {}
	// prevent copy and assignment operations.
	//CryptoSys(const CryptoSys&) = delete;
	//CryptoSys& operator= (const CryptoSys&) = delete;
	bool getPrivateKey(const int a, const int b) {
		if ( !checkKey(a, b) )
			return false;
		else {
			this->a = a;
			this->b = b;
			return true;
		}
	}
	void encrpt() {

	}
	const string cipher() const {
		return cipherText;
	}
private:
	bool checkKey() {};
private:
	const string plainText;
	string cipherText;
	int a, b;
};*/