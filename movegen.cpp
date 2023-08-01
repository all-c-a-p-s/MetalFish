#include <iostream>
#include <list>
#include "board.cpp"
using namespace std;

int moves[218][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};//list of origin squares followed by destination squares of moves
//218 is upper bound for legal moves possible in a position. theoretically there might be more pseudolegal moves,
//but this should never occur in practice


int squares_found[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int moves_count;

class piece{

    public:
        int board_code;
        char fen_code;
        bool slider;
        int moveset[4];//each piece has a multiple of 4 (either 4 or 8) move directions
        //so for generating moves we can consider e.g. knight1 and knight2 different pieces
        int piece_count;

        void find_piece(){


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
            while(found_count < 10){
                for(int i = 0; i <64; i++){
                    if(board[i] == board_code){
                        squares_found[found_count] = get_12x12(i);//where i is the square
                        found_count ++;
                    }
                }
                break;
            }

        }

        void movegen(int square){
            

            int colour = board_code/6;      // as explained in board.cpp
            int temp = square;
            

            if(slider == true){

                for(int i = 0; i <= 3; i++){
                square = temp;//reset square to the value passed into the function
                
                    while(board_12x12[square + moveset[i]] == -6 or isenemy(board_code,board_12x12[square + moveset[i]]) == true){
                        //as long as the next square is either empty or an enemy piece

                        moves[moves_count][0] = get_8x8(temp);//temp because square keeps getting updated
                        //cout << get_8x8(temp) << endl;
                        moves[moves_count][1] = get_8x8(square + moveset[i]);
                        //cout << get_8x8(square + moveset[i]) << endl;
                        moves_count ++;
                        //add origin and destination of move to moves array

                        if(isenemy(board_code,board_12x12[square + moveset[i]]) == true){
                            break;
                        }
                        //since you can capture an enemy piece but you can't go through it

                        square += moveset[i];                                 

                    }
                            
                            
                }
            }

            else if(slider == false and get_type(board_code) != 0){//non-sliders that aren't pawns

                for(int i = 0; i <= 3; i++){
                    if(board_12x12[square + moveset[i]] == -6 or isenemy(board_code,board_12x12[square + moveset[i]]) == true){
                        moves[moves_count][0] = get_8x8(square);
                        //cout << get_8x8(square) << endl;
                        moves[moves_count][1] = get_8x8(square + moveset[i]);
                        //cout << get_8x8(square + moveset[i]) << endl;
                        moves_count ++;
                    }
                }

            }
            else{//pawns have a bunch of exceptions e.g. promotion, en passant

                if((get_12x12_rank(square)== 4 and get_colour(board_code) == 0) or (get_12x12_rank(square)== 9 and get_colour(board_code) == 4)){
                //if pawn hasn't moved yet
                    if(board_12x12[square + moveset[0]] == -6 and board_12x12[square + moveset[1]] == -6){

                        moves[moves_count][0] = get_8x8(square);
                        //cout << get_8x8(square) << endl;
                        moves[moves_count][1] = get_8x8(square + moveset[1]);
                        //cout << get_8x8(square + moveset[1]) << endl;
                        moves_count ++;//by 2
                                
                    }

                }
                if(board_12x12[square + moveset[0]] == -6){//if pawn is not blocked
                    moves[moves_count][0] = get_8x8(square);
                    moves[moves_count][1] = get_8x8(square + moveset[0]);
                    moves_count ++;//it can move by 1
                }

                

                if(isenemy(board_code,board_12x12[square + moveset[2]]) == true){
                    moves[moves_count][0] = get_8x8(square);
                    moves[moves_count][1] = get_8x8(square + moveset[2]);
                    moves_count ++;//capture left
                }

                if(isenemy(board_code,board_12x12[square + moveset[3]]) == true){
                    moves[moves_count][0] = get_8x8(square);
                    moves[moves_count][1] = get_8x8(square + moveset[3]);
                    moves_count ++;//capture right
                }


                
                        


            }
                    
                     

        } 
        

};



