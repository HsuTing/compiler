#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include "Data.h"
using namespace std;

int count_index();
void input_grammar();

int main(void) {
	cout << count_index() << endl;
	input_grammar();

	return 0;
}

int count_index() {
	ifstream fp("grammar.txt");
	int count = 0;

	if(fp == NULL) {
		cout << "Can not find file." << endl;
	}
	else {
		string line;

		while(getline(fp, line)) {
			if(line.at(0)  != '\t') {
				count++;
			}
		}
	}

	fp.close();
	return count;
}

void input_grammar() {
	ifstream fp("grammar.txt");

	if(fp == NULL) {
		cout << "Can not find file." << endl;
	}
	else {
		string line;

		while(getline(fp, line)) {
			cout << line.at(0) << endl;
		}
	}

	fp.close();
}
