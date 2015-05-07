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
void find(Data index[], Data tempdata[], int check[], int max, string name, int position);
void first(Data index[], int max);
void find_follow(Data index[], Data tempdata[], int check[], int max, string name, int position);
void follow(Data tempdata[], int max);

int main(void) {
	int max = count_index();
	Data index[max], tempdata[max];
	input_grammar(index);
	first(index, max);

	for(int i = 0; i < max; i++) {
		int check[max];
		memset(check, 0, sizeof(check));

		tempdata[i].set_name(index[i].get());
		find_follow(index, tempdata, check, max, index[i].get(), i);
	}

	follow(tempdata, max);

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
			if(tempdata[i].at(j) == " ") {
				continue;
			}

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
	int temp = first_check(index, max, name);

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

void find(Data index[], Data tempdata[], int check[], int max, string name, int position) {
	int temp = first_check(index, max, name);

	if(temp == -1) {
		temp = tempdata[position].get_max();
		tempdata[position].set_subdata(temp, name);
		tempdata[position].set_max(temp + 1);
		return;
	}
	else {
		for(int i = 0; i < index[temp].get_check_max(); i++) {
			for(int j = 0; j < index[temp].get_max(); j++) {
				if(index[temp].find(j) == i) {
					find(index, tempdata, check, max, index[temp].at(j), position);
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

void find_follow(Data index[], Data tempdata[], int check[], int max, string name, int position) {
	for(int i = 0; i < max; i++) {
		for(int j = 0; j < index[i].get_max(); j++) {
			if(index[i].at(j) == name) {
				if(index[i].find(j + 1) != index[i].find(j)) {
					if(index[i].get() != name && check[i] != 1) {
						check[i] = 1;
						find_follow(index, tempdata, check, max, index[i].get(), position);
					}
				}
				else if(j == index[i].get_max() - 1) {
					if(index[i].get() != name && check[i] != 1) {
						check[i] = 1;
						find_follow(index, tempdata, check, max, index[i].get(), position);
					}
				}
				else if(index[i].get_max() != j + 1) {
					find(index, tempdata, check, max, index[i].at(j + 1), position);

					int temp = -1;
					for(int k = 0; k < tempdata[i].get_max(); k++) {
						if(tempdata[i].at(k) == "epsilon") {
							temp = k;
						}
					}
				}
			}
		}
	}
}

void follow(Data tempdata[], int max) {
	for(int i = 0; i < max; i++) {
		for(int j = 1; j < tempdata[i].get_max(); j++) {
			for(int k = 0; k < j; k++) {
				if(tempdata[i].at(j) == tempdata[i].at(k)) {
					tempdata[i].set_subdata(k, " ");
				}
			}
			if(tempdata[i].at(j) == "epsilon") {
				tempdata[i].set_subdata(j, " ");
			}
		}
	}
}
