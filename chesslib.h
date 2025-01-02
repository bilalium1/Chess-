#ifndef CHESS_H
#define CHESS_H
#include <vector>
using namespace std;

const vector<int> chess_setup = {1,1,2,2,2,8}; // {kings, queens, rooks, bishops, knights, pawns}

class Chess {
    int round=0;

    public:
        Piece* piece_list;
        // game setup , {kings, queens, rooks, bishops, knights, pawns}
        Chess(vector<int> setup);

        void display(); // this function display the current situation lul
        void update(); // this function updates the game depending on the input

};

class Piece {

    int piece_id;
    vector<int> start_pos; // start position
    vector<int> current_pos; // current position
    bool side; // which team/side if the pawn on. 

    public:
        Piece(); // constructor
        ~Piece(){}
        vector<int> get_pos(); // get position
        void move(); // move 
};

class Pawn : public Piece {};

class Knight : public Piece {};

class Bishop : public Piece {};

class Rook : public Piece {};

class Queen : public Piece {};

class King : public Piece {};

#endif