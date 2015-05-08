#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Data.h"
using namespace std;

int count_index();
void input_grammar(Data index[]);
void lltable(Data index[], int max);

int main(void) {
	int max = count_index();
	Data index[max];
	input_grammar(index);
	lltable(index, max);

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
	int count = -1, position = 0, check = 0;

	if(fp == NULL) {
		cout << "Can not find file." << endl;
	}
	else {
		string line;

		while(getline(fp, line)) {
			if(line.at(0) != '\t') {
				if(count != -1) {
					index[count].set_max(position);
					index[count].set_check_max(check);
				}

				count++;
				position = 0;
				check = 0;
				index[count].set_name(line);
			}
			else {
				istringstream fp_word(line);
				string word;

				while(fp_word >> word) {
					index[count].set_subdata(position, word);
					index[count].set_check(position, check);
					position++;
				}
				check++;
			}
		}

		index[count].set_max(position);
		index[count].set_check_max(check);
	}

	fp.close();
}

void lltable(Data index[], int max) {
	Data first[max], follow[max];
	ifstream fp("set.txt");

	string line;
	getline(fp, line);

	for(int i = 0; i < max; i++) {
		getline(fp, line);
		istringstream fp_word(line);
		string word;
		int count = 0;

		fp_word >> word;
		first[i].set_name(word);
		fp_word >> word;
		
		while(fp_word >> word) {
			first[i].set_subdata(count, word);
			count++;
		}
		first[i].set_max(count);
	}

	getline(fp, line);
	getline(fp, line);
	for(int i = 0; i < max; i++) {
		getline(fp, line);
 		istringstream fp_word(line);
		string word;
		int count = 0;

		fp_word >> word;
		follow[i].set_name(word);
		fp_word >> word;

		while(fp_word >> word) {
			follow[i].set_subdata(count, word);
			count++;
		}
		follow[i].set_max(count);
	}

	fp.close();
	ofstream fout("lltable.txt");
	fout.setf(ios::left);

	fout << "lltable" << endl;
	for(int i = 0; i < max; i++) {
		int check[ first[i].get_max() ];
		for(int j = 0; j < first[i].get_max(); j++) {
			if(first[i].at(j) == "epsilon") {
			}
			else {
				fout << setw(20) << first[i].get() << "| ";
				fout << setw(20) << first[i].at(j) << "| ";
				fout << index[i].get() << "->";
				fout << index[i].at(0) << " ";
				fout << endl;
			}
		}
	}

	fout.close();
}
