# MySql_OQM
MySql Object Querry Mapper

# Creating no password mysql user:

```sql
create user 'ivo@localhost';
grant all privileges on *.* to 'ivo'@'localhost' with grant option;
/* mysql -u ivo */
```

# Makefile:

```makefile

folder=Borislav_Stratev_B_2# Folder FirstName_LastName_Class_Number

db=exam# DB Name

user=ivo# mysql user Name

ip=192.168.0.103# machine IP

$make all# Generates all sql files in $(folder) if $mysql can be accesed with $(user) then exports are also generated.

$make get class=А/Б num=[1..29]# gets exam

$make picture# opens mysql-workbench

$make tar/zip# generates archive

$make post# posts exam

```

# Sequence example:

```
make get class=Б num=2
make
make picture
make tar
make post
```

# mysql.cc:

## Syntax upper/lower case (set as global varibels before int main(...):

```c++
bool Table::upper = true; //upper case
bool DB::upper = true; //upper case
```

```c++
bool Table::upper = false; //lower case
bool DB::upper = false; //lower case
```
## Creating DB:

```c++
DB db("exam"); // DB(const char* Name);
```

## Creating Table:

```c++
Table article("Article_1"); // Table(const char* Name = "");
```

## Adding table fields:

```c++
article.field("password", string_(), password_); // void field(const char* name, std::string sql, std::string (*pattern) (unsigned int), bool random = true);
```

### hardcoded.hh:

```c++
std::string varchar_(void);
std::string date_(void);
std::string currency_(void);
std::string string_(void);
std::string long_string_(void);
std::string boolean_(void);
std::string long_text_(void);
std::string double_(void);
std::string integer_(void);
std::string float_(void);
std::string varchar_6_(void);
std::string int_(void);
std::string varchar_16_(void);

std::string name_(unsigned int i);
std::string published_on_(unsigned int i);
std::string price_(unsigned int i);
std::string created_on_(unsigned int i);
std::string url_(unsigned int i);
std::string content_(unsigned int i);
std::string visible_(unsigned int i);
std::string password_(unsigned int i);
std::string description_(unsigned int i);
std::string date_created_on_(unsigned int i);
std::string priority_double_(unsigned int i);
std::string created_by_(unsigned int i);
std::string age_(unsigned int i);
std::string income_(unsigned int i);
std::string picture_url_(unsigned int i);
std::string twitter_(unsigned int i);
std::string priority_int_(unsigned int i);
std::string gender_(unsigned int i);
std::string hash_(unsigned int i);
std::string second_priority_(unsigned int i);
```

### Adding custom field set:

```c++
std::string my_field(unsigned int i) {
  return std::string("\"My Field# ") + std::to_string(i) + std::string("\""); // Note the escaping quotes -> it will be evaled as string when generating inserts.
}

article.field("my_field", std::string("tinyblob"), my_field, false); // Note that all sql types need to be written is lower case. Setting random to false -> my_field will be called with [1..num of inserts].
```

## Adding table relations:

### One to one:

```c++
db.one_to_one(&tag, &article); // void one_to_one(Table* T1, Table* T2); (Tag has one to one connection with Article)
```

### One to many:

```c++
db.one_to_many(&tag, &article); // void one_to_many(Table* T1, Table* T2); (Tag has one to many connection with Article)
```

### Many to one:

```c++
db.many_to_one(&tag, &article); // void many_to_one(Table* T1, Table* T2); (Tag has many to one connection with Article)
```

### Many to many:

```c++
Table tag_article; // Note that for each amny to many connection new connection table is required
db.many_to_many(&tag, &article, &tag_article); // void many_to_many(Table* T1, Table* T2, Table* T3); (Tag has many to many connection with Article)
```

## Adding table to db if no connection to it was provided:

```c++
db.add_if_missing(&article) // void add_if_missing(Table* T); (If table not added in db relation priority queue it will be added).
```

# Up so far mysql.cc looks like this:

