#include <map>
#include <random>
#include <algorithm>
#include "Table.hh"
#include "toUpper.hh"
#include "Pattern.hh"

#include <iostream>

Table::Table(const char* Name): name(Name), fields(std::vector<Field>()), keys(std::vector<std::string>()) {}

void Table::field(const char* name, std::string sql, std::string (*pattern) (unsigned int)) {
  fields.push_back({.name =  std::string(name), .sql = sql, .pattern = pattern});
}

void Table::key(std::string table, std::string sql) {
	std::string name = table + std::string("_id");
	field(name.c_str(), sql, Pattern::Int);
	keys.push_back(table);
}

std::string Table::create(void) {
  std::string sql_query = toUpper(std::string("\ncreate table "), upper);
  sql_query += name + std::string(" (\n\tid ");
  sql_query += toUpper(std::string("int not null primary key auto_increment,"), upper);
  for(Field field: fields) {
	sql_query += std::string("\n\t")  + field.name + std::string(" ") + toUpper(field.sql, upper) + std::string(",");
  }
  for(std::string key: keys) {
	  sql_query += std::string("\n\t") + toUpper(std::string("foreign key ("), upper) + key + std::string("_id");
	  sql_query += toUpper(std::string(") references "), upper) + key + std::string(" (id),");
  }
  sql_query.pop_back();
  sql_query += std::string("\n);\n");
  return sql_query;
}

std::string Table::insert(unsigned int count) {
	std::map<std::string, std::vector<unsigned int>> ids;
	std::vector<unsigned int> posible(1, count + 1);
	std::random_device rnd;
	std::mt19937 gen(rnd());
	for(std::string key: keys) {
		std::shuffle(posible.begin(), posible.end(), gen);
		ids[key + std::string("_id")] = posible;
	}
	std::map<std::string, std::vector<unsigned int>>::iterator end = ids.end();
	std::string sql_query = toUpper(std::string("\ninsert into "), upper);
	sql_query += name + std::string(" (");
	for(Field field: fields) {
  		sql_query += field.name + std::string(", ");
    }
	sql_query.pop_back();
	sql_query.pop_back();
	sql_query += toUpper(std::string(") values"), upper);
	for(unsigned int k = 1; k <= count; ++k) {
		sql_query += std::string("\n\t(");
		for(Field field: fields) {
			if(ids.find(field.name) != end) {
				sql_query += field.pattern(ids[field.name][k - 1]);
				std::cout << std::endl << field.name << ' ' << k << ' ' << ids[field.name][k - 1] << std::endl;
			} else {
				sql_query += field.pattern(k);
			}
			sql_query += std::string(", ");
	    }
		sql_query.pop_back();
		sql_query.pop_back();
		sql_query += std::string("),");
	}
	sql_query.pop_back();
	sql_query += std::string(";\n");
	return sql_query;
}
