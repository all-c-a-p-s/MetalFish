#include <iostream>
#include <array>
#include "board.cpp"

/**
 * This file contains functions to find pieces on the board and generate a list of pseudo-legal moves.
 * A pseudolegal move is a move that obeys the rules of how a certain piece may move, but could leave the
 * side-to-move's king in check. The file also contains the function to determine whether the side to move
 * is in check in the current position.
*/

using namespace std;

bool ischeck(int colour_to_test, int board[], int board_12x12[]);

class pseudolegal_move{//here we don't need to store anything like castling rights or square reset
    public:
        int square_from;
        int square_to;

};

array<pseudolegal_move, 100> moves;//100 is a resonable upper bound for number of pseudolegal moves
//in a position. An unnecessarily high number will slow down the engine's move generation

int squares_found[10];
int moves_count;//used to add new pseudolegal moves to the right index

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
                        squares_found[found_count] = get_12x12(i);//where i is the square. this is 12x12'd because it passes directly into movegen()
                        found_count ++;
                    }
                }
                break;
            }

        }

        void movegen(int square, int board[], int board_12x12[]){//function to update moves array with all pseudolegal moves in a position
            
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
                        //add origin and destination of move to array

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
                        moves_count ++;//add move to array
                    }
                }
                if(board_code == 5 and moveset[0] == 12){//otherwise this will get added for both king1 and king2
                    if(white_kingside_castling == true and ischeck(5, board, board_12x12) == false){
                        if(board_12x12[get_12x12(5)] == -6 and board_12x12[get_12x12(6)] == -6){//if nothing between king and rook
                            pseudolegal_move move;
                            move.square_from = get_8x8(square);
                            move.square_to = 6;//kingside castling

                            moves[moves_count] = move;
                            moves_count ++;
                        }
                    }
                    if(white_queenside_castling == true and ischeck(5, board, board_12x12) == false){
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
                    if(black_kingside_castling == true and ischeck(29, board, board_12x12) == false){
                        if(board_12x12[get_12x12(61)] == -6 and board_12x12[get_12x12(62)] == -6){//if nothing between king and rook
                            pseudolegal_move move;
                            move.square_from = get_8x8(square);
                            move.square_to = 62;//black kingside castling

                            moves[moves_count] = move;
                            moves_count ++;
                        }
                    }
                    if(black_queenside_castling == true and ischeck(29, board, board_12x12) == false){
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
                    move.square_to =get_8x8(square + moveset[0]);//by 1

                    moves[moves_count] = move;
                    moves_count ++;
                }

                

                if(isenemy(board_code,board_12x12[square + moveset[2]]) == true or board_12x12[square + moveset[2]] == 30){
                    pseudolegal_move move;
                    move.square_from = get_8x8(square);
                    move.square_to =get_8x8(square + moveset[2]);//capture left

                    moves[moves_count] = move;
                    moves_count ++;
                }

                if(isenemy(board_code,board_12x12[square + moveset[3]]) == true or board_12x12[square + moveset[3]] == 30){
                    pseudolegal_move move;
                    move.square_from = get_8x8(square);
                    move.square_to =get_8x8(square + moveset[3]);//capture right

                    moves[moves_count] = move;
                    moves_count ++;
                }


                
                        


            }
                    
                     

        } 
        
        void get_moves(int board[], int board_12x12[]){//function which calls find_piece() and movegen()
            find_piece(board);

            for(int i = 0;i < 10;i++){
                if(squares_found[i] == -1){
                    break;
                }
                movegen(squares_found[i], board, board_12x12);
        
            }
        }

};

