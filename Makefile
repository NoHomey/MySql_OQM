compile = g++ -std=c++11 -Wall

all: clean toUpper.o Table.o DB.o Pattern.o Type.o
	$(compile) -o sql sql.cc toUpper.o Table.o DB.o Pattern.o Type.o

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

clean:
	rm -f *.o sql
