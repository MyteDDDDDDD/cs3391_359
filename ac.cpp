#include<iostream>
#include<string>
using namespace std;

int memory[33];

int strToInt(string s) {
	int result = 0;
	for (int i = 0; i < 8; i++) {
		if (s[7 - i] == '1')
			result += (1 << i);
	}
	return result;
}
string convertToBinary(int n) {
	

	string s = "00000000";
	int temp;
	for (int i = 0; i < 8; i++) {
		if (n >> (7 - i) & 1)
			s[i] = '1';
	}
	return s;


}

void cal() {
	int accu = 0;
	int pc = 0;
	int ins = 0;
	int addr = 0;

	while (true) {

		addr = memory[pc] % 32;
		ins = memory[pc++] >> 5;
		pc %= 32;

		if (ins == 0) {
			memory[addr] = accu;
		}
		else if (ins == 1) {
			accu = memory[addr];
		}
		else if (ins == 2) {
			if (accu == 0) {
				pc = addr;
			}

		}
		else if (ins == 3) {
		}
		else if (ins == 4) {
			accu--;
			if (accu < 0)
				accu = 255;
		}
		else if (ins == 5) {
			accu++;
			if (accu >255)
				accu = 0;
		}
		else if (ins == 6) {
			pc = addr;
		}
		else
			break;
	}

	cout << convertToBinary(accu) << endl;
}

int main() {
	string s;
	getline(cin, s);
	while (!cin.eof()) {
		memory[0] = strToInt(s);
		for (int i = 1; i < 32; i++) {
			getline(cin, s);
			memory[i] = strToInt(s);
		}
		cal();
		getline(cin, s);
	}

	return 0;
}
