#include "Connection.hh"

Table* Connection::operator[](std::string table) {
	if(from->name == table) {
		return from;
	}
	if(to->name == table) {
		return to;
	}
	return NULL;
}

Table* Connection::operator[](Table* table) {
	if(from == table) {
		return to;
	}
	return from;
}
