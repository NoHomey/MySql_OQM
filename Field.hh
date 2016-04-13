#ifndef _FIELD_HH
#define _FIELD_HH

#include <string>

struct Field {
  std::string name;
  std::string sql;
  std::string (*pattern) (unsigned int);
};

#endif
