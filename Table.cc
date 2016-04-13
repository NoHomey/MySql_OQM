#include "Table.hh"
#include "toUpper.hh"
#include "Pattern.hh"

Table::Table(const char* Name): name(Name), fields(std::vector<Field>()), connections(std::vector<Connection>()) {}

void Table::field(const char* Name, std::string Sql, std::string (*Pattern) (unsigned int)) {
  fields.push_back({.name =  std::string(Name), .sql = Sql, .pattern = Pattern});
}

std::string Table::create(void) {
  std::string sql_query = toUpper(std::string("\ncreate table "), upper);
  sql_query += name + std::string(" (\n\tid ");
  sql_query += toUpper(std::string("int not null primary key auto_increment,"), upper);
  for(Field field: fields) {
	sql_query += std::string("\n\t")  + field.name + std::string(" ") + toUpper(field.sql, upper) + std::string(",");
  }
  sql_query += std::string("\n);\n");
  return sql_query;
}

void Table::connection(std::string Table, ConnectionType Type) {
	connections.push_back({.table = std::string(Table), .type = Type});
}

std::string Table::connection(void) {
	std::string sql_query("");
	for(Connection connection: connections) {
		if(connection.type == ConnectionType::many_to_many) {
			sql_query += toUpper(std::string("create table "), upper);
			sql_query += name + std::string("_") + connection.table;
			sql_query += std::string(" (\n\tid ");
			sql_query += toUpper(std::string("int not null primary key auto_increment,\n\t"), upper);
			sql_query += name + std::string("_id ") + toUpper(std::string("int,\n\t"), upper);
			sql_query += connection.table + std::string("_id ") + toUpper(std::string("int,\n\t"), upper);
			sql_query += toUpper(std::string("foreign key ("), upper);
			sql_query += name + std::string("_id ");
			sql_query += toUpper(std::string(") references "), upper);
			sql_query += name + std::string(" (id),\n\t");
			sql_query += toUpper(std::string("foreign key ("), upper);
			sql_query += connection.table + std::string("_id ");
			sql_query += toUpper(std::string(") references "), upper);
			sql_query += connection.table + std::string(" (id),\n);\n");
		} else {
			sql_query += toUpper(std::string("\nalter table "), upper);
			sql_query += name + toUpper(std::string(" add "), upper);
			sql_query += connection.table + toUpper(std::string("_id int not null"), upper);
			bool is_one_to_one = connection.type == ConnectionType::one_to_one;
			sql_query += toUpper(std::string(is_one_to_one ? " unique" : ""), upper);
			sql_query += toUpper(std::string(";\nalter table "), upper);
			sql_query += name + toUpper(std::string(" add foreign key ("), upper) + std::string("_id) ");
			sql_query += connection.table + toUpper(std::string("references "), upper);
			sql_query += connection.table + std::string(" (id);\n");
		}
    }
	return sql_query;
}
