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
        if (abs(coords[0]-x)==1 || abs(coords[1]-y)==1) return true;
        else return false;
        break;
    
    case 'Q':
        if ((abs(coords[0]-x)==0 || abs(coords[1]-y)==0) || abs(coords[0]-x)==abs(coords[1]-y))
            return true;
        else return false;
        break;
    
    case 'r':
        if (abs(coords[0]-x)==0 || abs(coords[1]-y)==0)
            return true;
        else return false;
        break;
    
    case 'b':
        if (abs(coords[0]-x)==abs(coords[1]-y)) 
            return true;
        else return false;
        break;
    
    case 'k':
        if (abs(coords[0]-x)==2 && abs(coords[1]-y)==1
        ||  abs(coords[1]-y)==2 && abs(coords[0]-x)==1)
            return true;
        else return false;
        break;
    
    case 'p':
        if (coords[1]-y==1*side_up && coords[0]-x==0)
            return true;
        else return false;
        
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

int Chess::move_type(int id, vector<int> crds){

    // -2 no move
    // -1 normal move
    // >0 eat move

    Piece curr=piece_list[id];
    int move_verf=piece_list[id].move_verified(crds);

    if (move_verf){

            if (get_piece(crds)>-1){

            Piece target=piece_list[get_piece(crds)];

            if (target.side_up==curr.side_up){
                return -1;
            }

            if (target.side_up==!(curr.side_up)){
                return 1;
            }

        } else return 0;
    }

    /*if (piece_list[id].piece_type=='p'){
        if (crds[1]-curr.y==1*piece_list[id].side_up && abs(crds[0]-curr.x)==1)
            return 1;
        
        if (crds[1]-curr.y==2*piece_list[id].side_up && abs(crds[0]-curr.x)==0 && ((curr.y==1 && curr.side_up) || (curr.y==6 && !(curr.side_up))))
            return 0;
    }*/
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

            if (select_piece!=-1){
                if (move_type(select_piece, {j,i})==0){
                    cout<<"\033[43m";
                }

                if (move_type(select_piece, {j,i})==1){
                    cout<<"\033[44m";
                }
            }
            
            if (cursor[0]==j && cursor[1]==i){
                cout << "\033[1;4m";
            }
            bool printed = false;
            for (int k = 0; k < 32; k++){
                if (piece_list[k].x == j && piece_list[k].y == i){

                    if (select_piece==k){
                        cout<<"\033[41m";
                    }

                    if (piece_list[k].side_up) {
                        cout << "\033[95m" << piece_list[k].piece_type << " ";  // Purple
                    } else {
                        cout << "\033[92m" << piece_list[k].piece_type << " ";  // Green
                    }
                    cout<<"\033[0m";
                    cout<<"\033[0m";
                    printed = true;
                    break;
                }
            }
            if (!printed) {
                cout << "O\033[0m ";  // Reset color for empty squares
            }
        }
        cout << "\033[0m" << endl;  // Reset after each line
    }
}

void Chess::move(int id, vector<int> coords){
    // check if move is possible
    int move_id=move_type(id,coords);
    int eaten_id=0;

    cout<<"MOVE ID : "<<move_id<<endl;

    if (move_id==1){
        cout<<"hello";
        eaten_id=get_piece(coords);
        piece_list[eaten_id].x=-1; piece_list[eaten_id].y=-1;
        piece_list[id].x=coords[0]; piece_list[id].y=coords[1];
    }

    if (move_id==0){
        cout<<"move normal";
        piece_list[id].x=coords[0]; piece_list[id].y=coords[1];
    }

}

int Chess::get_piece(vector<int> coords){
    for (int i=0;i<32;i++){
        if (piece_list[i].x==coords[0] && piece_list[i].y==coords[1]){
            return i;
        }
    }
    return -1;
}


Chess::~Chess(){ delete[] piece_list; piece_list=NULL;}

void display(){
    for (int i=0;i<8;i++){
        cout << "* * * * * * * *\n";
    }
}

/*int main(){
    Chess game;
    game.display();

    return 0;
}*/