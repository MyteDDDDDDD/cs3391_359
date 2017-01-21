#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;



int accu = 0;// accumulator ,0-255
int pc = 0;// program counter ,0-32
int memory[33][9] = { 0 };//32 byte array to store instructions and initialed to be 0;
int ir = 0;// integer number of ir, ir is short of instruction register ,0-7
string smemory[33];


void STA() { // store the value of the accu into memory byte x
	int temp = 0;//define all bits of temp to 0
	for (int i = 0; i < 5; i++) { //temp records the value of xxxxx
		if (memory[pc][i + 3] == 1)
			temp |= (1 << (4 - i));
	}
	for (int i = 0; i < 8; i++) {// stort accu into memory[temp][]
		if (accu&(1 << (7 - i)))
			memory[temp][i] = 1;
		else
			memory[temp][i] = 0;
	}
	pc++;
}

void LDA() { //LDA load the value of memory byte x into the accu
	accu = 0; // clear accu first
	int temp = 0;//define all bits of temp to 0
	for (int i = 0; i < 5; i++) { //temp records the value of xxxxx
		if (memory[pc][i + 3] == 1)
			temp |= (1 << (4 - i));
	}
	for (int i = 0; i < 8; i++) { //load the value in memory[temp][] to accu
		if (memory[temp][i] == 1)
			accu |= (1 << (7 - i));
	}
	pc++;
}

void BEQ() { //BEQ if the value of the accu if 0 ,load the value x into the pc
	if (accu == 0) {
		int temp = 0;//define all bits of temp to 0
		for (int i = 0; i < 5; i++) { //temp records the value of xxxxx
			if (memory[pc][i + 3] == 1)
				temp |= (1 << (4 - i));
		}
		pc = temp; //assign the value of temp to pc
	}
}

void NOP() { //NOP no operation
	pc++;
}

void DEC() { // DEC substract 1 from the accu
	accu -= 1;
	if (accu < 0)
		accu = 255;
	pc++;
}

void INC() { //INC add 1 to the accu
	accu += 1;
	if (accu > 255)
		accu = 0;
	pc++;
}

void JMP() { //JMP load the value x into the pc
	int temp = 0;//define all bits of temp to 0
	for (int i = 0; i < 5; i++) { //temp records the value of xxxxx
		if (memory[pc][i + 3] == 1)
			temp |= (1 << (4 - i));
	}
	pc = temp; //assign the value of temp to pc
}

int main() {
	while (true) { // read 32-bit and record in smemory[]
		for (int i = 0; i < 32; i++) {
			getline(cin, smemory[i]);
			if (cin.eof()) {
				return false;
				continue;
			}

		}

		for (int i = 0; i < 32; i++) { // convert smemory[] to memroy[][]
			for (int j = 0; j < 8; j++)
				memory[i][j] = smemory[i].at(j) - '0'; //convert char to int
		}

		while (ir != 7) {
			ir = 0;// clear ir first
			for (int i = 0; i < 3; i++) {
				if (memory[pc][i] == 1)
					ir |= (1 << (2 - i));
			}

			switch (ir) {
			case 0: //STA store the value of the accu into memory byte x
				STA();
				break;
			case 1: //LDA load the value of memory byte x into the accu
				LDA();
				break;
			case 2: //BEQ if the value of the accu if 0 ,load the value x into the pc
				BEQ();
				break;
			case 3: //NOP no operation
				NOP();
				break;
			case 4: // DEC substract 1 from the accu
				DEC();
				break;
			case 5: //INC add 1 to the accu
				INC();
				break;
			case 6: //JMP load the value x into the pc
				JMP();
				break;
			case 7: //HLT terminate program
			{
				for (int i = 0; i < 8; i++) { //print accu
					if (accu&(1 << (7 - i)))
						cout << "1";
					else
						cout << "0";
				}
				continue;
			}
			default:
				return false;
			}
		}
		accu = 0;// accumulator ,0-255
		pc = 0;// program counter ,0-32
			   //memory[][] = { 0 };//32 byte array to store instructions and initialed to be 0;
		ir = 0;// integer number of ir, ir is short of instruction register ,0-7
		if (cin.eof())
			return false;
	}

	return 0;
}
/*sample input
00111110
10100000
01010000
11100000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00111111
10000000
00000010
11000010
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
11111111
10001001
*/
