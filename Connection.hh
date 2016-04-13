#ifndef _CONNECTION_HH
#define _CONNECTION_HH

#include <string>

enum ConnectionType {
	one_to_one,
	many_to_one,
	many_to_many
};

struct Connection {
  std::string table;
  ConnectionType type;
};

#endif
