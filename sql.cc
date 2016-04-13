#include <iostream>
#include "DB.hh"
#include "Table.hh"
#include "Pattern.hh"
#include "Type.hh"

unsigned int Pattern::id = 0;
bool Table::upper = true;
bool DB::upper = true;

int main(void) {
	DB db("exam");
	Table article("Article_15");
	article.field("published_on", Type::Date(), Pattern::Date);
	article.field("visible", Type::Boolean(), Pattern::Boolean);
	article.field("prioiry", Type::Double(), Pattern::Double);
	Table user("User");
	user.field("created_on", Type::Date(), Pattern::Date);
	user.field("age", Type::Int(), Pattern::Int);
	user.field("income", Type::Float(), Pattern::Float);
	Table article_user;
	db.many_to_many(&article, &user, &article_user);

	std::cout << db.create();
	std::cout << db.tables.size() << std::endl;
	//std::cout << std::endl << article.fields[0].pattern(1) << std::endl;
	return 0;
}
