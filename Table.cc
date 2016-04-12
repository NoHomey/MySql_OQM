#include "Table.hh"
#include "toUpper.hh"
#include "Pattern.hh"

Table::Table(const char* Name): name(Name), fields(std::vector<Field>()), connections(std::vector<Connection>()) {}

void Table::field(const char* Name, const char* Sql, std::string (*Pattern) (int)) {
  fields.push_back({.name = std::string(Name), .sql = std::string(Sql), .pattern = Pattern});
}

std::string Table::create(void) {
  std::string sql_query = toUpper(std::string("\ncreate table "), upper);
  sql_query += name + std::string(" (\n\tid ");
  sql_query += toUpper(std::string("int not null primary key auto_increment,"), upper);
  for(Field field: fields) {
	if(field.sql[0] != '!') {
		sql_query += std::string("\n\t")  + field.name + std::string(" ") + toUpper(field.sql, upper) + std::string(",");
	}
  }
  sql_query += std::string("\n);\n");
  return sql_query;
}

void Table::connection(const char* Table, ConnectionType Type) {
	std::string name(Table);
	name += std::string("_id");
	field(name.c_str(), "!", Pattern::Connection_ID);
	connections.push_back({.table = std::string(Table), .field = name, .type = Type});
}

std::string Table::connection(void) {
	std::string sql_query("");
	for(Connection connection: connections) {
		if(connection.type == ConnectionType::many_to_many) {

		} else {
			sql_query += toUpper(std::string("\nalter table "), upper);
			sql_query += name + toUpper(std::string(" add "), upper);
			sql_query += connection.field + toUpper(std::string(" int not null"), upper);
			bool is_one_to_one = connection.type == ConnectionType::one_to_one;
			sql_query += toUpper(std::string(is_one_to_one ? " unique" : ""), upper);
			sql_query += toUpper(std::string(";\nalter table "), upper);
			sql_query += name + toUpper(std::string(" add foreign key ("), upper);
			sql_query += connection.field + toUpper(std::string(") references "), upper);
			sql_query += connection.table + std::string(" (id);\n");
		}
    }
	return sql_query;
}
