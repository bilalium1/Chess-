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
        int8_t piece_id;
        int8_t x,y;
        int8_t x_s, y_s;
        bool side_up = true;

        Piece(int8_t id,vector<int8_t> start_pos, int8_t side, char p_t); // constructor
        Piece();
        ~Piece();
        bool move_verified(vector<int8_t> crds);
};

class Chess {
    int16_t round = 0;
    Piece* piece_list;  // No more 'Piece' undefined error


    public:
        vector<int8_t> cursor= {0,0};
        vector<int8_t> select= {-1,-1};
        int8_t select_piece=-1;
        Chess();
        ~Chess();
        int move(int8_t id, vector<int8_t> crds);
        void display(); 
        int8_t get_piece(vector<int8_t> crds);
        bool turn = true;
        bool is_check();
        bool is_checkmate();
        int8_t move_type(int8_t id, vector<int8_t> crds);
        bool check_for_blockers(Piece target, Piece curr);
};

#endif
