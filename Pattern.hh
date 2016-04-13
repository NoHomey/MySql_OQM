#ifndef _PATTERN_HH
#define _PATTERN_HH

#include <string>

struct Pattern {
	static std::string Float(unsigned int i);
	static std::string Double(unsigned int i);
	static std::string Date(unsigned int i);
	static std::string Boolean(unsigned int i);
	static std::string Int(unsigned int i);
	static std::string String(unsigned int i);
};

#endif
