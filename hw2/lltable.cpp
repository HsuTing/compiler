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
int find(Data first[], int max, int position);
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

int find(Data first[], int max, int position) {
	for(int i = 0; i < first[position].get_max(); i++) {
		if(first[position].at(i) == "epsilon") {
			return 1;
		}
	}
	return 0;
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
		for(int j = 0; j < index[i].get_check_max(); j++) {
			for(int k = 0; k < index[i].get_max(); k++) {
				if(index[i].find(k) == j) {
					int temp = -1;
					for(int l = 0; l < max; l++) {
						if(first[l].get() == index[i].at(k)) {
							temp = l;
							break;
						}
					}

					if(temp != -1) {
						for(int l = 0; l < first[i].get_max(); l++) {
							for(int m = 0; m < first[temp].get_max(); m++) {
								if(first[temp].at(l) == first[i].at(m) && first[temp].at(l) != "epsilon" && first[i].at(m) != "epsilon") {
									fout << setw(20) << index[i].get() << "| ";
									fout << setw(20) << first[temp].at(l) << "| ";
									fout << index[i].get() << " -> ";

									for(int n = k; n < index[i].get_max(); n++) {
										if(index[i].find(n) == j) {
											fout << index[i].at(n) << " ";
										}
									}

									fout << endl;
								}
							}
						}

						if(find(first, max, i) == 1) {
							for(int l = 0; l < first[i].get_max(); l++) {
								for(int m = 0; m < follow[i].get_max(); m++) {
									if(first[i].at(l) == follow[i].at(m)) {
										fout << setw(20) << index[i].get() << "| ";
										fout << setw(20) << follow[i].at(m) << "| ";
										fout << index[i].get() << " -> ";

										for(int n = k; n < index[i].get_max(); n++) {
											if(index[i].find(n) == j) {
												fout << index[i].at(n) << " ";
											}
										}

										fout << endl;
									}
								}
							}

							for(int l = 0; l < follow[i].get_max(); l++) {
								if(follow[i].at(l) == "$") {
									fout << setw(20) << index[i].get() << "| ";
									fout << setw(20) << "$" << "| ";
									fout << index[i].get() << " -> ";

									for(int n = k; n < index[i].get_max(); n++) {
										if(index[i].find(n) == j) {
											fout << index[i].at(n) << " ";
										}
									}

									fout << endl;
								}
							}

						}
					}
					else {
						if(find(first, max, i) == 0) {
							fout << setw(20) << index[i].get() << "| ";
							fout << setw(20) << index[i].at(k) << "| ";
							fout << index[i].get() << " -> ";

							for(int n = k; n < index[i].get_max(); n++) {
								if(index[i].find(n) == j) {
									fout << index[i].at(n) << " ";
								}
							}
							fout << endl;
						}
						else {
							for(int l = 0; l < follow[i].get_max(); l++) {
								if(follow[i].at(l) == "$") {
									fout << setw(20) << index[i].get() << "| ";
									fout << setw(20) << "$" << "| ";
									fout << index[i].get() << " -> ";
									
									for(int n = k; n < index[i].get_max(); n++) {
										if(index[i].find(n) == j) {
											fout << index[i].at(n) << " ";
										}
									}

									fout << endl;
								}
							}
						}
					}

					break;
				}
			}
		}
	}

	fout.close();
}
