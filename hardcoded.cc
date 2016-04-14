#include "hardcoded.hh"

std::string varchar_(void) {
	return std::string("varchar(256)");
}
std::string date_(void) {
	return std::string("date");
}
std::string currency_(void) {
	return std::string("float(5, 2)");
}
std::string string_(void) {
	return varchar_();
}
std::string long_string_(void) {
	return std::string("varchar(1256)");
}
std::string boolean_(void) {
	return std::string("bit");
}
std::string long_text_(void) {
	return std::string("longtext");
}
std::string double_(void) {
	return std::string("double(16, 8)");
}
std::string integer_(void) {
	return std::string("int");
}
std::string float_(void) {
	return std::string("float(8, 4)");
}
std::string varchar_6_(void) {
	return std::string("varchar(6)");
}
std::string int_(void) {
	return integer_();
}
std::string varchar_16_(void) {
	return std::string("varchar(16)");
}

std::string name_(unsigned int i) {
	std::string n;
	unsigned int k;
	if(i < 11) {
		k = i;
	} else {
		for(k = 2; k < 11; k++) {
			if(i % k == 0) {
				break;
			}
		}
	}
	switch(k) {
		case 1:
			n = std::string("Liam South");
			break;
		case 3:
			n = std::string("Mason Scot");
			break;
		case 5:
			n = std::string("Jacob Lawson");
			break;
		case 7:
			n = std::string("Wilam White");
			break;
		case 9:
			n = std::string("james West");
			break;
		case 2:
			n = std::string("Emma Watson");
			break;
		case 4:
			n = std::string("Maisy Scot");
			break;
		case 6:
			n = std::string("Madison Ivy");
			break;
		case 8:
			n = std::string("Isabel White");
			break;
		case 10:
			n = std::string("Mia Kalifa");
			break;
		default:
			n = std::string("Ava Adams");
			break;
	}
	return std::string("\"") + n + std::string("\"");
}
std::string published_on_(unsigned int i) {
	return std::string("\"1989-") + std::string(i < 10 ? "0" : "") + std::to_string(i) + std::string("-11\"");
}
std::string price_(unsigned int i) {
	return std::to_string(i) + std::string(".99");
}
std::string created_on_(unsigned int i) {
	return std::string("\"2016-04-") + std::string(i < 10 ? "0" : "") + std::to_string(i) + std::string("\"");
}
std::string url_(unsigned int i) {
	return std::string("\"https://github.com/thebravoman/elsys-db-practices/pull/") + std::to_string(i) + std::string("\"");
}
std::string content_(unsigned int i) {
	return std::string("\"It should have some content at page ") + std::to_string(i) + std::string("\"");
}
std::string visble_(unsigned int i) {
	return std::to_string(i % 2);
}
std::string password_(unsigned int i) {
	return std::string("\"qweqwe123") + std::to_string(i) + std::string("\"");
}
std::string description_(unsigned int i) {
	return std::string("\"It should have some description at page ") + std::to_string(i) + std::string("\"");
}
std::string date_created_on_(unsigned int i) {
	return created_on_(i);
}
std::string priority_double_(unsigned int i) {
	return std::to_string(i) + std::to_string(i) + std::string(".") + std::to_string(i) + std::to_string(i);
}
std::string created_by_(unsigned int i) {
	return name_(i);
}
std::string age_(unsigned int i) {
	return std::to_string(i);
}
std::string income_(unsigned int i) {
	return std::to_string(i) + std::string(".") + std::to_string(i);
}
std::string picture_url_(unsigned int i) {
	return std::string("\"http://imgur.com/gallery/gzr") + std::to_string(i) + std::string("BG\"");
}
std::string twitter_(unsigned int i) {
	return std::string("\"https://twitter.com/iansomerhalder/status/7160661133066731") + std::to_string(i) + std::string("\"");
}
std::string priority_int_(unsigned int i) {
	return std::to_string(i) + std::to_string(i);
}
std::string gender_(unsigned int i) {
	if(i % 2 == 0) {
		return std::string("\"male\"");
	}
	return std::string("\"female\"");
}
std::string hash_(unsigned int i) {
	return std::string("\"95682432319") + std::string(i < 10 ? "0" : "") + std::to_string(i) + std::string("\"");
}
std::string second_priority_(unsigned int i) {
	return income_(i);
}
