#include "Connection.hh"

Table* Connection::operator[](Table* table) {
	if(from == table) {
		return to;
	} else if(to == table) {
		return from;
	}
	return NULL;
}

bool Connection::operator==(const Connection connection) {
	return ((type = connection.type) && (from == connection.from) && (to == connection.to));
}
