#ifndef _TABLE_HH
#define _TABLE_HH

#include <string>
#include <vector>
#include "Field.hh"

class Table {
public:
	static bool upper;
	Table(const char* Name = "");
	void field(const char* name, std::string sql, std::string (*pattern) (unsigned int));
	void key(std::string table, std::string sql);
	std::string create(void);
	std::string insert(unsigned int count);
	std::string name;
	std::vector<Field> fields;
	std::vector<std::string> keys;
};

#endif
