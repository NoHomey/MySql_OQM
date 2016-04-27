compile=g++ -std=c++11 -Wall

folder=Borislav_Stratev_B_2

db=exam

user=-u ivo

sql=mysql $(user) <

dump=mysqldump $(user) $(db) >

all: clean toUpper.o Table.o Connection.o DB.o Pattern.o Type.o hardcoded.o
	$(compile) -o sql sql.cc toUpper.o Table.o Connection.o DB.o Pattern.o Type.o hardcoded.o
	./sql
	mkdir -p $(folder)
	mv *.sql $(folder)
	make clean
	$(sql) $(folder)/creates.sql
	$(sql) $(folder)/inserts.sql
	$(dump) $(folder)/export1.sql
	$(sql) $(folder)/selects1.sql
	$(sql) $(folder)/migrates.sql
	$(sql) $(folder)/selects2.sql
	$(dump) $(folder)/export2.sql

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

generate_exam:
	rm -f exam.txt
	prev=1
	ruby $(repo)/generate_exams/main.rb $(num) > exam.txt
