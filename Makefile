#make get class=А/Б num=[1..29]
#make
#make picture
#make tar
#make post

compile=g++ -std=c++11 -Wall

folder=Borislav_Stratev_B_2

db=exam

user=ivo

ip=192.168.0.103

sql=mysql -u $(user) <

dump=mysqldump -u $(user) $(db) >

exams=student@$(ip):/home/student/local/subd_exam

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

get:
	scp $(exams)/$(class)_$(num)_* .

tar:
	tar -zcvf $(folder).tar.gz $(folder)

zip:
	zip -r $(folder).zip $(folder)

post:
	scp $(folder).* $(exams)/

picture:
	mysql-workbench

rm_folder:
	rm -Rf $(folder)*

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
	ruby ./../elsys-db-practices/generate_exams/main.rb $(num) > exam.txt

publish:
	mkdir ./../NoHomey-_Rep/sql/new_$(n)
	mv exam.txt ./../NoHomey-_Rep/sql/new_$(n)
	cp sql.cc ./../NoHomey-_Rep/sql/new_$(n)
	cd ../NoHomey-_Rep && git add -A && git commit -m "one more" && git push
