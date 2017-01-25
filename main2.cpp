#include <iostream>

using namespace std;


int accu=0;
int pc=0;
int ir=0;
int memory[33] = { 0 };


void STA() { // store the value of the accu into memory byte x
	int temp1 = 0;//record xxxxx,binary
	int temp2 = 0;//record xxxxx,integer
	int temp3 = 0;//record accu,integer
	temp1 = memory[pc] % 100000;
	for (int i = 0; i < 5; i++) {
		if(temp1%10==1)
			temp2 |= (1 << i);
		temp1 /= 10;
	}
	temp3 = accu;
	for (int i = 0; i < 8; i++) {
		if (temp3 % 10 == 1)
			memory[temp2] |= (1 << i);
		temp3 /= 10;
	}
	cout << "STA" << endl;
	pc++;
}

void LDA() { //LDA load the value of memory byte x into the accu
	accu = 0; // clear accu first
	int temp1 = 0;//record xxxxx,binary
	int temp2 = 0;//record xxxxx,integer
	int temp3 = 0;//record memomry[i],integer
	temp1 = memory[pc] % 100000;
	cout << "temp1: " << temp1 << endl;
	for (int i = 0; i < 5; i++) {
		if (temp1 % 10 == 1)
			temp2 |= (1 << i);
		temp1 /= 10;
	}
	temp3 = memory[temp2];
	for (int i = 0; i < 8; i++) {
		if (temp3 % 10 == 1)
			accu |= (1 << i);
		temp3 /= 10;
	}
	cout << "accu: " << accu << endl;
	cout << "LDA" << endl;
	pc++;
}

void BEQ() { //BEQ if the value of the accu if 0 ,load the value x into the pc
	if (accu == 0) {
		int temp1 = 0;//record xxxxx,binary
		int temp2 = 0;//record xxxxx,integer

		temp1 = memory[pc] % 100000;
		for (int i = 0; i < 5; i++) {
			if (temp1 % 10 == 1)
				temp2 |= (1 << i);
			temp1 /= 10;
		}
		pc = temp2; //assign the value of temp to pc
	}
	cout << "BEQ" << endl;
}

void NOP() { //NOP no operation
	pc++;
	cout << "NOP" << endl;
}

void DEC() { // DEC substract 1 from the accu
	accu -= 1;
	if (accu < 0)
		accu = 255;
	pc++;
	cout << "DEC" << endl;
}

void INC() { //INC add 1 to the accu
	accu += 1;
	if (accu > 255)
		accu = 0;
	pc++;
	cout << "INC" << endl;
}

void JMP() { //JMP load the value x into the pc
	int temp1 = 0;//record xxxxx,binary
	int temp2 = 0;//record xxxxx,integer

	temp1 = memory[pc] % 100000;
	for (int i = 0; i < 5; i++) {
		if (temp1 % 10 == 1)
			temp2 |= (1 << i);
		temp1 /= 10;
	}
	pc = temp2; //assign the value of temp to pc
	cout << "JMP" << endl;
}

int main() {
	while (true) {

		for (int i = 0; i < 32; i++) {
			cin >> memory[i];
			if (cin.eof()) {
				return false;
				continue;
			}
				
		}

		while (ir != 111) {
			ir = memory[0]/100000;

			switch(ir){
			case 0: //STA store the value of the accu into memory byte x
				STA();
				break;
			case 1: //LDA load the value of memory byte x into the accu
				LDA();
				break;
			case 10: //BEQ if the value of the accu if 0 ,load the value x into the pc
				BEQ();
				break;
			case 11: //NOP no operation
				NOP();
				break;
			case 100: // DEC substract 1 from the accu
				DEC();
				break;
			case 101: //INC add 1 to the accu
				INC();
				break;
			case 110: //JMP load the value x into the pc
				JMP();
				break;
			case 111:{ //HLT terminate program
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
		ir = 0;// integer number of ir, ir is short of instruction register ,
	}

	
	return 0;
}
