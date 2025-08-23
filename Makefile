all : 
	g++ main.c++ chesslib.c++ -o main.exe
	g++ main_linux.c++ chesslib.c++ -o main.out