```c++
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
	article.field("visible", boolean_(), visible_);
	article.field("password", string_(), password_);
	article.field("name", varchar_(), name_);

	Table category("Category");
	category.field("name", varchar_(), name_);
	category.field("date_created_on", date_(), date_created_on_);

	Table user("User");
	user.field("created_on", date_(), created_on_);
	user.field("description", long_text_(), description_);
	user.field("picture_url", string_(), picture_url_);

	Table tag("Tag");
	tag.field("second_priority", float_(), second_priority_);
	tag.field("description", varchar_(), description_);

	Table user_article;
	db.many_to_one(&category, &tag);
	db.one_to_one(&tag, &article);
	db.one_to_one(&article, &user);

	db.add_if_missing(&article);
	db.add_if_missing(&category);
	db.add_if_missing(&user);
	db.add_if_missing(&tag);
```

## Writing mysql querries for DB creation:

```c++
std::ofstream creates("creates.sql", std::ios::out);
creates << db.create(); // std::string create(void);
```

### creates.sql:

```sql
drop database if exists exam;
create database exam;
use exam;

create table User (
	id int not null primary key auto_increment,
	created_on date,
	description longtext,
	picture_url varchar(256)
);

create table Article_1 (
	id int not null primary key auto_increment,
	visible bit,
	password varchar(256),
	name varchar(256),
	User_id int not null unique,
	foreign key (User_id) references User (id)
);

create table Tag (
	id int not null primary key auto_increment,
	second_priority float(8, 4),
	description varchar(256),
	Article_1_id int not null unique,
	foreign key (Article_1_id) references Article_1 (id)
);

create table Category (
	id int not null primary key auto_increment,
	name varchar(256),
	date_created_on date,
	Tag_id int not null,
	foreign key (Tag_id) references Tag (id)
);

```

## Writing mysql querries for DB inserts (fake filling db):

```c++
std::ofstream inserts("inserts.sql", std::ios::out);
inserts << db.use() << db.insert(3); // std::string use(void);, std::string insert(unsigned int count);
```

### inserts.sql:

```sql
use exam;

insert into User (created_on, description, picture_url) values
	("2016-04-01", "It should have some description at page 1", "http://imgur.com/gallery/gzr2BG"),
	("2016-04-03", "It should have some description at page 2", "http://imgur.com/gallery/gzr3BG"),
	("2016-04-02", "It should have some description at page 3", "http://imgur.com/gallery/gzr1BG");

insert into Article_1 (visible, password, name, User_id) values
	(1, "qweqwe1231", "Liam South", 3),
	(0, "qweqwe1233", "Emma Watson", 2),
	(1, "qweqwe1232", "Mason Scot", 1);

insert into Tag (second_priority, description, Article_1_id) values
	(1.1, "It should have some description at page 2", 2),
	(3.3, "It should have some description at page 3", 3),
	(2.2, "It should have some description at page 1", 1);

insert into Category (name, date_created_on, Tag_id) values
	("Emma Watson", "2016-04-03", 1),
	("Liam South", "2016-04-01", 2),
	("Mason Scot", "2016-04-02", 3);

```

## Selecting by making relational querry:

```c++
selects1 << db.select(&article, &category, JoinType::inner, 3); // std::string select(Table* wich, Table* given, enum JoinType join_type, unsigned int id = 0);
```

### Joining:

```c++
enum JoinType {
	inner,
	left,
	right,
	outer,
	left_excld,
	right_excld,
	outer_excld
};
```

### Example:

```c++
std::ofstream selects1("selects1.sql", std::ios::out);
selects1 << db.use();
selects1 << db.select(&article, &category, JoinType::inner, 3); // Select Article for a given Category (id == 3) (id must be in range [1..number of inserts] 
```

### select1.sql:

```sql
use exam;

select Article_1.id from Article_1
inner join Tag on Tag.Article_1_id = Article_1.id
inner join Category on Category.Tag_id = Tag.id
where Category.id = 3;

```

## Migrating a table (spliting):

```c++
std::ofstream migrates("migrates.sql", std::ios::out);
Table migrate("Tag_part1"); //  Each migration requires a migration table (Separate Tag into twp tabes)
std::vector<std::string> fields; // Fields wich new table will contain, all other are left in second table.
fields.push_back(std::string("description")); // Only one field in this case
migrates << db.use();
migrates << db.migrate(&migrate, fields, &tag, std::string("Tag_part2")); // std::string migrate(Table* T1, std::vector<std::string> fields, Table* T2, std::string name);
```

