#ifndef CHESS_H
#define CHESS_H
#include <vector>
using namespace std;

// piece types
// pawn 0
// king 1
// queen 2
// rook 3
// bishop 4
// knight 5

const vector<int> chess_setup = {1,1,2,2,2,8}; // {kings, queens, rooks, bishops, knights, pawns}

class Piece {

    public:
        char piece_type;
        int piece_id;
        int x,y;
        bool side_up;

        Piece(int id,vector<int> start_pos, bool side, char p_t); // constructor
        Piece();
        ~Piece();
        bool move_verified(vector<int> coords);
};

class Chess {
    int round = 0;
    Piece* piece_list;  // No more 'Piece' undefined error


    public:
        vector<int> cursor={0,0};
        vector<int> select={-1,-1};
        int select_piece=-1;
        Chess();
        ~Chess();
        void move(int id, vector<int> coords);
        void display(); 
        int get_piece(vector<int> coords);
        bool is_check();
        bool is_checkmate();
        int move_type(int id, vector<int> crds);
};

#endif
