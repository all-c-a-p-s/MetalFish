#include <iostream>
#include <array>
#include "move.cpp"

using namespace std;

/**
 * This file contains functions that are used to get a static evaluation of a board position (an evaluation
 * which is reached without having to look any further into the position).
*/

const int pawn_value = 100;
const int knight_value = 300;
const int bishop_value = 320;
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

const int wr_table[64] = {    0,  0, 10, 15, 15, 10,  0, 0,
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
                         0,  0, 10, 15, 15, 10,  0, 0};

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


int ischeckmate(int board[], int board_10x12[]){//should only be called if legal_moves[0].square_from = -1. determines whether position is checkmate or stalemate.
    
    int engine_side = 1;//necessary because eval most be from side-to-move's perpective

    if(engine_plays_white == false){
        engine_side = -1;
    }

    if(white_to_move(tempi) == true){
        if(ischeck(5,board,board_10x12) == true){
            return negative_infinity * engine_side;//win for black
        }
        return 0;

    }
    else{

        if(ischeck(29,board,board_10x12) == true){
            return positive_infinity * engine_side;//win for white
        }
        return 0;
    }
    return 0;//stalemate
}

//function to statically evaluate the position
//i.e. evaluate the position without having to look any further
int evaluate(int board[]){

    int eval = 0;//initialise as 0 so previous evals don't affect this position's eval


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
                break;
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
                break;

        }
        
    }
    
    if(white_to_move(tempi) == false){
        return eval * -1;
    }
    return eval;//always from white's perspective

}



