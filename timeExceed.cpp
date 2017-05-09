Dear MyteD,

Your Submission (ID: 35109) for the problem 359 - Simple Computers (CO assignment?) has been judged with verdict Time Limit Exceeded.

Compiler:	C++ 11, flag: -static -std=c++0x
Runtime:	1 seconds
Memory:	1,888 KBs



Best regards,
Administrator
CityU CS OnlineJudge System

/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 35109
 * Submitted at:  2017-05-09 16:27:43
 *
 * User ID:       312
 * Username:      54018358
 * Problem ID:    359
 * Problem Name:  Simple Computers (CO assignment?)
 */

#include<iostream>
#include <string>
#include <math.h>    
using namespace std;

string memory[33];

string convertToBinary(int n){
	if (n == 0)
		return "0";

	if (n == 1) {
		return "1";
	}
	while (n > 1) {
		if (n % 2 == 0) {
			return (convertToBinary(n / 2) + "0");
		}
		else {
			return (convertToBinary(n / 2) + "1");
		}
	}
	
}

int convertToDecimal(string n) {
	int temp = stoi(n);
	int count = 0;
	int sum = 0;

	while (temp > 0) {
		if (temp % 10 == 0) {
			temp /= 10;
			count++;
		}
		else {
			temp /= 10;
			sum += pow(2, count);
			count++;
		}
	}
	return sum;
}

void STA(string location,int accu) {
	int loc = convertToDecimal(location);
	memory[loc] = convertToBinary(accu);
}

int LDA(string location) {
	int loc = convertToDecimal(location);
	int num =convertToDecimal(memory[loc]);
	return num;
}

string simpCom() {
	int accu = 0;
	int pc = 0;
	string ins;
	while (pc >= 0) {
		ins = memory[pc].substr(0,3);
		if (ins == "000") {
			
			STA(memory[pc].substr(3, 5), accu);
			pc++;
		}
		else if (ins == "001") {
			
			accu = LDA(memory[pc].substr(3, 5));
			pc++;
		}
		else if (ins == "010") {
			if (accu == 0) {
				pc = convertToDecimal(memory[pc].substr(3, 5));
			}
			else {
				pc++;
			}
		}
		else if (ins == "011") {
			pc++;
		}
		else if (ins == "100") {
			
			accu -= 1;
			pc++;
		}
		else if (ins == "101") {
			accu += 1;
			if (accu >= 256) {
				accu = 0;
			}
			pc++;
		}
		else if (ins == "110") {
			
			pc = convertToDecimal(memory[pc].substr(3, 5));
		}
		else if(ins=="111"){
			break;
		}
	}
	return convertToBinary(accu);
}

int main() {
	string temp;
	getline(cin, temp);
	while (!cin.eof()) {
		memory[0] = temp;
		for (int i = 1; i < 32; i++) {
			getline(cin, memory[i]);
		}
		cout<<simpCom();
		getline(cin, temp);
	}

	return 0;
}
