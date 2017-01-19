#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


int binaryToDecimal(long b) {
	int sum = 0, i = 0, remainder;
	while (b != 0) {
		remainder = b % 10;
		if (remainder == 1)
			sum |= (1 << i);
		i++;
		b /= 10;
	}
	return sum;
}


void STA(long accu, long pc,long memory[]) { // store the value of the accu into memory byte x
	memory[binaryToDecimal(pc)] = accu; 
	pc++;
}

void LDA(long accu,long pc,long memory[]) { //LDA load the value of memory byte x into the accu
	accu = memory[binaryToDecimal(pc) ];
	pc++;
}

void BEQ(long accu,long pc,long memory[]) { //BEQ if the value of the accu if 0 ,load the value x into the pc
	if (accu == 00000000)
		pc = memory[(binaryToDecimal(pc) ) % 100000];
}

void NOP(long pc) { //NOP no operation
	pc++;
}

void DEC(long accu, long pc) { // DEC substract 1 from the accu
	accu -= 1;
	pc++;
}

void INC(long accu, long pc) { //INC add 1 to the accu
	accu += 1;
	pc++;
}

void JMP(long pc, long memory[]) { //JMP load the value x into the pc
	pc = memory[(binaryToDecimal(pc) ) % 100000];
}





int main() {
	long accu=00000000;// accumulator ,binary format
	long pc=0;// program counter ,binary format, 00000 to 11111
	long memory[32] = { 00000000 };//32 byte array to store instructions and initialed to be 0;
	long temp;
	int count = 0;
	cin >> temp; 
	memory[0] = temp;
	while (!cin.eof()) {
		memory[count]=temp;
		count++;
		cin >> temp;
	}
	cout << "ok" << endl;
	long ir = memory[binaryToDecimal(pc) ] / 100000;// instruction register
	while (true) {
		switch (ir) {
		case 000: //STA store the value of the accu into memory byte x
			STA(accu, pc, memory);
			break;
		case 001: //LDA load the value of memory byte x into the accu
			LDA(accu, pc, memory);
			break;
		case 010: //BEQ if the value of the accu if 0 ,load the value x into the pc
			BEQ(accu, pc, memory);
			break;
		case 011: //NOP no operation
			NOP(pc);
			break;
		case 100: // DEC substract 1 from the accu
			DEC(accu, pc);
			break;
		case 101: //INC add 1 to the accu
			INC(accu, pc);
			break;
		case 110: //JMP load the value x into the pc
			JMP(pc, memory);
			break;
		case 111: //HLT terminate program
			continue;
		default:
			cout << "error";
		}
	}
	cout << accu<<endl;

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
