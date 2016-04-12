#ifndef _PATTERN_HH
#define _PATTERN_HH

#include <string>

struct Pattern {
	static std::string Float(int i);
	static std::string Double(int i);
	static std::string Date(int i);
	static std::string Boolean(int i);
	static std::string Int(int i);
	static std::string Connection_ID(int i);
	static unsigned int id;
};

#endif
