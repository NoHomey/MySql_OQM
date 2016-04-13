#include <algorithm>
#include "DB.hh"
#include "toUpper.hh"
#include "Pattern.hh"
#include "Type.hh"

DB::DB(const char* Name): name(Name), tables(std::vector<Table*>()) {}

bool DB::not_in(Table* T) {
	std::vector<Table*>::iterator end = tables.end();
	return std::find(tables.begin(), end, T) == end;
}

void DB::many_to_many(Table* T1, Table* T2, Table* T3) {
	std::string name = T1->name + std::string("_") + T2->name;
	T3->name.swap(name);
	T3->key(T2->name, Type::Key());
	T3->key(T1->name, Type::Key());
	if(not_in(T1)) {
		tables.push_back(T1);
	}
	if(not_in(T2)) {
		tables.push_back(T2);
	}
	tables.push_back(T3);
}

void DB::add_tables(Table* T1, Table* T2) {
	if(tables.empty()) {
		tables.push_back(T2);
		tables.push_back(T1);
	} else {
		std::vector<Table*>::iterator end = tables.end();
		std::vector<Table*>::iterator begin = tables.begin();
		std::vector<Table*>::iterator find_T1 = std::find(begin, end, T1);
		std::vector<Table*>::iterator find_T2 = std::find(begin, end, T2);
		if(find_T1 == end) {
			tables.insert(find_T2 + 1, T1);
		} else {
			tables.insert(find_T1, T2);
		}
	}
}

void DB::many_to_one(Table* T1, Table* T2) {
	T1->key(T2->name, Type::Key());
	add_tables(T1, T2);
}

void DB::one_to_many(Table* T1, Table* T2) {
	many_to_one(T2, T1);
}

void DB::one_to_one(Table* T1, Table* T2) {
	T1->key(T2->name, Type::UniqueKey());
	add_tables(T1, T2);
}

void DB::add_if_missing(Table* T) {
	if(not_in(T)) {
		tables.insert(tables.begin(), T);
	}
}

std::string DB::create(void) {
  std::string sql_query = toUpper(std::string("drop database if exists "), upper);
  sql_query += name + toUpper(std::string(";\ncreate database "), upper);
  sql_query += name + toUpper(std::string(";\nuse "), upper);
  sql_query += name + std::string(";\n");
  for(Table* table: tables) {
	  sql_query += table->create();
  }
  return sql_query;
}

std::string DB::insert(unsigned int count) {
  std::string sql_query("");
  for(Table* table: tables) {
	  sql_query += table->insert(count);
  }
  return sql_query;
}

std::string DB::use(void) {
	return toUpper(std::string("use "), upper) + name + std::string(";\n");
}

std::string DB::migrate(Table* T1, std::vector<std::string> fields, Table* T2, std::string name) {
	for(std::string field : fields) {
		std::vector<Field>::iterator it = std::find_if(T2->fields.begin(), T2->fields.end(),
			[field](Field search) -> bool {return search.name == field;});
		T1->fields.push_back(*it);
		T2->fields.erase(it);
	}
	std::string sql_query = T1->create();
	sql_query += toUpper(std::string("\ninsert into "), upper) + T1->name + std::string(" (");
	for(std::string field : fields) {
		sql_query += field + std::string(", ");
	}
	sql_query.pop_back();
	sql_query.pop_back();
	sql_query += toUpper(std::string(") select "), upper);
	for(std::string field : fields) {
		sql_query += field + std::string(", ");
	}
	sql_query.pop_back();
	sql_query.pop_back();
	sql_query += toUpper(std::string(" from "), upper) + T2->name + std::string(";\n");
	for(std::string field : fields) {
		sql_query += toUpper(std::string("alter table "), upper) + T2->name;
		sql_query += toUpper(std::string(" drop column "), upper) + field + std::string(";\n");
	}
	sql_query += toUpper(std::string("alter table "), upper) + T2->name;
	sql_query += toUpper(std::string(" rename "), upper) + name + std::string(";\n");
	T2->name.swap(name);
	return sql_query;
}
