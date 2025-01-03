#include <iostream>
#include "chesslib.h"
#include <vector>
using namespace std;
 // {kings, queens, rooks, bishops, knights, pawns}

Piece::Piece(int id, vector<int> s_pos, bool side, char p_t){
    piece_id=id; x=s_pos[0]; x=s_pos[1]; side_up=side; piece_type=p_t;
}

Piece::Piece(){piece_id=0; x=0, y=0; side_up=false; piece_type=' ';}
char Piece::get_type(){return piece_type;}
Piece::~Piece(){}

Chess::Chess(){

    piece_list = new Piece[16];
    
    int i=0,j=0;
    // king
    piece_list[j]=Piece(j, {4,0},false, 'K'); ++j;
    // queen 
    piece_list[j]=Piece(j, {3,0},false, 'Q'); ++j;
    // rooks
    piece_list[j]=Piece(j, {0,0},false, 'r'); ++j;
    piece_list[j]=Piece(j, {7,0},false, 'r'); ++j;
    // bishops
    piece_list[j]=Piece(j, {1,0},false, 'b'); ++j;
    piece_list[j]=Piece(j, {6,0},false, 'b'); ++j;
    // knights
    piece_list[j]=Piece(j, {3,0},false, 'k'); ++j;
    piece_list[j]=Piece(j, {5,0},false, 'k'); ++j;
    for (int i=0; i<8; i++,j++)
        {piece_list[j]=Piece(j,{i,1},false,0);}      
}

Chess::~Chess(){ delete[] piece_list;}

void Chess::display(){
    for (int i=0;i<8;i++){
        for(int j=0;i<8;i++){
            for(int k=0;i<16;k++){
                if (piece_list[k].x==j && piece_list[k].y==i){
                    cout << piece_list[k].get_type()<<" ";
                }
                else cout << "* ";
            }
        }
        cout << endl;
    }
}

void display(){
    for (int i=0;i<8;i++){
        cout << "* * * * * * * *\n";
    }
}

int main(){
    display();
    Chess game;
    game.display();
    cout << "Hello";

    return 0;
}