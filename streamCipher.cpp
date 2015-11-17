#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
int a[40];

void keyGen() {
	for (int i = 0; i < 31; i++) {
		a[i+5] = (a[i+3] + a[i]) % 2;
	}
	
	cout << "key stream: " << endl;
	for (int i = 0; i < 31; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int getMask() {
	static int pos = 0;
	int mask = 0;
	for (int i = 0; i < 8; i++) {
		mask += a[pos] << (7-i);
		//cout << a[pos] << " ";
		pos++;
		if (pos == 31) {	// 越界了
			pos = 0;
		}
	}
	//cout << pos << ":" << mask << endl;
	return mask;
}

void encrypt() {
	ifstream is;
	is.open("plain.txt", ifstream::in);
	ofstream os;
	os.open("cipher.txt", ifstream::out);
	
	char c;
	while (is.get(c)) {
		char data = c ^ getMask();
		os << data;
	}
	is.close();
	os.close();
}

void decrypt() {
	ifstream is;
	is.open("cipher.txt", ifstream::in);
	ofstream os;
	os.open("result.txt", ifstream::out);
	
	char c;
	while (is.get(c)) {
		char data = c ^ getMask();
		os << data;
	}
	is.close();
	os.close();
}

int main () {
	int sel;
	cout << "Please input initial key: " << endl;
	for (int i = 0; i < 5; i++) {
		cin >> a[i];
	}
	
	keyGen();
	
	cout << "select: 1 for encrypt, 2 for decrypt" << endl;
	cin >> sel;
	switch (sel) {
		case 1:	encrypt(); break;
		case 2:	decrypt(); break;
		default: cout << "Wrong selection!" << endl;
	}
	return 0;
}

/*
	for (int i = 0; i < 10; i++) {
		getMask();
	}*/






