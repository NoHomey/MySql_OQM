#include "DB.hh"
#include "toUpper.hh"

DB::DB(const char* Name): name(Name), tables(std::vector<Table>()) {}

std::string DB::create(void) {
  std::string sql_query = toUpper(std::string("\ndrop database if exists "), upper);
  sql_query += name + toUpper(std::string(";\ncreate database "), upper);
  sql_query += name + toUpper(std::string(";\nuse "), upper);
  sql_query += name + std::string(";\n");
  return sql_query;
}
