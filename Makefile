all: win lin

win: main.exe

main.exe: src/main.c++ src/chesslib.c++
	g++ src/main.c++ src/chesslib.c++ -o main.exe

lin: main.out

main.out: src/main_linux.c++ src/chesslib.c++
	g++ src/main_linux.c++ src/chesslib.c++ -o main.out
