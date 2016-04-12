#include "Pattern.hh"

std::string Pattern::Float(int i) {
	return std::to_string(i) + std::string(".") + std::to_string(i);
}

std::string Pattern::Double(int i) {
	return Float(i);
}

std::string Pattern::Date(int i) {
	return std::string("\"2016-04-") + std::string(i < 10 ? "0" : "") + std::to_string(i) + std::string("\"");
}

std::string Pattern::Boolean(int i) {
	return std::to_string(i % 2);
}

std::string Pattern::Int(int i) {
	return std::to_string(i);
}

std::string Pattern::Connection_ID(int i) {
	unsigned int k;
	if(i == 2) {
		k = id % i;
	} else {
		for(k = 1; k < i - 1; ++i) {
			if(id % k == 0) {
				break;
			}
		}
	}
	id++;
	return Int(i > 1 ? i - k : i);
}
