#include <iostream>
#include "chesslib.h"
#include <vector>
using namespace std;
 // {kings, queens, rooks, bishops, knights, pawns}

Piece::Piece(int id, vector<int> s_pos, bool side, char p_t){
    piece_id=id; x=s_pos[0]; y=s_pos[1]; side_up=side; piece_type=p_t;
}

Piece::Piece(){piece_id=0; x=0, y=0; side_up=false; piece_type=' ';}
char Piece::get_type(){return piece_type;}
Piece::~Piece(){}

Chess::Chess(){

    piece_list = new Piece[32];
    
    int j=0;

    // UPSIDE TEAM
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
    piece_list[j]=Piece(j, {2,0},false, 'k'); ++j;
    piece_list[j]=Piece(j, {5,0},false, 'k'); ++j;
    for (int i=0; i<8; i++,j++)
        {piece_list[j]=Piece(j,{i,1},false,'p');} 

    // DOWNSIDE TEAM

    piece_list[j]=Piece(j, {4,7},true, 'K'); ++j;
    // queen 
    piece_list[j]=Piece(j, {3,7},true, 'Q'); ++j;
    // rooks
    piece_list[j]=Piece(j, {0,7},true, 'r'); ++j;
    piece_list[j]=Piece(j, {7,7},true, 'r'); ++j;
    // bishops
    piece_list[j]=Piece(j, {1,7},true, 'b'); ++j;
    piece_list[j]=Piece(j, {6,7},true, 'b'); ++j;
    // knights
    piece_list[j]=Piece(j, {2,7},true, 'k'); ++j;
    piece_list[j]=Piece(j, {5,7},true, 'k'); ++j;
    for (int i=0; i<8; i++,j++)
        {piece_list[j]=Piece(j,{i,6},true,'p');}
}

void Chess::display(){
    cout << "  0 1 2 3 4 5 6 7\n";
    for (int i = 0; i < 8; i++){
        cout << i << " ";
        for (int j = 0; j < 8; j++){
            bool printed = false;
            for (int k = 0; k < 32; k++){
                if (piece_list[k].x == j && piece_list[k].y == i){
                    if (piece_list[k].side_up) {
                        cout << "\033[97m" << piece_list[k].get_type() << " ";  // White Pieces
                    } else {
                        cout << "\033[94m" << piece_list[k].get_type() << " ";  // Black Pieces
                    }
                    printed = true;
                    break;
                }
            }
            if (!printed) {
                cout << "\033[0m# ";  // Reset color for empty squares
            }
        }
        cout << "\033[0m" << endl;  // Reset after each line
    }
}


Chess::~Chess(){ delete[] piece_list; piece_list=NULL;}

void display(){
    for (int i=0;i<8;i++){
        cout << "* * * * * * * *\n";
    }
}

int main(){
    Chess game;
    game.display();

    return 0;
}