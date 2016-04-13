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
	article.field("price", currency_(), price_);
	article.field("url", string_(), url_);
	article.field("created_on", date_(), created_on_);

	Table category("Category");
	category.field("name", varchar_(), name_);
	category.field("created_by", date_(), created_by_);

	Table user("User");
	user.field("income", float_(), income_);
	user.field("gender", varchar_6_(), gender_, false);
	user.field("name", varchar_(), name_, false);

	Table tag("Tag");
	tag.field("hash", varchar_16_(), hash_);
	tag.field("name", varchar_(), name_);

	db.one_to_many(&category, &user);
	db.many_to_one(&user, &tag);
	Table link;
	db.many_to_many(&article, &tag, &link);

	db.add_if_missing(&article);
	db.add_if_missing(&category);
	db.add_if_missing(&user);
	db.add_if_missing(&tag);

	std::ofstream creates("creates.sql", std::ios::out);
	creates << db.create();
	std::cout << "creates" << std::endl;

	std::ofstream inserts("inserts.sql", std::ios::out);
	inserts << db.use() << db.insert(7);
	std::cout << "inserts" << std::endl;

	std::ofstream migrates("migrates.sql", std::ios::out);
	Table migrate("User_part1");
	std::vector<std::string> fields;
	fields.push_back(std::string("income"));
	migrates << db.use() << db.migrate(&migrate, fields, &user, std::string("User_part2"));
	std::cout << "migrates" << std::endl;

	return 0;
}