bool ischeck(int colour_to_test, int board[], int board_12x12[]){//function to determine whether current position if check

    /**
     * Instead of just getting black's pseudolegal moves in a position and seeing if any of these take
     * our king, this function finds the position of the king being tested for and looks for enemy pieces
     * from here based on their moveset, which should be faster on average */
    
    int king_square;//board index where king is
    int last_queen1_move;//will be used to keep track of where to loop through moves_reset
    int moves_count_reset;//used to reset moves_count variable
    moves_count_reset = moves_count;

    moves_count = 0;

    array <pseudolegal_move, 100> moves_reset = moves;//used to reset moves array
    pseudolegal_move blank_move;
    blank_move.square_from = -1;
    blank_move.square_to = -1;

    for(int i = 0;i < 100;i++){
        moves[i] = blank_move;
    }

    for(int i = 0;i < 64;i++){
        if(board[i] == colour_to_test){
            king_square = get_12x12(i);//get_12x12() because this will be passed into movegen
        }
    }

    piece queen_check_1;//also rook
    queen_check_1.board_code = colour_to_test;
    queen_check_1.slider = true;
    queen_check_1.moveset[0] = 12;
    queen_check_1.moveset[1] = -12;
    queen_check_1.moveset[2] = 1;
    queen_check_1.moveset[3] = -1;

    piece queen_check_2;//also bishop
    queen_check_2.board_code = colour_to_test;
    queen_check_2.slider = true;
    queen_check_2.moveset[0] = 11;
    queen_check_2.moveset[1] = 13;
    queen_check_2.moveset[2] = -11;
    queen_check_2.moveset[3] = -13;

    int knight_moveset[8] = {14, 25, 23, 10, -14, -25, -23, -10};
    int king_moveset[8] = {12, 13, 1, -11, -12, -13, -1, 11};//since these aren't passed into movegen(), all moves can be in one array

    if(colour_to_test == 5){
        if(board_12x12[king_square + 11] == 24 or board_12x12[king_square + 13] == 24){
            moves_count = moves_count_reset;
            moves = moves_reset;
            return true;//white king in check form black pawns
        }
    }
    else{
        if(board_12x12[king_square - 11] == 0 or board_12x12[king_square - 13] == 0){
            moves_count = moves_count_reset;
            moves = moves_reset;
            return true;//black king in check from white pawns
        }
    }

    for(int i = 0;i < 8;i++){
        if(get_type(board_12x12[king_square + knight_moveset[i]]) == 1 and isenemy(colour_to_test, board_12x12[king_square + knight_moveset[i]])){
            moves_count = moves_count_reset;
            moves = moves_reset;
            return true;//knight of opposite colour
        }
    }

    for(int i = 0;i < 8;i++){
        int product = colour_to_test * board_12x12[king_square + king_moveset[i]];//test if kings are next to each other
        if(product == 145){//product of two kings will always be 145 (5 * 29)
            moves_count = moves_count_reset;
            moves = moves_reset;
            return true;//no other pieces can give this product
        }
    }

    queen_check_1.get_moves(board, board_12x12);

    for(int i = 0;i < 100;i++){//loop through rook-like moves
        pseudolegal_move move = moves[i];
        if(move.square_from == -1){
            last_queen1_move = i;
            break;
        }
        if(isenemy(colour_to_test, board[move.square_to]) == true){//is of opposite colour
            if(get_type(board[move.square_to]) == 4 or get_type(board[move.square_to]) == 3){//queen or rook
                moves_count = moves_count_reset;
                moves = moves_reset;
                return true;
            }
        }
    }

    queen_check_2.get_moves(board, board_12x12);

    for(int i = last_queen1_move;i < 100;i++){//loop through bishop-like moves
        pseudolegal_move move = moves[i];
        if(move.square_from == -1){
            break;
        }
        if(isenemy(colour_to_test, board[move.square_to]) == true){//is of opposite colour
            if(get_type(board[move.square_to]) == 4 or get_type(board[move.square_to]) == 2){//queen or bishop
                moves = moves_reset;
                moves_count = moves_count_reset;
                moves = moves_reset;
                return true;
            }
        }
    }

    moves = moves_reset;
    moves_count = moves_count_reset;
    return false;//did not return true from any of above conditions, so king is not in check

}


