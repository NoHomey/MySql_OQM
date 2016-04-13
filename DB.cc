#include <algorithm>
#include "DB.hh"
#include "toUpper.hh"
#include "Pattern.hh"

DB::DB(const char* Name): name(Name), tables(std::vector<Table>()) {}

bool DB::not_in(Table& T) {
	std::vector<Table>::iterator end = tables.end();
	return std::find(tables.begin(), end, T) != end;
}

void DB::many_to_many(Table& T1, Table& T2, Table& T3) {
	T3.name.swap(T1.name + std::string("_") + T2.name);
	std::string name = T1.name + std::string("_id");
	field(name.c_str(), "!", Pattern::Connection_ID);
	std::string name = T2.name + std::string("_id");
	field(name.c_str(), "!", Pattern::Connection_ID);
	if(not_in(T1)) {
		tables.push_back(T1);
	}
	if(not_in(T2)) {
		tables.push_back(T2);
	}
	tables.push_back(T3);
	T1.connection(T2, ConnectionType::many_to_many);
}

void DB::add_tables(Table& T1, Table& T2, ConnectionType Type) {
	if(tables.empty()) {
		tables.push_back(T2);
		tables.push_back(T1);
	} else {
		std::vector<Table>::iterator end = tables.end();
		std::vector<Table>::iterator begin = tables.begin();
		std::vector<Table>::iterator find_T1 = std::find(begin, end, T1);
		std::vector<Table>::iterator find_T2 = std::find(begin, end, T2);
		if(find_T1 != end) {
			tables.insert(find_T2 , T1);
		} else {
			tables.insert(find_T1 + 1, T2);
		}
	}
	std::string name = T2.name + std::string("_id");
	field(name.c_str(), "!", Pattern::Connection_ID);
	T1.connection(T2, Type);
}

void DB::many_to_one(Table& T1, Table& T2) {
	add_tables(T1, T2, ConnectionType::many_to_one);
}

void DB::one_to_many(Table& T1, Table& T2) {
	many_to_one(T2, T1);
}

void DB::one_to_one(Table& T1, Table& T2) {
	add_tables(T1, T2, ConnectionType::one_to_one);
}

std::string DB::create(void) {
  std::string sql_query = toUpper(std::string("\ndrop database if exists "), upper);
  sql_query += name + toUpper(std::string(";\ncreate database "), upper);
  sql_query += name + toUpper(std::string(";\nuse "), upper);
  sql_query += name + std::string(";\n");
  for(Table& table: tables) {
	  sql_query += table.create();
  }
  return sql_query;
}
