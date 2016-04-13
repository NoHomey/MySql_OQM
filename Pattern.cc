#include "Pattern.hh"

std::string Pattern::Float(unsigned int i) {
	return std::to_string(i) + std::string(".") + std::to_string(i);
}

std::string Pattern::Double(unsigned int i) {
	return Float(i);
}

std::string Pattern::Date(unsigned int i) {
	return std::string("\"2016-04-") + std::string(i < 10 ? "0" : "") + std::to_string(i) + std::string("\"");
}

std::string Pattern::Boolean(unsigned int i) {
	return std::to_string(i % 2);
}

std::string Pattern::Int(unsigned int i) {
	return std::to_string(i);
}

std::string Pattern::String(unsigned int i) {
	return std::string("\"Bla bla bla ") + std::to_string(i) + std::string("\"");;
}