### migrates.sql:

```sql
use exam;

create table Tag_part1 (
	id int not null primary key auto_increment,
	description varchar(256)
);

insert into Tag_part1 (description) select description from Tag;
alter table Tag drop column description;
alter table Tag rename Tag_part2;

```

### All joining type selects example:

```c++
std::ofstream selects2("selects2.sql", std::ios::out);
	selects2 << db.use();
	selects2 << db.select(&user, &tag, JoinType::inner, 2);
	selects2 << db.select(&user, &tag, JoinType::left);
	selects2 << db.select(&user, &tag, JoinType::right);
	selects2 << db.select(&user, &tag, JoinType::outer);
	selects2 << db.select(&user, &tag, JoinType::left_excld);
	selects2 << db.select(&user, &tag, JoinType::right_excld);
	selects2 << db.select(&user, &tag, JoinType::outer_excld);
```

### select2.sql:

```sql
use exam;

select User.id from User
inner join Article_1 on Article_1.User_id = User.id
inner join Tag_part2 on Tag_part2.Article_1_id = Article_1.id
where Tag_part2.id = 2;

select User.id from User
left join Article_1 on Article_1.User_id = User.id
left join Tag_part2 on Tag_part2.Article_1_id = Article_1.id;

select User.id from User
right join Article_1 on Article_1.User_id = User.id
right join Tag_part2 on Tag_part2.Article_1_id = Article_1.id;

select User.id from User
left join Article_1 on Article_1.User_id = User.id
left join Tag_part2 on Tag_part2.Article_1_id = Article_1.id
union all
select User.id from User
right join Article_1 on Article_1.User_id = User.id
right join Tag_part2 on Tag_part2.Article_1_id = Article_1.id;

select User.id from User
left join Article_1 on Article_1.User_id = User.id
left join Tag_part2 on Tag_part2.Article_1_id = Article_1.id
where Tag_part2.id is null;

select User.id from User
right join Article_1 on Article_1.User_id = User.id
right join Tag_part2 on Tag_part2.Article_1_id = Article_1.id
where User.id is null;

select User.id from User
left join Article_1 on Article_1.User_id = User.id
left join Tag_part2 on Tag_part2.Article_1_id = Article_1.id
union all
select User.id from User
right join Article_1 on Article_1.User_id = User.id
right join Tag_part2 on Tag_part2.Article_1_id = Article_1.id
where User.id is null or Tag_part2.id is null;

```

## Full version of sql.cc:

```c++
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
	article.field("visible", boolean_(), visible_);
	article.field("password", string_(), password_);
	article.field("name", varchar_(), name_);

	Table category("Category");
	category.field("name", varchar_(), name_);
	category.field("date_created_on", date_(), date_created_on_);

	Table user("User");
	user.field("created_on", date_(), created_on_);
	user.field("description", long_text_(), description_);
	user.field("picture_url", string_(), picture_url_);

	Table tag("Tag");
	tag.field("second_priority", float_(), second_priority_);
	tag.field("description", varchar_(), description_);

	Table user_article;
	db.many_to_one(&category, &tag);
	db.one_to_one(&tag, &article);
	db.one_to_one(&article, &user);

	db.add_if_missing(&article);
	db.add_if_missing(&category);
	db.add_if_missing(&user);
	db.add_if_missing(&tag);

	std::ofstream creates("creates.sql", std::ios::out);
	creates << db.create();

	std::ofstream inserts("inserts.sql", std::ios::out);
	inserts << db.use() << db.insert(3);

	std::ofstream selects1("selects1.sql", std::ios::out);
	selects1 << db.use();
	selects1 << db.select(&article, &category, JoinType::inner, 3);

	std::ofstream migrates("migrates.sql", std::ios::out);
	Table migrate("Tag_part1");
	std::vector<std::string> fields;
	fields.push_back(std::string("description"));
	migrates << db.use();
	migrates << db.migrate(&migrate, fields, &tag, std::string("Tag_part2"));

	std::ofstream selects2("selects2.sql", std::ios::out);
	selects2 << db.use();
	selects2 << db.select(&user, &tag, JoinType::inner, 2);
	/*selects2 << db.select(&user, &tag, JoinType::left);
	selects2 << db.select(&user, &tag, JoinType::right);
	selects2 << db.select(&user, &tag, JoinType::outer);
	selects2 << db.select(&user, &tag, JoinType::left_excld);
	selects2 << db.select(&user, &tag, JoinType::right_excld);
	selects2 << db.select(&user, &tag, JoinType::outer_excld);*/

	return 0;
}

```

