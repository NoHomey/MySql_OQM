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

	Table article("Article_1");
	article.field("name", varchar_(), name_);
	article.field("created_on", date_(), created_on_);
	article.field("content", long_string_(), content_);

	Table category("Category");
	category.field("name", varchar_(), name_);
	category.field("created_by", string_(), created_by_);

	Table user("User");
	user.field("twitter", varchar_6_(), twitter_);
	user.field("name", varchar_(), name_);
	user.field("dexcription", long_text_(), description_);

	Table tag("Tag");
	tag.field("priority", int_(), priority_int_);
	tag.field("hash", varchar_16_(), hash_);

	db.one_to_one(&tag, &user);
	db.one_to_many(&user, &category);
	//Table link;
	db.many_to_one(&article, &category);

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
	Table migrate("User_part1");
	std::vector<std::string> fields;
	fields.push_back(std::string("name"));
	migrates << db.use();
	migrates << db.migrate(&migrate, fields, &user, std::string("User_part2"));

	std::ofstream selects2("selects2.sql", std::ios::out);
	selects2 << db.use();

	return 0;
}
