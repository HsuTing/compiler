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
		void set_subdata(int i, string s);
		int get_max();
		string get();
		string at(int i);
	private:
		int max;
		string name;
		string subdata[100];
};
