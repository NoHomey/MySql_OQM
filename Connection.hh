#ifndef _CONNECTION_HH
#define _CONNECTION_HH

#include <string>

enum ConnectionType {
	one_to_one,
	one_to_many,
	many_to_many
};

struct Connection {
  std::string table;
  std::string field;
  ConnectionType type;
};

#endif
