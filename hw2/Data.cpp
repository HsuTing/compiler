#include "Data.h"

Data::Data() {
	max = 0;
	name = "";
}

void Data::set_name(string s) {
	name = s;
}

void Data::set_subdata(int i, string s) {
	subdata[i] = s;
}

string Data::get() {
	return name;
}

string Data::at(int i) {
	return subdata[i];
}
