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
	article.field("visible", boolean_(), visible_);

	Table category("Category");
	category.field("priority_double", double_(), priority_double_);
	category.field("name", varchar_(),name_);

	Table user("User");
	user.field("created_on", date_(), created_on_);
	user.field("age", integer_(), age_);
	user.field("gender", varchar_6_(), gender_);

	Table tag("Tag");
	tag.field("priority_int", int_(), priority_int_);
	tag.field("description", varchar_(), description_);

	Table category_article;
	db.many_to_many(&category, &article, &category_article);
	db.one_to_one(&user, &tag);
	db.many_to_one(&tag, &category);

	db.add_if_missing(&article);
	db.add_if_missing(&category);
	db.add_if_missing(&user);
	db.add_if_missing(&tag);

	std::ofstream creates("creates.sql", std::ios::out);
	creates << db.create();

	std::ofstream inserts("inserts.sql", std::ios::out);
	inserts << db.use() << db.insert(6);

	std::ofstream selects1("selects1.sql", std::ios::out);
	selects1 << db.use();
	selects1 << db.select(&category, &user, JoinType::inner, 3);

	std::ofstream migrates("migrates.sql", std::ios::out);
	Table migrate("Tag_part1");
	std::vector<std::string> fields;
	fields.push_back(std::string("description"));
	migrates << db.use();
	migrates << db.migrate(&migrate, fields, &tag, std::string("Tag_part2"));

	std::ofstream selects2("selects2.sql", std::ios::out);
	selects2 << db.use();
	selects2 << db.select(&article, &tag, JoinType::inner, 2);

	return 0;
}
