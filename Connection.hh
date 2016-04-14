#ifndef _CONNECTION_HH
#define _CONNECTION_HH

#include <string>
#include "Table.hh"

enum ConnectionType {
	one_to_one,
	many_to_one,
	many_to_many
};

struct Connection {
	Table* operator[](std::string table);
	Table* operator[](Table* table);
	ConnectionType type;
	Table* from;
	Table* to;
};

#endif
