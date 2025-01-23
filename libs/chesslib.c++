#include <iostream>
#include "chesslib.h"
#include <vector>
using namespace std;
 // {kings, queens, rooks, bishops, knights, pawns}

Piece::Piece(int8_t id, vector<int8_t> s_pos, int8_t side, char p_t){
    piece_id=id; x=s_pos[0]; y=s_pos[1]; side_up=side; piece_type=p_t; x_s=s_pos[0]; y_s=s_pos[1]; 
}

Piece::Piece(){piece_id=0; x=0; y=0; side_up=1; piece_type=' '; x_s=0; y_s=0;}
Piece::~Piece(){}

bool king_verify(int8_t x, int8_t y, vector<int8_t> crds){
    if (abs(crds[0]-x) + abs(crds[1]-y)<3 && !(abs(crds[0]-x)==2 || abs(crds[1]-y)==2)) return true;
    else return false;
}

bool rook_verify(int8_t x, int8_t y, vector<int8_t> crds){
    if (abs(crds[0]-x)==0 || abs(crds[1]-y)==0)
        return true;
    else return false;
}

bool bishop_verify(int8_t x, int8_t y, vector<int8_t> crds){
    if (abs(crds[0]-x)==abs(crds[1]-y)) 
        return true;
    else return false;
}

bool knight_verify(int8_t x, int8_t y, vector<int8_t> crds){
    if (abs(crds[0]-x)==2 && abs(crds[1]-y)==1 ||  abs(crds[1]-y)==2 && abs(crds[0]-x)==1)
        return true;
    else return false;
}

bool Chess::check_for_blockers(Piece target, Piece curr){

    int8_t dx=target.x-curr.x;
    int8_t dy=target.y-curr.y;

    if (dx==0){
        while (dy!=0){
            dy-=curr.side_up;
            if (get_piece({curr.x, static_cast<int8_t>(curr.y + dy)})) return true;
        }
    }
    else if (dy==0)
    {
        while (dx!=0){
            dx-=curr.side_up;
            if (get_piece({curr.y, static_cast<int8_t>(curr.x + dx)})) return true;
        }
    }
    else {
        while (dx!=0 && dy!=0){
            dy-=curr.side_up;
            dx-=curr.side_up;
            if (get_piece({static_cast<int8_t>(curr.x + dx), static_cast<int8_t>(curr.y + dy)})) return true;
        }
    }

    return false;
    
}

bool Piece::move_verified(vector<int8_t> crds){

    switch (piece_type)
    {
    case 'K':
        return king_verify(x,y,crds);
    
    case 'Q':
        return (rook_verify(x,y,crds) || bishop_verify(x,y,crds));
    
    case 'r':
        return rook_verify(x,y,crds);
    
    case 'b':
        return bishop_verify(x,y,crds);
    
    case 'k':
        return knight_verify(x,y,crds);
    case 'p':
        return true;
    
    default:
        break;
    }

}

Chess::Chess(){

    piece_list = new Piece[32];
    
    int8_t j=0;

    // UPSIDE TEAM
    // king
    piece_list[j]=Piece(j, {4,0},1, 'K'); ++j;
    // queen 
    piece_list[j]=Piece(j, {3,0},1, 'Q'); ++j;
    // rooks
    piece_list[j]=Piece(j, {0,0},1, 'r'); ++j;
    piece_list[j]=Piece(j, {7,0},1, 'r'); ++j;
    // bishops
    piece_list[j]=Piece(j, {1,0},1, 'b'); ++j;
    piece_list[j]=Piece(j, {6,0},1, 'b'); ++j;
    // knights
    piece_list[j]=Piece(j, {2,0},1, 'k'); ++j;
    piece_list[j]=Piece(j, {5,0},1, 'k'); ++j;
    for (int8_t i=0; i<8; i++,j++)
        {piece_list[j]=Piece(j,{i,1},1,'p');} 

    // DOWNSIDE TEAM

    piece_list[j]=Piece(j, {4,7},-1, 'K'); ++j;
    // queen 
    piece_list[j]=Piece(j, {3,7},-1, 'Q'); ++j;
    // rooks
    piece_list[j]=Piece(j, {0,7},-1, 'r'); ++j;
    piece_list[j]=Piece(j, {7,7},-1, 'r'); ++j;
    // bishops
    piece_list[j]=Piece(j, {1,7},-1, 'b'); ++j;
    piece_list[j]=Piece(j, {6,7},-1, 'b'); ++j;
    // knights
    piece_list[j]=Piece(j, {2,7},-1, 'k'); ++j;
    piece_list[j]=Piece(j, {5,7},-1, 'k'); ++j;
    for (int8_t i=0; i<8; i++,j++)
        {piece_list[j]=Piece(j,{i,6},-1,'p');}
}

