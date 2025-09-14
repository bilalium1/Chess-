all : 
	g++ src/main.c++ src/chesslib.c++ -o main.exe
	g++ src/main_linux.c++ src/chesslib.c++ -o main.out