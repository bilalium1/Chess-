#include <iostream>
#include "chesslib.h"
#include <vector>

using namespace std;
 // {kings, queens, rooks, bishops, knights, pawns}

Piece::Piece(int id, vector<int> s_pos, int side, char p_t){
    piece_id=id; x=s_pos[0]; y=s_pos[1]; side_up=side; piece_type=p_t; x_s=s_pos[0]; y_s=s_pos[1]; 
}

Piece::Piece(){piece_id=0; x=0; y=0; side_up=1; piece_type=' '; x_s=0; y_s=0;}
Piece::~Piece(){}

bool king_verify(int x, int y, vector<int> crds){
    if (abs(crds[0]-x) + abs(crds[1]-y)<3 && !(abs(crds[0]-x)==2 || abs(crds[1]-y)==2)) return true;
    else return false;
}

bool rook_verify(int x, int y, vector<int> crds){
    if (abs(crds[0]-x)==0 || abs(crds[1]-y)==0)
        return true;
    else return false;
}

bool bishop_verify(int x, int y, vector<int> crds){
    if (abs(crds[0]-x)==abs(crds[1]-y)) 
        return true;
    else return false;
}

bool knight_verify(int x, int y, vector<int> crds){
    if (abs(crds[0]-x)==2 && abs(crds[1]-y)==1 ||  abs(crds[1]-y)==2 && abs(crds[0]-x)==1)
        return true;
    else return false;
}

bool Chess::check_for_blockers(vector<int> target, Piece curr){

    if (curr.piece_type=='k')
        return false;

    int dx=target[0]-curr.x;
    int dy=target[1]-curr.y;

    vector<int> crd = {target[0], target[1]};

    dx = (dx == 0 ? 0 : dx / abs(dx));
    dy = (dy == 0 ? 0 : dy / abs(dy));

    crd[0] -= dx;
    crd[1] -= dy;

    while (crd[0] != curr.x || crd[1] != curr.y)
    {

        if (get_piece(crd) > -1)
            return true;
        
        crd[0] -= dx;
        crd[1] -= dy;
    }

    return false;
    
}

bool Piece::move_verified(vector<int> crds){

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
    p1_list = new Piece[16];
    p2_list = new Piece[16];
    
    int j=0;

    // UPSIDE TEAM
    // king
    piece_list[j]=Piece(j, {4,0},true, 'K'); ++j;
    piece_list[j]=Piece(j, {4,0},true, 'K'); ++j;
    // queen 
    piece_list[j]=Piece(j, {3,0},true, 'Q'); ++j;
    piece_list[j]=Piece(j, {3,0},true, 'Q'); ++j;
    // rooks
    piece_list[j]=Piece(j, {0,0},true, 'r'); ++j;
    piece_list[j]=Piece(j, {7,0},true, 'r'); ++j;
    piece_list[j]=Piece(j, {0,0},true, 'r'); ++j;
    piece_list[j]=Piece(j, {7,0},true, 'r'); ++j;
    // bishops
    piece_list[j]=Piece(j, {1,0},true, 'b'); ++j;
    piece_list[j]=Piece(j, {6,0},true, 'b'); ++j;
    piece_list[j]=Piece(j, {1,0},true, 'b'); ++j;
    piece_list[j]=Piece(j, {6,0},true, 'b'); ++j;
    // knights
    piece_list[j]=Piece(j, {2,0},true, 'k'); ++j;
    piece_list[j]=Piece(j, {5,0},true, 'k'); ++j;
    for (int i=0; i<8; i++,j++)
        {piece_list[j]=Piece(j,{i,1},true,'p');} 

    // DOWNSIDE TEAM

    piece_list[j]=Piece(j, {4,7},false, 'K'); ++j;
    piece_list[j]=Piece(j, {4,7},false, 'K'); ++j;
    // queen 
    piece_list[j]=Piece(j, {3,7},false, 'Q'); ++j;
    piece_list[j]=Piece(j, {3,7},false, 'Q'); ++j;
    // rooks
    piece_list[j]=Piece(j, {0,7},false, 'r'); ++j;
    piece_list[j]=Piece(j, {7,7},false, 'r'); ++j;
    piece_list[j]=Piece(j, {0,7},false, 'r'); ++j;
    piece_list[j]=Piece(j, {7,7},false, 'r'); ++j;
    // bishops
    piece_list[j]=Piece(j, {1,7},false, 'b'); ++j;
    piece_list[j]=Piece(j, {6,7},false, 'b'); ++j;
    piece_list[j]=Piece(j, {1,7},false, 'b'); ++j;
    piece_list[j]=Piece(j, {6,7},false, 'b'); ++j;
    // knights
    piece_list[j]=Piece(j, {2,7},false, 'k'); ++j;
    piece_list[j]=Piece(j, {5,7},false, 'k'); ++j;
    for (int i=0; i<8; i++,j++)
        {piece_list[j]=Piece(j,{i,6},false,'p');}
}

