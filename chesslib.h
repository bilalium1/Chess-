#ifndef CHESS_H
#define CHESS_H
#include <vector>
using namespace std;

class Piece {
    Piece(int x, int y); // constructor

    vector<int> start_pos; // start position
    vector<int> current_pos; // current position
    bool side; // which team/side if the pawn on. 

    public:
        vector<int> get_pos(); // get position
        void move(); // move 
};

class Pawn : public Piece {
    int pawn_id;

    Pawn(int x, int y);
};


#endif