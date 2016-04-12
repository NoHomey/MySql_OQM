all: clean toUpper.o Table.o DB.o Pattern.o
	g++ -std=c++11 -o sql sql.cc toUpper.o Table.o DB.o Pattern.o

toUpper.o:
	g++ -std=c++11 -c toUpper.cc

Table.o:
	g++ -std=c++11 -c Table.cc

DB.o:
	g++ -std=c++11 -c DB.cc

Pattern.o:
	g++ -std=c++11 -c Pattern.cc

clean:
	rm -f *.o sql
