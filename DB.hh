#ifndef _DB_HH
#define _DB_HH

#include <string>
#include <vector>
#include "Table.hh"

class DB {
public:
	static bool upper;
	DB(const char* Name);
	void one_to_one(Table* T1, Table* T2);
	void one_to_many(Table* T1, Table* T2);
	void many_to_one(Table* T1, Table* T2);
	void many_to_many(Table* T1, Table* T2, Table* T3);
	void add_if_missing(Table* T);
	std::string create(void);
	std::string insert(unsigned int count);
	std::string use(void);
	std::string migrate(Table* T1, std::vector<std::string> fields, Table* T2, std::string name);
	std::string name;
	std::vector<Table*> tables;
private:
	bool not_in(Table* T);
	void add_tables(Table* T1, Table* T2);
};

#endif
