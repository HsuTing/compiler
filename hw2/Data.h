#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Data {
	public:
		Data();
		void set_max(int i);
		void set_name(string s);
		void set_check(int i, int j);
		void set_check_max(int i);
		void set_subdata(int i, string s);
		int get_max();
		string get();
		int find(int i);
		int get_check_num();
		string at(int i);
	private:
		int max;
		string name;
		int check[50];
		int check_max;
		string subdata[50];
};
