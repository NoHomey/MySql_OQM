#include "toUpper.hh"

std::string toUpper(std::string str, bool upper) {
	int i = 0;
	if(upper) {
		for(char c: str) {
			str[i++] = std::toupper(c);
		}
	}
	return str;
}
