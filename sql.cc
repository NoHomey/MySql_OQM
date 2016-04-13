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

	Table article("Article_16");
	article.field("price", currency_(), price_);
	article.field("url", string_(), url_);
	article.field("password", string_(), password_);

	Table category("Category");
	category.field("name", varchar_(), name_);
	category.field("date_created_on", date_(), date_created_on_);

	Table user("User");
	user.field("description", long_text_(), description_);
	user.field("gender", varchar_6_(), gender_, false);
	user.field("name", varchar_(), name_, false);

	Table tag("Tag");
	tag.field("hash", varchar_16_(), hash_);
	tag.field("name", varchar_(), name_);

	Table article_user;
	db.many_to_many(&article, &user, &article_user);
	db.many_to_one(&article, &tag);
	db.one_to_one(&tag, &category);

	db.add_if_missing(&article);
	db.add_if_missing(&category);
	db.add_if_missing(&user);
	db.add_if_missing(&tag);

	std::ofstream creates("creates.sql", std::ios::out);
	creates << db.create();

	std::ofstream inserts("inserts.sql", std::ios::out);
	inserts << db.use() << db.insert(6);

	std::ofstream migrates("migrates.sql", std::ios::out);
	Table migrate("Article_16_part_1");
	std::vector<std::string> fields;
	fields.push_back(std::string("password"));
	//fields.push_back(std::string("url"));
	migrates << db.use() << db.migrate(&migrate, fields, &article, std::string("Article_16_part_2"));

	return 0;
}
