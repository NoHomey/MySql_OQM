#include <iostream>
#include <string>
#include "DB.hh"
#include "Table.hh"
#include "Pattern.hh"
#include "Type.hh"

bool Table::upper = true;
bool DB::upper = true;

std::string url(unsigned int i) {
	return std::string("\"https://imgur.com/asdshfh/") + std::to_string(i) + std::string("\"");
}

std::string gender(unsigned int i) {
	if(i % 2 == 0) {
		return std::string("\"male\"");
	}
	return std::string("\"female\"");
}

std::string name(unsigned int i) {
	if(i % 2 == 0) {
		return std::string("\"Taylor Swift\"");
	}
	return std::string("\"Mike Tyson\"");
}

int main(void) {
	DB db("exam");

	Table article("Article_16");
	article.field("price", Type::Float(), Pattern::Float);
	article.field("url", Type::String(), url);
	article.field("password", Type::String(), Pattern::String);

	Table category("Category");
	category.field("name", Type::String(), Pattern::String);
	category.field("date_created_on", Type::Date(), Pattern::Date);

	Table user("User");
	user.field("description", std::string("longtext"), Pattern::String);
	user.field("gender", std::string("varchar(6)"), gender, false);
	user.field("name", Type::String(), name, false);

	Table tag("Tag");
	tag.field("hash", std::string("varchar(16)"), Pattern::String);
	tag.field("name", Type::String(), name, false);

	Table article_user;
	db.many_to_many(&article, &user, &article_user);
	db.many_to_one(&article, &tag);
	db.one_to_one(&tag, &category);

	db.add_table(&article);
	db.add_table(&category);
	db.add_table(&user);
	db.add_table(&tag);

	std::cout << db.create();

	std::cout << db.insert(6);

	Table migrate("Article_16_part_1");
	std::vector<std::string> fields;
	fields.push_back(std::string("password"));
	//fields.push_back(std::string("url"));
	std::cout << db.migrate(&migrate, fields, &article, std::string("Article_16_part_2"));

	return 0;
}
