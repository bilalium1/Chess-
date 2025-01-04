#include <iostream>
#include "chesslib.h"
#include <vector>
using namespace std;
 // {kings, queens, rooks, bishops, knights, pawns}

Piece::Piece(int id, vector<int> s_pos, bool side, char p_t){
    piece_id=id; x=s_pos[0]; y=s_pos[1]; side_up=side; piece_type=p_t;
}

Piece::Piece(){piece_id=0; x=0, y=0; side_up=false; piece_type=' ';}
Piece::~Piece(){}

bool Piece::move_verified(vector<int> coords){

    switch (piece_type)
    {
    case 'K':
        if (coords[0]-x==1 || coords[1]-y==1) return true;
        else return false;
        break;
    
    case 'Q':
        if (coords[0]-x==0 || coords[1]-y==1 || (coords[0]-x==coords[1]-y))
            return true;
        else return false;
        break;
    
    case 'r':
        if (coords[0]-x==0 || coords[1]-y==1)
            return true;
        else return false;
        break;
    
    case 'b':
        if (coords[0]-x==coords[1]-y) 
            return true;
        else return false;
        break;
    
    case 'k':
        if (abs(coords[0]-x)==2 && abs(coords[1]-y)==1
        ||  abs(coords[1]-y)==1 && abs(coords[0]-x)==1)
            return 1;
        else return 0;
        break;
    
    case 'p':
        /* code */
        break;
    
    default:
        break;
    }

}

Chess::Chess(){

    piece_list = new Piece[32];
    
    int j=0;

    // UPSIDE TEAM
    // king
    piece_list[j]=Piece(j, {4,0},true, 'K'); ++j;
    // queen 
    piece_list[j]=Piece(j, {3,0},true, 'Q'); ++j;
    // rooks
    piece_list[j]=Piece(j, {0,0},true, 'r'); ++j;
    piece_list[j]=Piece(j, {7,0},true, 'r'); ++j;
    // bishops
    piece_list[j]=Piece(j, {1,0},true, 'b'); ++j;
    piece_list[j]=Piece(j, {6,0},true, 'b'); ++j;
    // knights
    piece_list[j]=Piece(j, {2,0},true, 'k'); ++j;
    piece_list[j]=Piece(j, {5,0},true, 'k'); ++j;
    for (int i=0; i<8; i++,j++)
        {piece_list[j]=Piece(j,{i,1},true,'p');} 

    // DOWNSIDE TEAM

    piece_list[j]=Piece(j, {4,7},false, 'K'); ++j;
    // queen 
    piece_list[j]=Piece(j, {3,7},false, 'Q'); ++j;
    // rooks
    piece_list[j]=Piece(j, {0,7},false, 'r'); ++j;
    piece_list[j]=Piece(j, {7,7},false, 'r'); ++j;
    // bishops
    piece_list[j]=Piece(j, {1,7},false, 'b'); ++j;
    piece_list[j]=Piece(j, {6,7},false, 'b'); ++j;
    // knights
    piece_list[j]=Piece(j, {2,7},false, 'k'); ++j;
    piece_list[j]=Piece(j, {5,7},false, 'k'); ++j;
    for (int i=0; i<8; i++,j++)
        {piece_list[j]=Piece(j,{i,6},false,'p');}
}

void Chess::display(){
    for (int i=0;i<32;i++){
        cout<<piece_list[i].piece_id<<":"<<piece_list[i].piece_type;
        if (piece_list[i].side_up) cout<<"1"; else cout<<"2";
        cout<<", ";
    }
    cout<<endl;
    cout << "  0 1 2 3 4 5 6 7\n";

    for (int i = 0; i < 8; i++){
        cout << i << " ";
        for (int j = 0; j < 8; j++){
            bool printed = false;
            for (int k = 0; k < 32; k++){
                if (piece_list[k].x == j && piece_list[k].y == i){
                    if (piece_list[k].side_up) {
                        cout << "\033[95m" << piece_list[k].piece_type << " ";  // Purple
                    } else {
                        cout << "\033[92m" << piece_list[k].piece_type << " ";  // Green
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

void Chess::move(int id, vector<int> coords){
    // check if move is possible
    bool verified=piece_list[id].move_verified(coords);
    bool is_eat=false;
    bool is_collision=false;
    int eaten_id=0;

    // check if place is already take or its an eat move
    for (int i=0;i<32;i++){
        if (i!=id && piece_list[i].x==coords[0] && piece_list[i].y==coords[1]){
            is_collision=(piece_list[i].side_up==piece_list[i].side_up);
            is_eat=!(piece_list[i].side_up==piece_list[i].side_up);
            if (is_eat){eaten_id=i;}
        }
    }

    if (verified){
        // collision
        if (is_collision) cout<<"move impossible : place already taken.";
        // eat
        if (is_eat) 
        {cout<<"piece "<<piece_list[eaten_id].piece_type<<" eaten!"; 
        piece_list[eaten_id].piece_id=-1;
        piece_list[id].x=coords[0]; piece_list[id].y=coords[1];} 
        // move
        if (is_collision==false && is_eat==false)
        {cout<<"move done!"; piece_list[id].x=coords[0]; piece_list[id].y=coords[1];}
    }
    else cout<<"This move is not possible! \n";
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