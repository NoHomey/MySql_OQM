#include "Type.hh"

std::string Type::Float(void) {
	return std::string("float(8, 4)");
}

std::string Type::Double(void) {
	return std::string("double(8, 4)");
}

std::string Type::Date(void) {
	return std::string("date");
}

std::string Type::Boolean(void) {
	return std::string("bit");
}

std::string Type::Int(void) {
	return std::string("int");
}

std::string Type::Key(void) {
	return Type::Int() + std::string(" not null");
}

std::string Type::UniqueKey(void) {
	return Type::Key() + std::string(" unique");
}
