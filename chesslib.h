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
    char piece_type;
    int piece_id;
    bool side_up; // which team/side if the pawn on. 

    public:
        int x,y;

        Piece(int id,vector<int> start_pos, bool side, char p_t); // constructor
        Piece();
        ~Piece();
        char get_type();
        void move(); // move 
};

class Chess {
    int round = 0;

    public:
        Piece* piece_list;  // No more 'Piece' undefined error
        Chess();
        ~Chess();
        void display(); 
        void update(); 
};

#endif
