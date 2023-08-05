#include <iostream>
#include <array>
#include "move.cpp"

/**
 * This file contains functions that are used to get a static evaluation of a board position (an evaluation
 * which is reached without having to look any further into the position).
*/

int negative_infinity = -1000000;
int positive_infinity = 1000000;

using namespace std;

const int pawn_value = 100;
const int knight_value = 300;
const int bishop_value = 300;
const int rook_value = 500;
const int queen_value = 900;

//piece-square tables give general guidelines about where to put pieces

const int wp_table[64] ={0,  0,  0,  0,  0,   0,  0,  0,
                         0, 10, 10,-20,-20,  15, 10,  0,
                         5, -5, -10, 0,  0, -15, -5,  5,
                         0,  0,  0, 15, 15,   0,  0,  0,
                         5,  5, 10, 25, 25,  10,  5, 15,
                         10, 10, 20, 40, 40, 20, 10, 20,
                         60, 60, 60, 70, 70, 60, 60, 60,
                          0,  0,  0,  0,  0,  0,  0,  0};

const int wn_table[64] = {  -25, -20, -15, -15, -15, -15, -20, -25,
                            -15, -20,   0  , 0,   0,   0, -20, -15,
                            -10,   0,  10,   5,   5,  10,   0, -10,
                            -10,   5,  15,  20,  20,  15,   5, -10,
                             -5,   0,  15,  20,  20,  15,   0,  -5,
                            -15,   5,  20,  25,  25,  20,   5, -15,
                            -20, -20,   0,   5,   5,   0, -20, -20,
                            -50, -40, -30, -30, -30, -30, -40, -50};

const int wb_table[64] = {-20, -10, -15, -10, -10, -15, -10, -20,
                          -10,  15,   0,   0,   0,   0,  15, -10,
                          -10,  10,  10,  10,  10,  10,  10, -10,
                          -10,   0,  15,  10,  10,  10,   0, -10,
                          -10,   5,   5,  10,  10,   5,  10, -10,
                          -10,   0,   5,   0,   0,   5,   0, -10,
                          -20, -10,  -5,  -5,  -5,  -5, -10, -20,
                          -30, -30, -30, -30, -30, -30, -30, -30};

const int wr_table[64] = {    0,  0,  0, 15, 15, 10,  0, 0,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                             15, 25, 25, 25, 25, 25, 25, 15,
                              0,  0,  0,  0,  0,  0,  0, 0};

const int wq_table[64] = {-20, -10, -10, -5, -5, -10, -10, -20,
                          -10,   0,   0,  0,  0,   0,   0, -10,
                          -10,   0,   5,   5, 5,   5,   0, -10,
                           -5,   0,   5,   5, 5,   5,   0,  -5,
                            0,   0,   5,   5, 5,   5,   0,  -5,
                          -10,   5,   5,   5, 5,   5,   0, -10,
                          -10,   0,   5,   0, 0,   0,   0, -10,
                          -20, -10, -10, -5, -5, -10, -10, -20};

const int wk_table[64] ={20, 30,   20, -10,  -5, -10,  30,  10,
                         20,  0,  -10, -10, -10, -10,   0,  20,
                        -10, -20, -20, -20, -20, -20, -20, -10,
                         20, -30, -30, -40, -40, -30, -30, -20,
                        -30, -40, -40, -50, -50, -40, -40, -30,
                        -30, -40, -40, -50, -50, -40, -40, -30,
                        -30, -40, -40, -50, -50, -40, -40, -30,
                        -30, -40, -40, -50, -50, -40, -40, -30};


const int bp_table[64] = {0,  0,  0,  0,  0,   0,  0,  0,
                          60, 60, 60, 70, 70, 60, 60, 60,
                          10, 10, 20, 40, 40, 20, 10, 20,
                          5,  5, 10, 25, 25,  10,  5, 15,
                          0,  0,  0, 15, 15,   0,  0,  0,
                          5, -5, -10, 0,  0, -15, -5,  5,
                          0, 10, 10,-20,-20,  15, 10,  0,
                          0,  0,  0,  0,  0,   0,  0,  0};

const int bn_table[64] = {-50, -40, -30, -30, -30, -30, -40, -50,
                          -20, -20,   0,   5,   5,   0, -20, -20,
                          -15,   5,  20,  25,  25,  20,   5, -15,
                          -5,   0,  15,  20,  20,  15,   0,  -5,
                          -10,   5,  15,  20,  20,  15,   5, -10,
                          -10,   0,  10,   5,   5,  10,   0, -10,
                          -15, -20,   0  , 0,   0,   0, -20, -15,
                          -25, -20, -15, -15, -15, -15, -20, -25};

