#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

int check(string word);					//找尋是否有特別的符號，包括operator, special,
int length(string word);				//計算找到的符號長度
string Keyword(string word);			//以下為各種比對function
string Operator(string word);
string Special(string word);
string Identifier(string word);
string Number(string word);
string Char(string word);
string Comment(string word);
string Error(string word);

int main(int argc, char *argv[]) {
	ifstream fin(argv[1]);
	ofstream fout("token.txt");
	int count_line = 0;

	if(fin == NULL) {
		cout << "Can not find file." << endl;
	}
	else {
		string line;

		while(getline(fin, line)) {			//逐行讀取
			if(line == "") {
				continue;
			}

			istringstream fin_word(line);
			string word = "", temp = "", remain = "";
			int pos = 0;

			count_line++;
			fout << "Line " << count_line << ":" << endl;

			while(fin_word >> word) {			//逐字讀取
				if(Comment(word) == "Comment") {
					break;
				}

				while(word != "") {
					fout << "   ";

					if((pos = check(word)) != -1) {			//切割字串
						remain = word.substr(pos);
						if(pos != 0) {
							word = word.substr(0, pos);
						}
						else {
							remain = word.substr(pos + length(word));
							word = word.substr(0, length(word));
						}
					}

					temp = temp + Keyword(word);
					temp = temp + Operator(word);
					temp = temp + Special(word);
					temp = temp + Number(word);
					temp = temp + Char(word);
					if(temp == "") {
						temp = temp + Identifier(word);
					}
					temp =  Error(temp);
					fout << temp << word << endl;

					temp = "";
					pos = 0;
					word = remain;
					remain = "";
				}
			}
		}

		fin.close();
		fout.close();
	}
	
	return 0;
}

int check(string word) {
	string temp[] = {"{", "}", "[", "]", "(", ")", ";", ",", "=", "!", "+", "-", "*", "/", "==", "!=", "<", ">", "<=", ">=", "&&", "||"};
	int count = -1;

	for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
		if(word.find(temp[i]) != -1 && count > word.find(temp[i])) {
			count = word.find(temp[i]);
		}
	}

	return count;
}

int length(string word) {
	string temp[] = {"==", "!=", "<=", ">=", "&&", "||"};
	int count = -1;

	for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
		if(word.find(temp[i]) != -1 && count > word.find(temp[i])) {
			count = word.find(temp[i]);
		}
	}

	if(count != -1) {
		return 2;
	}
	else {
		return 1;
	}
}

string Keyword(string word) {
	string temp[] = {"int", "char", "float", "double", "return", "break", "print", "if", "else", "while", "break", "for"};

	for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
		if(word == temp[i]) {
			return "<Keyword>     : ";
		}
	}

	return "";
}

string Operator(string word) {
	string temp[] = {"==", "!=", "<", ">", "<=", ">=", "&&", "||", "=", "!", "+", "-", "*", "/"};

	for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
		if(word == temp[i]) {
			return "<Operator>    : ";
		}
	}

	return "";
}

string Special(string word) {
	string temp[] = {"(", ")", "[", "]", "{", "}", ";", ","};

	for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
		if(word == temp[i]) {
			return "<Special>     : ";
		}
	}

	return "";
}

string Identifier(string word) {
	string Letter[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "k", "l", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "_"};

	for(int i = 0; i < word.length(); i++) {
		int check = 0;

		stringstream temp(word.substr(i, 1));
		int num;
		temp >> num;

		if(i == 0) {
			if(temp) {
				return "";
			}
		}
		else {
			if(temp) {
				check = 1;
			}
		}

		for(int j = 0; j < (sizeof(Letter) / sizeof(Letter[0])); j++) {
			if(word.substr(i, 1) == Letter[j]) {
				check = 1;
			}
		}

		if(check == 0) {
			return "";
		}
	}

	return "<Identifier>  : ";
}

string Number(string word) {
	int count = 0;

	for(int i = 0; i < word.length(); i++) {
		stringstream temp(word.substr(i, 1));
		int num;
		temp >> num;

		if(word.substr(0,1) == ".") {
			return "";
		}

		if(word.substr(i, 1) == "." && count == 0) {
			count = 1;
			continue;
		}

		if(!temp) {
			return "";
		}
	}

	return "<Number>      : ";
}

string Char(string word) {
	string temp_start = word.substr(0, 1);
	int temp = word.length();
	string temp_end = word. substr(temp - 1, 1);

	if(temp_start == "'" && temp_end == "'") {
		return "<Char>        : ";
	}

	return "";
}

string Comment(string word) {
	if(word == "//") {
		return "Comment";
	}

	return "";
}

string Error(string word) {
	if(word == "") {
		return "<Error>       : ";
	}
	else {
		return word;
	}
}
