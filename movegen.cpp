#include <iostream>
#include <array>
#include "board.cpp"

/**
 * This file contains functions to find pieces on the board and generate a list of pseudo-legal moves.
 * A pseudolegal move is a move that obeys the rules of how a certain piece may move, but could leave the
 * side-to-move's king in check.
*/

using namespace std;


class pseudolegal_move{//here we don't need to store anything like castling rights
    public:
        int square_from;
        int square_to;

};

array<pseudolegal_move, 218> moves;//218 is maximum possible number of legal moves in a position
//theoretically this could be higher for pseudolegal moves, bu in practice this won't occur

int squares_found[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};//initialise as empty
int moves_count;

class piece{

    public:
        int board_code;
        bool slider;
        int moveset[4];//each piece has a multiple of 4 (either 4 or 8) move directions
        //so for generating moves we can consider e.g. knight1 and knight2 different pieces

        void find_piece(int board[]){


            squares_found[0] = -1;
            squares_found[1] = -1;
            squares_found[2] = -1;
            squares_found[3] = -1;
            squares_found[4] = -1;
            squares_found[5] = -1;
            squares_found[6] = -1;
            squares_found[7] = -1;
            squares_found[8] = -1;
            squares_found[9] = -1;

            int found_count = 0;
            while(found_count < 10){//there can never be more than 10 of a certain piece on the board at a time
                for(int i = 0; i <64; i++){
                    if(board[i] == board_code){
                        squares_found[found_count] = get_12x12(i);//where i is the square
                        found_count ++;
                    }
                }
                break;
            }

        }

        void movegen(int square, int board_12x12[]){//function to update moves array with all pseudolegal moves in a position
            

            int colour = board_code/6;      // as explained in board.cpp
            int temp = square;//to keep track of which square a sliding piece started on
            

            if(slider == true){

                for(int i = 0; i <= 3; i++){
                square = temp;//reset square to the value passed into the function
                
                    while(board_12x12[square + moveset[i]] == -6 or board_12x12[square + moveset[i]] == 30 or isenemy(board_code,board_12x12[square + moveset[i]]) == true){//pieces can also move onto en passant squares
                        //as long as the next square is either empty or an enemy piece

                        pseudolegal_move move;
                        move.square_from = get_8x8(temp);
                        move.square_to =get_8x8(square + moveset[i]);

                        moves[moves_count] = move;
                        moves_count ++;
                        //add origin and destination of move to list

                        if(isenemy(board_code,board_12x12[square + moveset[i]]) == true){
                            break;
                        }
                        //since you can capture an enemy piece but you can't go through it

                        square += moveset[i];                                 

                    }
                            
                            
                }
            }

            else if(get_type(board_code) != 0){//non-sliders that aren't pawns

                for(int i = 0; i < 4; i++){
                    if(board_12x12[square + moveset[i]] == -6 or board_12x12[square + moveset[i]] == 30 or isenemy(board_code,board_12x12[square + moveset[i]]) == true){
                        pseudolegal_move move;
                        move.square_from = get_8x8(square);
                        move.square_to =get_8x8(square + moveset[i]);

                        moves[moves_count] = move;
                        moves_count ++;
                    }
                }
                if(board_code == 5 and moveset[0] == 12){//otherwise this will get added for both king1 and king2
                    if(white_kingside_castling == true){
                        if(board_12x12[get_12x12(5)] == -6 and board_12x12[get_12x12(6)] == -6){//if nothing between king and rook
                            pseudolegal_move move;
                            move.square_from = get_8x8(square);
                            move.square_to = 6;//kingside castling

                            moves[moves_count] = move;
                            moves_count ++;
                        }
                    }
                    if(white_queenside_castling == true){
                        if(board_12x12[get_12x12(3)] == -6 and board_12x12[get_12x12(2)] == -6 and board_12x12[get_12x12(1)] == -6){//if nothing between king and rook
                            pseudolegal_move move;
                            move.square_from = get_8x8(square);
                            move.square_to = 2;//queenside castling

                            moves[moves_count] = move;
                            moves_count ++;
                        }
                    }
                }
                else if(board_code == 29 and moveset[0] == 12){//as above
                    if(black_kingside_castling == true){
                        if(board_12x12[get_12x12(61)] == -6 and board_12x12[get_12x12(62)] == -6){//if nothing between king and rook
                            pseudolegal_move move;
                            move.square_from = get_8x8(square);
                            move.square_to = 62;//black kingside castling

                            moves[moves_count] = move;
                            moves_count ++;
                        }
                    }
                    if(black_queenside_castling == true){
                        if(board_12x12[get_12x12(59)] == -6 and board_12x12[get_12x12(58)] == -6 and board_12x12[get_12x12(57)] == -6){//if nothing between king and rook
                            pseudolegal_move move;
                            move.square_from = get_8x8(square);
                            move.square_to = 58;//black queenside castling

                            moves[moves_count] = move;
                            moves_count ++;
                        }
                    }
                }                  

                

            }
            else{//pawns have a bunch of exceptions e.g. promotion, en passant

                if((get_12x12_rank(square)== 4 and get_colour(board_code) == 0) or (get_12x12_rank(square)== 9 and get_colour(board_code) == 4)){
                //if pawn hasn't moved yet
                    if(board_12x12[square + moveset[0]] == -6 and board_12x12[square + moveset[1]] == -6){

                        pseudolegal_move move;
                        move.square_from = get_8x8(square);
                        move.square_to =get_8x8(square + moveset[1]);

                        moves[moves_count] = move;
                        moves_count ++;//by 2
                                
                    }

                }
                if(board_12x12[square + moveset[0]] == -6){//if pawn is not blocked
                    pseudolegal_move move;
                    move.square_from = get_8x8(square);
                    move.square_to =get_8x8(square + moveset[0]);

                    moves[moves_count] = move;
                    moves_count ++;
                }

                

                if(isenemy(board_code,board_12x12[square + moveset[2]]) == true or board_12x12[square + moveset[2]] == 30){
                    pseudolegal_move move;
                    move.square_from = get_8x8(square);
                    move.square_to =get_8x8(square + moveset[2]);

                    moves[moves_count] = move;
                    moves_count ++;
                }

                if(isenemy(board_code,board_12x12[square + moveset[3]]) == true or board_12x12[square + moveset[3]] == 30){
                    pseudolegal_move move;
                    move.square_from = get_8x8(square);
                    move.square_to =get_8x8(square + moveset[3]);

                    moves[moves_count] = move;
                    moves_count ++;
                }


                
                        


            }
                    
                     

        } 
        
        void get_moves(int board[], int board_12x12[]){
            find_piece(board);

            for(int i = 0;i < 10;i++){
                if(squares_found[i] == -1){
                    break;
                }
                movegen(squares_found[i], board_12x12);
        
            }
        }

};



