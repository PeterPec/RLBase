all:
	g++ -o run -I ./include -L ./lib ./src/*.cpp -ltcod -ltcodxx -Wall -Wl,-rpath=./lib
