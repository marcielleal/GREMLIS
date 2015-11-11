all:gremlins
gremlins:
	g++ -Wall -std=c++11 ./src/main.cpp -o ./bin/gremlins

clean:
	rm -f ./bin/gremlins