const int bb_table[64] = {-30, -30, -30, -30, -30, -30, -30, -30,
                          -20, -10,  -5,  -5,  -5,  -5, -10, -20,
                          -10,   0,   5,   0,   0,   5,   0, -10,
                          -10,   5,   5,  10,  10,   5,  10, -10,
                          -10,   0,  15,  10,  10,  10,   0, -10,
                          -10,  10,  10,  10,  10,  10,  10, -10,
                          -10,  15,   0,   0,   0,   0,  15, -10,
                          -20, -10, -15, -10, -10, -15, -10, -20};

const int br_table[64] = {0,  0,  0,  0,  0,  0,  0, 0,
                         15, 25, 25, 25, 25, 25, 25, 15,
                         -5,  0,  0,  0,  0,  0,  0, -5,
                         -5,  0,  0,  0,  0,  0,  0, -5,
                         -5,  0,  0,  0,  0,  0,  0, -5,
                         -5,  0,  0,  0,  0,  0,  0, -5,
                         -5,  0,  0,  0,  0,  0,  0, -5,
                         0,  0,  0, 15, 15, 10,  0, 0};

const int bq_table[64] = {-20, -10, -10, -5, -5, -10, -10, -20,
                          -10,   0,   5,   0, 0,   0,   0, -10,
                          -10,   5,   5,   5, 5,   5,   0, -10,
                            0,   0,   5,   5, 5,   5,   0,  -5,
                           -5,   0,   5,   5, 5,   5,   0,  -5,
                          -10,   0,   5,   5, 5,   5,   0, -10,
                          -10,   0,   0,  0,  0,   0,   0, -10,
                          -20, -10, -10, -5, -5, -10, -10, -20};

const int bk_table[64] = {-30, -40, -40, -50, -50, -40, -40, -30,
                          -30, -40, -40, -50, -50, -40, -40, -30,
                          -30, -40, -40, -50, -50, -40, -40, -30,
                          -30, -40, -40, -50, -50, -40, -40, -30,
                           20, -30, -30, -40, -40, -30, -30, -20,
                          -10, -20, -20, -20, -20, -20, -20, -10,
                           20,  0,  -10, -10, -10, -10,   0,  20,
                           20, 30,   20, -10,  -5, -10,  30,  10};


int ischeckmate(){//should be called only if there are no legal moves. returns the eval if that is the case
    
    if(white_to_move(tempi) == true){
        if(legal_moves[0].square_from == -1){//i.e. no legal moves have been added to the array
            if(ischeck(5,board,board_12x12) == true){
                return negative_infinity;//checkmate for black
            }
        }
    }
    else{
        if(legal_moves[0].square_from == -1){
            if(ischeck(29,board,board_12x12) == true){
                return positive_infinity;//checkmate for white
            }
    }
    }
    return 0;//stalemate
}

//function to statically evaluate the position
//i.e. evaluate the position without having to look any further
int evaluate(int board[]){

    int eval = 0;//initialise as 0 so previous evals don't affect this position's eval
    

    if(legal_moves[0].square_from == -1){//if there are no legal moves
        return ischeckmate();//checkmate or stalemate?
    }  


    for(int i = 0;i<64;i++){//loops through board counting material and evaluating piece-square tables
        switch(board[i]){
            
            case 0:
                eval += pawn_value;
                eval += wp_table[i];
                break;
            case 1:
                eval += knight_value;
                eval += wn_table[i];
                break;
            case 2:
                eval += bishop_value;
                eval += wb_table[i];
                break;
            case 3:
                eval += rook_value;
                eval += wr_table[i];
                break;
            case 4:
                eval += queen_value;
                eval += wq_table[i];
                break;
            case 5:
                eval +=wk_table[i];
            case 24:
                eval -= pawn_value;
                eval -= bp_table[i];
                break;
            case 25:
                eval -= knight_value;
                eval -= bn_table[i];
                break;
            case 26:
                eval -= bishop_value;
                eval -= bb_table[i];
                break;
            case 27:
                eval -= rook_value;
                eval -= br_table[i];
                break;
            case 28:
                eval -= queen_value;
                eval -= bq_table[i];
                break;
            case 29:
                eval -= bk_table[i];

        }
        
    }

    return eval;//always from white's perspective

}



