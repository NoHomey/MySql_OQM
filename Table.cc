#include <random>
#include <algorithm>
#include "Table.hh"
#include "toUpper.hh"
#include "Pattern.hh"

Table::Table(const char* Name): name(Name), fields(std::vector<Field>()), keys(std::map<Table*, std::string>()) {}

void Table::field(const char* name, std::string sql, std::string (*pattern) (unsigned int), bool random) {
  fields.push_back({.name =  std::string(name), .sql = sql, .pattern = pattern, .random = random});
}

void Table::key(Table* table, std::string sql) {
	std::string name = table->name + std::string("_id");
	field(name.c_str(), sql, Pattern::Int);
	keys[table] = name;
}

std::string Table::create(void) {
  std::string sql_query = toUpper(std::string("\ncreate table "), upper);
  sql_query += name + std::string(" (\n\tid ");
  sql_query += toUpper(std::string("int not null primary key auto_increment,"), upper);
  for(Field field: fields) {
	sql_query += std::string("\n\t")  + field.name + std::string(" ") + toUpper(field.sql, upper) + std::string(",");
  }
  for(auto key: keys) {
	  sql_query += std::string("\n\t") + toUpper(std::string("foreign key ("), upper) + key.second;
	  sql_query += toUpper(std::string(") references "), upper) + key.first->name + std::string(" (id),");
  }
  sql_query.pop_back();
  return sql_query + std::string("\n);\n");
}

std::string Table::insert(unsigned int count) {
	const unsigned int len = fields.size();
	std::vector<unsigned int> map[len];
	std::vector<unsigned int> posible;
	for(unsigned int k = 0; k < count; ++k) {
		posible.push_back(k + 1);
	}
	std::random_device rnd;
	std::mt19937 gen(rnd());
	for(unsigned int i = 0; i < len; ++ i) {
		std::shuffle(posible.begin(), posible.end(), gen);
		map[i] = posible;
	}
	std::string sql_query = toUpper(std::string("\ninsert into "), upper);
	sql_query += name + std::string(" (");
	for(Field field: fields) {
  		sql_query += field.name + std::string(", ");
    }
	sql_query.pop_back();
	sql_query.pop_back();
	sql_query += toUpper(std::string(") values"), upper);
	for(unsigned int k = 0; k < count; ++k) {
		sql_query += std::string("\n\t(");
		for(unsigned int i  = 0; i < len; ++i) {
			sql_query += fields[i].pattern(fields[i].random ? map[i][k] : k + 1) + std::string(", ");
	    }
		sql_query.pop_back();
		sql_query.pop_back();
		sql_query += std::string("),");
	}
	sql_query.pop_back();
	return sql_query + std::string(";\n");
}
