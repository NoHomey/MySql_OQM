#include <iostream>
#include <fstream>
#include <string>
#include "DB.hh"
#include "Table.hh"
#include "Pattern.hh"
#include "Type.hh"

#include "hardcoded.hh"

bool Table::upper = false;
bool DB::upper = false;

int main(void) {
	DB db("exam");

	Table article("Article_15");
	article.field("password", string_(), password_);
	article.field("url", string_(), url_);
	article.field("created_on", date_(), created_on_);

	Table category("Category");
	category.field("description", long_text_(), description_);
	category.field("priority", double_(), priority_double_);

	Table user("User");
	user.field("password", varchar_(), password_);
	user.field("twitter", varchar_6_(), twitter_);
	user.field("name", varchar_(), name_);

	Table tag("Tag");
	tag.field("second_priority", float_(), second_priority_);
	tag.field("priority", int_(), priority_int_);

	db.many_to_one(&user, &category);
	db.one_to_many(&category, &article);
	Table link;
	db.many_to_many(&article, &tag, &link);

	db.add_if_missing(&article);
	db.add_if_missing(&category);
	db.add_if_missing(&user);
	db.add_if_missing(&tag);

	std::ofstream creates("creates.sql", std::ios::out);
	creates << db.create();

	std::ofstream inserts("inserts.sql", std::ios::out);
	inserts << db.use() << db.insert(7);

	std::ofstream migrates("migrates.sql", std::ios::out);
	Table migrate("Category_part1");
	std::vector<std::string> fields;
	fields.push_back(std::string("description"));
	migrates << db.use() << db.migrate(&migrate, fields, &category, std::string("Category_part2"));

	return 0;
}
