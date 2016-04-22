compile = g++ -std=c++11 -Wall

folder = Ivo_Stratev_B_16

db = exam

user = -u ivo

sql = mysql $(user) <

dump = mysqldump $(user) $(db) >

all: clean toUpper.o Table.o Connection.o DB.o Pattern.o Type.o hardcoded.o
	$(compile) -o sql sql.cc toUpper.o Table.o Connection.o DB.o Pattern.o Type.o hardcoded.o
	./sql
	mkdir -p $(folder)
	mv *.sql $(folder)
	make clean
	cd $(folder)
	$(sql) creates.sql
	$(sql) inserts.sql
	$(dump) export1.sql
	$(sql) selects1.sql
	$(sql) migrates.sql
	$(sql) selects2.sql
	$(dump) export2.sql

toUpper.o:
	$(compile) -c toUpper.cc

Table.o:
	$(compile) -c Table.cc

Connection.o:
	$(compile) -c Connection.cc

DB.o:
	$(compile) -c DB.cc

Pattern.o:
	$(compile) -c Pattern.cc

Type.o:
	$(compile) -c Type.cc

hardcoded.o:
	$(compile) -c hardcoded.cc

clean:
	rm -f *.o sql *.sql

run_sql:
	mysql -u ivo < file.sql

dumb:
	mysqldumb $(db) > file.sql
