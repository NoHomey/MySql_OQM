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

	Table article("Article_1");
	article.field("password", string_(), password_);
	article.field("created_on", date_(), created_on_);
	article.field("content", long_string_(), content_);

	Table category("Category");
	category.field("description", long_text_(), description_);
	category.field("created_by", string_(), created_by_);

	Table user("User");
	user.field("income", float_(), income_);
	user.field("name", varchar_(), name_);

	Table tag("Tag");
	tag.field("priority", int_(), priority_int_);
	tag.field("name", varchar_(), name_);

	Table category_article;
	db.many_to_many(&category, &article, &category_article);
	db.many_to_one(&article, &tag);
	Table tag_user;
	db.many_to_many(&tag, &user, &tag_user);

	db.add_if_missing(&article);
	db.add_if_missing(&category);
	db.add_if_missing(&user);
	db.add_if_missing(&tag);

	std::ofstream creates("creates.sql", std::ios::out);
	creates << db.create();

	std::ofstream inserts("inserts.sql", std::ios::out);
	inserts << db.use() << db.insert(7);

	std::ofstream selects1("selects1.sql", std::ios::out);
	selects1 << db.use() << db.select(&tag, &category, 2);

	std::ofstream migrates("migrates.sql", std::ios::out);
	Table migrate("Article_1_part1");
	std::vector<std::string> fields;
	fields.push_back(std::string("created_on"));
	migrates << db.use();
	migrates << db.migrate(&migrate, fields, &article, std::string("Article_1_part2"));

	std::ofstream selects2("selects2.sql", std::ios::out);
	selects2 << db.use() << db.select(&user, &article, 2);

	return 0;
}
