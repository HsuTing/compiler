#include "Data.h"

Data::Data() {
	max = 0;
	name = "";
	memset(check, 0, sizeof(check));
}

void Data::set_max(int i) {
	max = i;
}

void Data::set_name(string s) {
	name = s;
}

void Data::set_check(int i, int j) {
	check[i] = j;
}

void Data::set_subdata(int i, string s) {
	subdata[i] = s;
}

int Data::get_max() {
	return max;
}

string Data::get() {
	return name;
}

int Data::find(int i) {
	return check[i];
}

string Data::at(int i) {
	return subdata[i];
}