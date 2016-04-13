#ifndef _Type_HH
#define _Type_HH

#include <string>

class Type {
public:
	static std::string Float(void);
	static std::string Double(void);
	static std::string Date(void);
	static std::string Boolean(void);
	static std::string Int(void);
	static std::string Key(void);
	static std::string UniqueKey(void);
};

#endif
