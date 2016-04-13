#ifndef _TABLE_HH
#define _TABLE_HH

#include <string>
#include <vector>
#include "Field.hh"
#include "Connection.hh"

struct Table {
	static bool upper;
	Table(const char* Name = "");
	void field(const char* Name, const char* Sql, std::string (*Pattern) (unsigned int));
	void connection(std::string Table, ConnectionType Type);
	std::string connection(void);
	std::string create(void);
	std::string name;
	std::vector<Field> fields;
	std::vector<Connection> connections;
};

#endif