# G++ -v

Supporting g++ versions >= g++-4.8.x

```
ivo@ivo-Inspiron-5558:~$ g++ -v
Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/4.8/lto-wrapper
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 4.8.4-2ubuntu1~14.04.1' --with-bugurl=file:///usr/share/doc/gcc-4.8/README.Bugs --enable-languages=c,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-4.8 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.8 --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --enable-gnu-unique-object --disable-libmudflap --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64 --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-4.8-amd64 --with-arch-directory=amd64 --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.1)

```

# Output:

## No mysql installed or no access:

```
ivo@ivo-Inspiron-5558:~/MySql_OQM$ make
rm -f *.o sql *.sql
g++ -std=c++11 -Wall -c toUpper.cc
g++ -std=c++11 -Wall -c Table.cc
g++ -std=c++11 -Wall -c Connection.cc
g++ -std=c++11 -Wall -c DB.cc
g++ -std=c++11 -Wall -c Pattern.cc
g++ -std=c++11 -Wall -c Type.cc
g++ -std=c++11 -Wall -c hardcoded.cc
g++ -std=c++11 -Wall -o sql sql.cc toUpper.o Table.o Connection.o DB.o Pattern.o Type.o hardcoded.o
./sql
mkdir -p Borislav_Stratev_B_2 
mv *.sql Borislav_Stratev_B_2 
make clean
make[1]: Entering directory `/home/ivo/MySql_OQM'
rm -f *.o sql *.sql
make[1]: Leaving directory `/home/ivo/MySql_OQM'
mysql -u ivo  < Borislav_Stratev_B_2 /creates.sql
/bin/sh: 1: mysql: not found
make: *** [all] Error 127
ivo@ivo-Inspiron-5558:~/MySql_OQM$
ivo@ivo-Inspiron-5558:~/MySql_OQM$ ls Borislav_Stratev_B_2/
creates.sql  inserts.sql  migrates.sql  selects1.sql  selects2.sql
ivo@ivo-Inspiron-5558:~/MySql_OQM$ 

```

## With mysql and access:

```
ivo@ivo-Inspiron-5558:~/MySql_OQM$ make
rm -f *.o sql *.sql
g++ -std=c++11 -Wall -c toUpper.cc
g++ -std=c++11 -Wall -c Table.cc
g++ -std=c++11 -Wall -c Connection.cc
g++ -std=c++11 -Wall -c DB.cc
g++ -std=c++11 -Wall -c Pattern.cc
g++ -std=c++11 -Wall -c Type.cc
g++ -std=c++11 -Wall -c hardcoded.cc
g++ -std=c++11 -Wall -o sql sql.cc toUpper.o Table.o Connection.o DB.o Pattern.o Type.o hardcoded.o
./sql
mkdir -p Borislav_Stratev_B_2
mv *.sql Borislav_Stratev_B_2
make clean
make[1]: Entering directory `/home/ivo/MySql_OQM'
rm -f *.o sql *.sql
make[1]: Leaving directory `/home/ivo/MySql_OQM'
mysql -u ivo < Borislav_Stratev_B_2/creates.sql
mysql -u ivo < Borislav_Stratev_B_2/inserts.sql
mysqldump -u ivo exam > Borislav_Stratev_B_2/export1.sql
mysql -u ivo < Borislav_Stratev_B_2/selects1.sql
id
2
mysql -u ivo < Borislav_Stratev_B_2/migrates.sql
mysql -u ivo < Borislav_Stratev_B_2/selects2.sql
id
1
mysqldump -u ivo exam > Borislav_Stratev_B_2/export2.sql
ivo@ivo-Inspiron-5558:~/MySql_OQM$
```

# Examples:

https://github.com/NoHomey/NoHomey-_Rep/tree/master/sql
