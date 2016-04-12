#ifndef _DB_HH
#define _DB_HH

#include <string>
#include <vector>
#include "Table.hh"

struct DB {
	static bool upper;
	DB(const char* Name);
	void one_to_one(Table& T1, Table& T2);
	void one_to_many(Table& T1, Table& T2);
	void many_to_one(Table& T1, Table& T2);
	void many_to_many(Table& T1, Table& T2);
	std::string create(void);
	std::string relations(void);
	std::string name;
	std::vector<Table> tables;
};

#endif
