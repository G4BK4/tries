all: tet

tet: build/main.o build/foo.o build/node.o
	g++ build/main.o build/foo.o build/node.o -o tet 
build/main.o: src/main.cpp
	g++ -Wall -Werror -o build/main.o -c src/main.cpp
build/foo.o: src/foo.cpp
	g++ -Wall -Werror -o build/foo.o -c src/foo.cpp  
build/node.o: src/node.cpp
	g++ -Wall -Werror -o build/node.o -c src/node.cpp  
clean:
	rm -rf build/* tet 