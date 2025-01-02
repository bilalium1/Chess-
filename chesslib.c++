#include <iostream>
#include "chesslib.h"
#include <vector>
using namespace std;



Chess::Chess(vector<int> setup){

    piece_list = new Piece[16];
    
    int i=0,j=0;
        // king loop
        for (int i=0; i<setup[0]; i++,j++){piece_list[j]=King();}  
        // queen loop
        for (int i=0; i<setup[1]; i++,j++){piece_list[j]=Queen();}
        // rook loop
        for (int i=0; i<setup[2]; i++,j++){piece_list[j]=Rook();}
        // bishop loop
        for (int i=0; i<setup[3]; i++,j++){piece_list[j]=Knight();}
        // pawn loop
        for (int i=0; i<setup[4]; i++,j++){piece_list[j]=Pawn();}      
}

void Chess::display(){
    for (int i=0;i<8;i++){
        cout<<"";
    }
}

void display(){
    for (int i=0;i<8;i++){
        cout << "* * * * * * * *\n";
    }
}

int main(){
    display();

    return 0;
}