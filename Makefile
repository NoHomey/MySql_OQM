compile = g++ -std=c++11 -Wall

folder = Borislav_Stratev_B_2

db = exam

all: clean toUpper.o Table.o DB.o Pattern.o Type.o hardcoded.o
	$(compile) -o sql sql.cc toUpper.o Table.o DB.o Pattern.o Type.o hardcoded.o
	./sql
	mkdir -p $(folder)
	mv *.sql $(folder)
	make clean

toUpper.o:
	$(compile) -c toUpper.cc

Table.o:
	$(compile) -c Table.cc

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