int Chess::move_type(int id, vector<int> crds){

    // -1 no move
    // 0 normal move
    // 1 eat move
    // -1 no move
    // 0 normal move
    // 1 eat move

    Piece curr=piece_list[id];
    int move_verf=piece_list[id].move_verified(crds);
    int target_id=get_piece(crds);

    if (target_id == id)
        return -1;

    if (target_id > -1 && piece_list[target_id].side_up==curr.side_up){
        // ally piece
        return -1;
    }

    if (curr.piece_type == 'p') {

        int coeff = (curr.side_up) ? 1 : -1; 

        int coeff = (curr.side_up) ? 1 : -1; 

        if (crds[0]-curr.x==0) {
            // Forward movement
            if (crds[1]-curr.y==1*coeff && get_piece(crds)==-1) return 0;
            else if (crds[1] - curr.y == 2 * coeff && curr.y == curr.y_s && get_piece(crds) == -1) return 0;
            if (crds[1]-curr.y==1*coeff && get_piece(crds)==-1) return 0;
            else if (crds[1] - curr.y == 2 * coeff && curr.y == curr.y_s && get_piece(crds) == -1) return 0;
            else return -1;
        } else if (abs(crds[0] - curr.x)==1 && crds[1]-curr.y==1*coeff) {
        } else if (abs(crds[0] - curr.x)==1 && crds[1]-curr.y==1*coeff) {
            // Diagonal capture'
            if (target_id > -1) return 1;
            else return -1;
        } else {
            return -1; // Invalid move
        }
    }

    if (move_verf){

        if (check_for_blockers(crds, curr))
            return -1;

        if (get_piece(crds)>-1){
            Piece target=piece_list[get_piece(crds)];

            if (target.side_up!=curr.side_up)
                return 1;
        } 
        else 
            return 0;
    }

}

void Chess::display(){

    int i = 0;

    if (turn)
    {
        cout << "\033[1;45m Player 1";
        i = p1_count;
        while (i >= 0)
            cout << p1_list[i--].piece_type << " < ";
        cout << " \033[0m" << endl;
    }
    else
    {
        cout << "\033[1;42m Player 2";
        i = p2_count;
        while (i >= 0)
            cout << p2_list[i--].piece_type << " < ";
        cout << " \033[0m" << endl;
    }
    
    cout<<endl;
    cout << "\033[47m\033[30m   A B C D E F G H   \033[0m\n";

    for (int i = 0; i < 8; i++){
        cout << "\033[47m\033[30m"<< i+1 << " \033[0m ";
        for (int j = 0; j < 8; j++){

            if (select_piece!=-1 && (cursor[0]!=j || cursor[1]!=i)){
            if (select_piece!=-1 && (cursor[0]!=j || cursor[1]!=i)){
                if (move_type(select_piece, {j,i})==0){
                    cout<<"\033[43m"; // YELLOW BACKGROUND, MOVE
                    cout<<"\033[43m"; // YELLOW BACKGROUND, MOVE
                }

                if (move_type(select_piece, {j,i})==1){
                    cout<<"\033[44m"; // BLUE BACKGROUND, EAT
                    cout<<"\033[44m"; // BLUE BACKGROUND, EAT
                }
            }
            
            if (cursor[0]==j && cursor[1]==i){
                if (turn)
                    cout << "\033[45m\033[30m";
                else 
                    cout << "\033[42m\033[30m";
            }

            bool printed = false;
            for (int k = 0; k < 32; k++){
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
                cout << "-\033[0m ";  // Reset color for empty squares
            }
        }
        cout << "\033[47m\033[30m  \033[0m";
        cout << "\033[0m" << endl;  // Reset after each line
    }
    cout << "\033[47m\033[30m                     \033[0m";
}

int Chess::move(int id, vector<int> crds){
    // check if move is possible
    int move_id=move_type(id,crds);
    int eaten_id=0;

    cout<<"MOVE ID : "<<move_id<<endl;

    if (move_id==1){
        eaten_id=get_piece(crds);
        piece_list[eaten_id].x=-1; piece_list[eaten_id].y=-1;
        piece_list[id].x=crds[0]; piece_list[id].y=crds[1];

        if (piece_list[id].side_up) p1_list[p1_count++] = piece_list[eaten_id];

        else p2_list[p2_count++] = piece_list[eaten_id];
    }

    if (move_id==0){
        cout<<"move normal";
        piece_list[id].x=crds[0]; piece_list[id].y=crds[1];
    }

    return move_id;

    return move_id;

}

int Chess::get_piece(vector<int> crds){
    for (int i=0;i<32;i++){
        if (piece_list[i].x==crds[0] && piece_list[i].y==crds[1]){
            return i;
        }
    }
    return -1;
}


Chess::~Chess(){ 
    delete[] piece_list; piece_list=NULL;
    delete[] p1_list; p1_list=NULL;
    delete[] p2_list; p2_list=NULL;
}

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