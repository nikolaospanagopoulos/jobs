FLAGS= -Wall -std=c++20
LIB = -lcrypt -lmariadbcpp

OBJECTS=./build/Models/User.o ./build/Routes/UserRoutes.o ./build/Database/Database.o ./build/helpers.o

all: ${OBJECTS}
	g++ ${FLAGS} -o ./bin/main ./src/main.cpp ${OBJECTS} ${LIB}
./build/Models/User.o:
	g++ ./src/Models/User.cpp -c -o ./build/Models/User.o
./build/Routes/UserRoutes.o:
	g++ ./src/Routes/UserRoutes.cpp -c -o ./build/Routes/UserRoutes.o
./build/Database/Database.o:
	g++ ./src/Database/Database.cpp -c -o ./build/Database/Database.o
./build/helpers.o:
	g++ ./src/helpers.cpp -c -o ./build/helpers.o
clean:
	rm ./build/*/*.o
