#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include "Data.h"
using namespace std;

int count_index();
void input_grammar(Data index[]);

int main(void) {
	int max = count_index();
	Data index[max];
	input_grammar(index);

	for(int i = 0; i < max; i++) {
		cout << index[i].get() << ": ";
		for(int j = 0; j < index[i].get_max(); j++) {
			cout << index[i].at(j) << " ";
		}
		cout << endl;
	}

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

void input_grammar(Data index[]) {
	ifstream fp("grammar.txt");
	int count = -1, position = 0;

	if(fp == NULL) {
		cout << "Can not find file." << endl;
	}
	else {
		string line;

		while(getline(fp, line)) {
			if(line.at(0) != '\t') {
				if(count != -1) {
					index[count].set_max(position);
				}

				count++;
				position = 0;
				index[count].set_name(line);
			}
			else {
				istringstream fp_word(line);
				string word;

				while(fp_word >> word) {
					index[count].set_subdata(position, word);
					position++;
				}
			}
		}

		index[count].set_max(position);
	}

	fp.close();
}
