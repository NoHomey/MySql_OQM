#include <iostream>
#include <fstream>
#include <string>
#include "DB.hh"
#include "Table.hh"
#include "Pattern.hh"
#include "Type.hh"

#include "hardcoded.hh" //192.168.113.98

bool Table::upper = false;
bool DB::upper = false;

int main(void) {
	DB db("exam");

	Table article("Article_15");
	article.field("name", varchar_(), name_);
	article.field("price", currency_(), price_);
	article.field("content", long_string_(), content_);

	Table category("Category");
	category.field("date_created_on", date_(), date_created_on_);
	category.field("name", varchar_(), name_);

	Table user("User");
	user.field("password", varchar_(), password_);
	user.field("name", varchar_(), name_);
	user.field("age", int_(), age_);

	Table tag("Tag");
	tag.field("description", varchar_(), description_);
	tag.field("name", varchar_(), name_);

	db.one_to_many(&category, &tag);
	Table link;
	db.many_to_many(&tag, &article, &link);
	db.one_to_many(&article, &user);

	db.add_if_missing(&article);
	db.add_if_missing(&category);
	db.add_if_missing(&user);
	db.add_if_missing(&tag);

	std::ofstream creates("creates.sql", std::ios::out);
	creates << db.create();

	std::ofstream inserts("inserts.sql", std::ios::out);
	inserts << db.use() << db.insert(7);

	std::ofstream selects1("selects1.sql", std::ios::out);
	selects1 << db.use();

	std::ofstream migrates("migrates.sql", std::ios::out);
	Table migrate("Tag_part1");
	std::vector<std::string> fields;
	fields.push_back(std::string("name"));
	migrates << db.use();
	migrates << db.migrate(&migrate, fields, &tag, std::string("Tag_part2"));

	std::ofstream selects2("selects2.sql", std::ios::out);
	selects2 << db.use();

	return 0;
}
