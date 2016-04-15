#include "Connection.hh"

Table* Connection::operator[](Table* table) {
	if(from == table) {
		return to;
	}
	return from;
}
