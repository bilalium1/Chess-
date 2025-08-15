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
        int x_s, y_s;
        bool side_up = true;

        Piece(int id,vector<int> start_pos, int side, char p_t); // constructor
        Piece();
        ~Piece();
        bool move_verified(vector<int> crds);
};

class Chess {
    int16_t round = 0;
    Piece* piece_list;  // No more 'Piece' undefined error
    Piece* p1_list;
    Piece* p2_list;
    int p1_count = 0;
    int p2_count = 0;


    public:
        vector<int> cursor= {0,0};
        vector<int> select= {-1,-1};
        int select_piece=-1;
        Chess();
        ~Chess();
        int move(int id, vector<int> crds);
        void display(); 
        int get_piece(vector<int> crds);
        bool turn = true;
        bool is_check();
        bool is_checkmate();
        int move_type(int id, vector<int> crds);
        bool check_for_blockers(vector<int> target, Piece curr);
};

#endif
