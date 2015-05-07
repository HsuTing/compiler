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
int first_check(Data index[], int max, string name);
void find(Data index[], int max, string name);
void find(Data index[], Data tempdata[], int max, string name, int position);
void first(Data index[], int max);
void find_follow(Data index[], Data tempdata[], int max, string name, int position);
void follow(Data index[], Data tempdata[], int max);

int main(void) {
	int max = count_index();
	Data index[max], tempdata[max];
	input_grammar(index);
	first(index, max);

	for(int i = 0; i < max; i++) {
		tempdata[i].set_name(index[i].get());
		find_follow(index, tempdata, max, index[i].get(), i);
	}

	/*for(int i = 0; i < max; i++) {
		cout << index[i].get() << ": ";
		for(int j = 0; j < index[i].get_max(); j++) {
			cout << index[i].find(j) << " ";
		}
		cout << endl;

		cout << index[i].get() << ": ";
		for(int j = 0; j < index[i].get_max(); j++) {
			cout << index[i].at(j) << " ";
		}
		cout << endl;

		cout << index[i].get_check_max() << endl;
	}*/

	for(int i = 0; i < max; i++) {
		cout << tempdata[i].get() << ": ";
		for(int j = 0; j < tempdata[i].get_max(); j++) {
			cout << tempdata[i].at(j) << " ";
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

int first_check(Data index[], int max, string name) {
	for(int i = 0; i < max; i++) {
		if(index[i].get() == name) {
			return i;
		}
	}
	return -1;
}

void find(Data index[], int max, string name) {
	int temp = first_check(index, max, name), check = 0;

	if(temp == -1) {
		ofstream fp("set.txt", ios::app);
		fp << name << " ";
		fp.close();
		return;
	}
	else {
		for(int i = 0; i < index[temp].get_check_max(); i++) {
			for(int j = 0; j < index[temp].get_max(); j++) {
				if(index[temp].find(j) == i) {
					find(index, max, index[temp].at(j));
					break;
				}
			}
		}
	}
}

void find(Data index[], Data tempdata[], int max, string name, int position) {
	int temp = first_check(index, max, name), check = 0;

	if(temp == -1) {
		if(name == "epsilon") {
			return;
		}

		temp = tempdata[position].get_max();
		tempdata[position].set_subdata(temp, name);
		tempdata[position].set_max(temp + 1);
		return;
	}
	else {
		for(int i = 0; i < index[temp].get_check_max(); i++) {
			for(int j = 0; j < index[temp].get_max(); j++) {
				if(index[temp].find(j) == i) {
					find(index, tempdata, max, index[temp].at(j), position);
					break;
				}
			}
		}
	}
}

void first(Data index[], int max) {
	ofstream fp("set.txt");
	fp << "First" << endl;
	fp.close();

	for(int i = 0; i < max; i++) {
		ofstream fp1("set.txt", ios::app);
		fp1.setf(ios::left);
		fp1 << setw(20) << index[i].get() << ": ";
		fp1.close();

		for(int j = 0; j < index[i].get_check_max(); j++) {
			for(int k = 0; k < index[i].get_max(); k++) {
				if(index[i].find(k) == j) {
					find(index, max, index[i].at(k));
					break;
				}
			}
		}

		ofstream fp2("set.txt", ios::app);
		fp2 << endl;
		fp2.close();
	}
}

void find_follow(Data index[], Data tempdata[], int max, string name, int position) {
	for(int i = 0; i < max; i++) {
		for(int j = 0; j < index[i].get_max(); j++) {
			if(index[i].at(j) == name) {
				if(index[i].find(j + 1) != index[i].find(j)) {
				}
				else if(index[i].get_max() != j + 1){
					find(index, tempdata, max, index[i].at(j + 1), position);
				}
			}
		}
	}
}

void follow(Data index[], Data tempdata[], int max) {
}