int8_t Chess::move_type(int8_t id, vector<int8_t> crds){

    // -2 no move
    // -1 normal move
    // >0 eat move

    Piece curr=piece_list[id];
    int8_t move_verf=piece_list[id].move_verified(crds);
    int8_t target_id=get_piece(crds);

    if (target_id>-1 && piece_list[target_id].side_up){
        // ally piece
        // test if its blocking the way
        if (check_for_blockers(piece_list[target_id], curr)) return -1;
        else return 0;
    }

    if (curr.piece_type == 'p') {

        if (crds[0]-curr.x==0) {
            // Forward movement
            if (crds[1]-curr.y==1*curr.side_up && get_piece(crds)==-1) return 0;
            else if (crds[1] - curr.y == 2 * curr.side_up && curr.y == curr.y_s && get_piece(crds) == -1) return 0;
            else return -1;
        } else if (abs(crds[0] - curr.x)==1 && crds[1]-curr.y==1*curr.side_up) {
            // Diagonal capture'
            int8_t id;
            if (id > -1) return 1;
            else return -1;
        } else {
            return -1; // Invalid move
        }
    }

    if (move_verf){

            if (get_piece(crds)>-1){

            Piece target=piece_list[get_piece(crds)];

            if (target.side_up==!(curr.side_up)){
                return 1;
            }

        } else return 0;
    }

}

void Chess::display(){
    cout<<endl;
    cout << "  0 1 2 3 4 5 6 7\n";

    for (int8_t i = 0; i < 8; i++){
        cout << i+1 << " ";
        for (int8_t j = 0; j < 8; j++){

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
            for (int8_t k = 0; k < 32; k++){
                if (piece_list[k].x == j && piece_list[k].y == i){

                    if (select_piece==k){
                        cout<<"\033[41m";
                    }

                    if (piece_list[k].side_up==1) {
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

void Chess::move(int8_t id, vector<int8_t> crds){
    // check if move is possible
    int8_t move_id=move_type(id,crds);
    int8_t eaten_id=0;

    cout<<"MOVE ID : "<<move_id<<endl;

    if (move_id==1){
        cout<<"hello";
        eaten_id=get_piece(crds);
        piece_list[eaten_id].x=-1; piece_list[eaten_id].y=-1;
        piece_list[id].x=crds[0]; piece_list[id].y=crds[1];
    }

    if (move_id==0){
        cout<<"move normal";
        piece_list[id].x=crds[0]; piece_list[id].y=crds[1];
    }

}

int8_t Chess::get_piece(vector<int8_t> crds){
    for (int8_t i=0;i<32;i++){
        if (piece_list[i].x==crds[0] && piece_list[i].y==crds[1]){
            return i;
        }
    }
    return -1;
}


Chess::~Chess(){ delete[] piece_list; piece_list=NULL;}

void display(){
    for (int8_t i=0;i<8;i++){
        cout << "* * * * * * * *\n";
    }
}

/*int main(){
    Chess game;
    game.display();

    return 0;
}*/