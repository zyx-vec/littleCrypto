#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

vector<char> table[26];
string key;
string plaintext;
string ciphertext;

void generate_table() {
	// above main line
	char data;
	for (int i = 0; i < 26; i++) {
		data = 'A' + i;
		for (int j = 0; j <= i; j++) {
			table[j].push_back(data);
		}
	}
	// under main line
	for (int i = 1; i < 26; i++) {
		data = 'A' + i - 1;
		for (int j = i; j < 26; j++) {
			table[j].push_back(data);
		}
	}
}

void encrypt() {
	cout << "Input key: " << endl;
	cin >> key;
	cout << "Input plaintext: " << endl;
	cin >> plaintext;

	transform(key.begin(), key.end(), key.begin(), ::toupper);
	//cout << key << endl;
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);
	//cout << plaintext << endl;

	int size = plaintext.size();
	int keySize = key.size();
	for (int i = 0; i < size; i++) {
		ciphertext += table[ key[i%keySize]-'A' ][ plaintext[i]-'A' ];
	}

	cout << "ciphertext is: " << endl;
	cout << ciphertext << endl;
}

void decrypt() {
	cout << "Input key: " << endl;
	cin >> key;
	cout << "Input ciphertext: " << endl;
	cin >> ciphertext;

	transform(key.begin(), key.end(), key.begin(), ::toupper);
	//cout << key << endl;
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);
	//cout << plaintext << endl;

	int size = ciphertext.size();
	int keySize = key.size();
	for (int i = 0; i < size; i++) {
		int row = key[ i%keySize ];
		if (ciphertext[i] >= row) {
			plaintext += ciphertext[i] - row + 'A';
		} else {
			plaintext += ciphertext[i] - row + 26 + 'A';
		}
	}

	cout << "plaintext is: " << endl;
	cout << plaintext << endl;
}

int main () {
	generate_table();
	int mode;
	cout << "Select mode (0 -- e, 1 -- d): " << endl;
	cin >> mode;

	switch (mode) {
		case 0:	encrypt(); break;
		case 1: decrypt(); break;
		default: cout << "Wrong selection!!!" << endl;
	}

	return 0;
}
