#include <iostream>
#include <array>
#include "movegen.cpp"

/**
 * This file finds legal moves in a position, and also contains functions to make or undo a move on the
 * board, as well as the function to determine whether the position if check.
 */
using namespace std;

enum move_type{normal, promotion};//promotions are different because we need to keep track of which piece to promote to

void get_w_pseudolegal(int board[], int board_12x12[]){//updates moves[] array with list of white's pseudolegal moves

    pseudolegal_move blank_move;
    blank_move.square_from = -1;
    blank_move.square_to = -1;

    for(int i = 0;i<218;i++){
        moves[i] = blank_move;
    }
    //WHITE PIECES:

    piece w_pawn;
    w_pawn.board_code = 0;
    w_pawn.slider = false;
    w_pawn.moveset[0] = 12;
    w_pawn.moveset[1] = 24;
    w_pawn.moveset[2] = 13;
    w_pawn.moveset[3] = 11;

    piece w_knight1;//forward moves
    w_knight1.board_code = 1;
    w_knight1.slider = false;
    w_knight1.moveset[0] = 14;
    w_knight1.moveset[1] = 25;
    w_knight1.moveset[2] = 23;
    w_knight1.moveset[3] = 10;

    piece w_knight2;//backward moves
    w_knight2.board_code = 1;
    w_knight2.slider = false;
    w_knight2.moveset[0] = -14;
    w_knight2.moveset[1] = -25;
    w_knight2.moveset[2] = -23;
    w_knight2.moveset[3] = -10;

    piece w_bishop;
    w_bishop.board_code = 2;
    w_bishop.slider = true;
    w_bishop.moveset[0] = 11;
    w_bishop.moveset[1] = 13;
    w_bishop.moveset[2] = -11;
    w_bishop.moveset[3] = -13;

    piece w_rook;
    w_rook.board_code = 3;
    w_rook.slider = true;
    w_rook.moveset[0] = 12;
    w_rook.moveset[1] = 1;
    w_rook.moveset[2] = -1;
    w_rook.moveset[3] = -12;

    piece w_queen1;//like rook
    w_queen1.board_code = 4;
    w_queen1.slider = true;
    w_queen1.moveset[0] = 12;
    w_queen1.moveset[1] = 1;
    w_queen1.moveset[2] = -1;
    w_queen1.moveset[3] = -12;

    piece w_queen2;
    w_queen2.board_code = 4;
    w_queen2.slider = true;
    w_queen2.moveset[0] = 11;
    w_queen2.moveset[1] = 13;
    w_queen2.moveset[2] = -11;
    w_queen2.moveset[3] = -13;

    piece w_king1;//moves like rook
    w_king1.board_code = 5;
    w_king1.slider = false;
    w_king1.moveset[0] = 12;
    w_king1.moveset[1] = 1;
    w_king1.moveset[2] = -1;
    w_king1.moveset[3] = -12;

    piece w_king2;//moves like bishop
    w_king2.board_code = 5;
    w_king2.slider = false;
    w_king2.moveset[0] = 11;
    w_king2.moveset[1] = 13;
    w_king2.moveset[2] = -11;
    w_king2.moveset[3] = -13;

    moves_count = 0;

    w_pawn.get_moves(board, board_12x12);
    w_knight1.get_moves(board, board_12x12);
    w_knight2.get_moves(board, board_12x12);
    w_bishop.get_moves(board, board_12x12);
    w_rook.get_moves(board, board_12x12);
    w_queen1.get_moves(board, board_12x12);
    w_queen2.get_moves(board, board_12x12);
    w_king1.get_moves(board, board_12x12);
    w_king2.get_moves(board, board_12x12);
        
}

void get_b_pseudolegal(int board[], int board_12x12[]){//updates moves[] array with list of black's pseudolegal moves

    pseudolegal_move blank_move;
    blank_move.square_from = -1;
    blank_move.square_to = -1;

    for(int i = 0;i<218;i++){
        moves[i] = blank_move;
    }
    //BLACK PIECES:

    piece b_pawn;
    b_pawn.board_code = 24;
    b_pawn.slider = false;
    b_pawn.moveset[0] = -12;
    b_pawn.moveset[1] = -24;
    b_pawn.moveset[2] = -13;
    b_pawn.moveset[3] = -11;

    piece b_knight1;//backward moves
    b_knight1.board_code = 25;
    b_knight1.slider = false;
    b_knight1.moveset[0] = 14;
    b_knight1.moveset[1] = 25;
    b_knight1.moveset[2] = 23;
    b_knight1.moveset[3] = 10;

    piece b_knight2;//forward moves
    b_knight2.board_code = 25;
    b_knight2.slider = false;
    b_knight2.moveset[0] = -14;
    b_knight2.moveset[1] = -25;
    b_knight2.moveset[2] = -23;
    b_knight2.moveset[3] = -10;

    piece b_bishop;
    b_bishop.board_code = 26;
    b_bishop.slider = true;
    b_bishop.moveset[0] = 11;
    b_bishop.moveset[1] = 13;
    b_bishop.moveset[2] = -11;
    b_bishop.moveset[3] = -13;

    piece b_rook;
    b_rook.board_code = 27;
    b_rook.slider = true;
    b_rook.moveset[0] = 12;
    b_rook.moveset[1] = 1;
    b_rook.moveset[2] = -1;
    b_rook.moveset[3] = -12;

    piece b_queen1;//like rook
    b_queen1.board_code = 28;
    b_queen1.slider = true;
    b_queen1.moveset[0] = 12;
    b_queen1.moveset[1] = 1;
    b_queen1.moveset[2] = -1;
    b_queen1.moveset[3] = -12;

    piece b_queen2;
    b_queen2.board_code = 28;
    b_queen2.slider = true;
    b_queen2.moveset[0] = 11;
    b_queen2.moveset[1] = 13;
    b_queen2.moveset[2] = -11;
    b_queen2.moveset[3] = -13;

    piece b_king1;//moves like rook
    b_king1.board_code = 29;
    b_king1.slider = false;
    b_king1.moveset[0] = 12;
    b_king1.moveset[1] = 1;
    b_king1.moveset[2] = -1;
    b_king1.moveset[3] = -12;

    piece b_king2;//moves like bishop
    b_king2.board_code = 29;
    b_king2.slider = false;
    b_king2.moveset[0] = 11;
    b_king2.moveset[1] = 13;
    b_king2.moveset[2] = -11;
    b_king2.moveset[3] = -13;

    
    moves_count = 0;
  
    b_pawn.get_moves(board, board_12x12);
    b_knight1.get_moves(board, board_12x12);
    b_knight2.get_moves(board, board_12x12);
    b_bishop.get_moves(board, board_12x12);
    b_rook.get_moves(board, board_12x12);
    b_queen1.get_moves(board, board_12x12);
    b_queen2.get_moves(board, board_12x12);
    b_king1.get_moves(board, board_12x12);
    b_king2.get_moves(board, board_12x12);
}

class Move{//Move object contains all the information required to make/undo a move on the board
    public:
        int square_from;
        int square_to;
        int square_reset;
        int promote_to;
        int ep_square;
        int fifty_moves_reset;
        bool wkca_reset;
        bool wqca_reset;
        bool bkca_reset;
        bool bqca_reset;
        move_type type;

    void make_move(int board[], int board_12x12[]){//function to make a move on the board        

        for(int i = 0;i < 64;i++){//remove old en passant squares
            if(board[i] == 30){
                board[i] = -6;
                board_12x12[get_12x12(i)] = -6;
            }
        }
        

        if(type == normal){

            //updating castling rights etc.
            if(board[square_from] == 5){//if white king is moved
                white_kingside_castling = false;
                white_queenside_castling = false;
            }

            if(square_from == 0 or square_to == 0){//if any piece moves from a1 or captures a1
                white_queenside_castling = false;//in case another piece was on a1, this will just 
                                                //be set from false to false
            }
            if(square_from == 7 or square_to == 7){//as above
                white_kingside_castling = false;
            }

            else if(board[square_from] == 29){//if black king is moved
                black_kingside_castling = false;
                black_queenside_castling = false;
            }

            if(square_from == 56 or square_to == 56){//if any piece moves from a8 or captures a8
                black_queenside_castling = false;//in case another piece was on a8, this will just 
                                                //be set from false to false
            }
            if(square_from == 63 or square_to == 63){//as above
                black_kingside_castling = false;
            }

            if(get_type(board[square_from]) == 0 and board[square_to] == 30){
                if(white_to_move(tempi) == true){//white en passant
                    board[square_to - 8] = -6;
                    board_12x12[get_12x12(square_to - 8)] = -6;
                }
                else{//black e.p.
                    board[square_to + 8] = -6;
                    board_12x12[get_12x12(square_to + 8)] = -6;
                }
            }

            if(board[square_from] != 0 and board[square_from] != 24 and board[square_to] == -6){//no pawn move or capture        
                fifty_moves = fifty_moves_reset + 1;
        
            }
            else{//reset fifty move rule
                fifty_moves = 0;
            }      
            
            if(board[square_from] == 0 and (square_to == square_from + 16)){
                board[square_from + 8] = 30;
                board_12x12[get_12x12(square_from) + 12] = 30;// add en passant square
                en_passant_square = square_from + 8;
            }

            else if(board[square_from] == 24 and (square_to == square_from - 16)){
                board[square_from - 8] = 30;
                board_12x12[get_12x12(square_from) - 12] = 30;//add en passant square
                en_passant_square = square_from - 8;
            }

            if(square_from == 4 and board[square_from] == 5 and square_to == 6){//if white castles kingside
                board[4] = -6;
                board[7] = -6;
                board[6] = 5;
                board[5] = 3;//update board accordingly
                board_12x12[get_12x12(4)] = -6;
                board_12x12[get_12x12(7)] = -6;
                board_12x12[get_12x12(6)] = 5;
                board_12x12[get_12x12(5)] = 3; 
                tempi ++;
            }
            else if(square_from == 4 and board[square_from] == 5 and square_to == 2){//if white castles queenside
                board[4] = -6;
                board[0] = -6;
                board[2] = 5;
                board[3] = 3;//update board accordingly
                board_12x12[get_12x12(4)] = -6;
                board_12x12[get_12x12(0)] = -6;
                board_12x12[get_12x12(2)] = 5;
                board_12x12[get_12x12(3)] = 3;
                tempi ++;
            }
            else if(square_from == 60 and board[square_from] == 29 and square_to == 62){//if black castles kingside
                board[60] = -6;
                board[63] = -6;
                board[62] = 29;
                board[61] = 27;//update board accordingly
                board_12x12[get_12x12(60)] = -6;
                board_12x12[get_12x12(63)] = -6;
                board_12x12[get_12x12(62)] = 29;
                board_12x12[get_12x12(61)] = 27;
                tempi ++;
            }
            else if(square_from == 60 and board[square_from] == 29 and square_to == 62){//if black castles kingside
                board[60] = -6;
                board[56] = -6;
                board[58] = 29;
                board[59] = 27;//update board accordingly
                board_12x12[get_12x12(60)] = -6;
                board_12x12[get_12x12(56)] = -6;
                board_12x12[get_12x12(58)] = 29;
                board_12x12[get_12x12(59)] = 27;
                tempi ++;
            }
            else{
                board[square_to] = board[square_from];
                board_12x12[get_12x12(square_to)] = board_12x12[get_12x12(square_from)];
                board[square_from] = -6;
                board_12x12[get_12x12(square_from)] = -6;
                tempi ++;//update board and increase tempi count
            }
        }
        else{//promotions
            switch(square_to){//in case black promotes by taking a rook
                case 0:
                    white_queenside_castling = false;
                    break;
                case 7:
                    white_kingside_castling = false;
                    break;
                case 56:
                    black_queenside_castling = false;
                    break;
                case 63:
                    black_kingside_castling = false;
                    break;
            }

            board[square_from] = -6;
            board_12x12[get_12x12(square_from)] = -6;
            board[square_to] = promote_to;
            board_12x12[get_12x12(square_to)];
            fifty_moves = 0;
            tempi ++;//update board and tempi, using promote_to

        }
    }

    void undo_move(int board[], int board_12x12[]){//function to undo a move
        if(type == normal){
            if(square_from == 4 and board[square_from] == 5 and square_to == 6){//if white castles kingside
                board[4] = 5;
                board[7] = 3;
                board[6] = -6;
                board[5] = -6;//update board accordingly
                board_12x12[get_12x12(4)] = -5;
                board_12x12[get_12x12(7)] = 3;
                board_12x12[get_12x12(6)] = -6;
                board_12x12[get_12x12(5)] = -6; 
                tempi --;
            }
            else if(square_from == 4 and board[square_from] == 5 and square_to == 2){//if white castles queenside
                board[4] = 5;
                board[0] = 3;
                board[2] = -6;
                board[3] = -6;//update board accordingly
                board_12x12[get_12x12(4)] = 5;
                board_12x12[get_12x12(0)] = 3;
                board_12x12[get_12x12(2)] = -6;
                board_12x12[get_12x12(3)] = -6;
                tempi --;
            }
            else if(square_from == 60 and board[square_from] == 29 and square_to == 62){//if black castles kingside
                board[60] = 29;
                board[63] = 27;
                board[62] = -6;
                board[61] = -6;//update board accordingly
                board_12x12[get_12x12(60)] = 29;
                board_12x12[get_12x12(63)] = 27;
                board_12x12[get_12x12(62)] = -6;
                board_12x12[get_12x12(61)] = -6;
                tempi --;
            }
            else if(square_from == 60 and board[square_from] == 29 and square_to == 62){//if black castles kingside
                board[60] = 29;
                board[56] = 27;
                board[58] = -6;
                board[59] = -6;//update board accordingly
                board_12x12[get_12x12(60)] = 29;
                board_12x12[get_12x12(56)] = 27;
                board_12x12[get_12x12(58)] = -6;
                board_12x12[get_12x12(59)] = -6;
                tempi --;
            }
            else if(square_reset == 30 and get_type(board[square_to]) == 0){//if last move was en passant
                if(white_to_move(tempi - 1) == true){//if white made the last move as an en passant capture
                    board[square_from] = board[square_to];
                    board[square_to] = square_reset;
                    board_12x12[get_12x12(square_from)] = board_12x12[get_12x12(square_to)];
                    board_12x12[get_12x12(square_to)] = square_reset;
                    tempi --;

                    board[ep_square - 8] = 24;//set black pawn on square "above" en passant square
                    board_12x12[get_12x12(ep_square - 8)] = 24;
                }
                else{//as above
                    board[square_from] = board[square_to];
                    board[square_to] = square_reset;
                    board_12x12[get_12x12(square_from)] = board_12x12[get_12x12(square_to)];
                    board_12x12[get_12x12(square_to)] = square_reset;
                    tempi --;

                    board[ep_square + 8] = 0;
                    board_12x12[get_12x12(ep_square + 8)] = 0;
                }
            }
            else{
                board[square_from] = board[square_to];
                board[square_to] = square_reset;
                board_12x12[get_12x12(square_from)] = board_12x12[get_12x12(square_to)];
                board_12x12[get_12x12(square_to)] = square_reset;
                tempi --;
            }
        }
        else{//promotions
            if(get_rank(square_to) == 8){//white pawn that promoted
                board[square_from] = 0;
                board_12x12[get_12x12(square_from)] = 0;
            }
            else{
                board[square_from] = 24;
                board_12x12[get_12x12(square_from)] = 24;
            }
            board[square_to] = -6;
            board_12x12[get_12x12(square_to)] = -6;

        }

        if(ep_square != -1){
            board[ep_square] = 30;
            board_12x12[get_12x12(ep_square)] = 30;
        }

        fifty_moves = fifty_moves_reset;

        white_kingside_castling = wkca_reset;
        white_queenside_castling = wqca_reset;
        black_kingside_castling = bkca_reset;
        black_queenside_castling = bqca_reset;
    }
};

array<Move, 218> legal_moves;//array containing all legal moves for the side to move


bool ischeck(int colour_to_test, int board[], int board_12x12[]){//tests whether a position is check

    array <pseudolegal_move, 218> check_moves = moves;//makes a copy of moves array to use

    pseudolegal_move blank_move;
    blank_move.square_from = -1;
    blank_move.square_to = -1;

    for(int i = 0;i<218;i++){
        check_moves[i] = blank_move;//fills check moves with empty moves
    }  
    

    if(colour_to_test == 5){
        get_b_pseudolegal(board, board_12x12);//gets black's pseudolegal moves
        check_moves = moves;

        for(int i = 0;i < 218;i++){            
            pseudolegal_move move = check_moves[i];
            if(move.square_to == -1){
                break;
            }

            if(board[move.square_to] == 5){//if any of the moves land on white's king square
                return true;//white is in check
            }            
        }
    }

    else if(colour_to_test == 29){//as above
        get_w_pseudolegal(board, board_12x12);

        check_moves = moves;

        for(int i = 0;i < 218;i++){
            pseudolegal_move move = check_moves[i];
            if(move.square_to == -1){
                break;
            }
            if(board[move.square_to] == 29){//if any of the moves land on black's king square
                return true;//black is in check
            }            
        }
    }

    return false;//passed through loop and no checks found, so side to move is not in check
    

}

void get_legal(int board[], int board_12x12[]){//gets list of all legal moves in a position
    
    int legal_count = 0;
    Move blank_move;
    blank_move.square_from = -1;
    blank_move.square_to = -1;
    blank_move.square_reset = -1;
    blank_move.fifty_moves_reset = -1;
    blank_move.ep_square = -1;
    blank_move.promote_to = -1;
    blank_move.type = normal;
    blank_move.wkca_reset = false;
    blank_move.wqca_reset = false;
    blank_move.bkca_reset = false;
    blank_move.bqca_reset = false;//create blank_move

    for(int i = 0; i < 218; i++){
        legal_moves[i] = blank_move;
    }//reset legal moves array

    if(white_to_move(tempi) == true){
        get_w_pseudolegal(board, board_12x12);//first get white's pseudolegal moves
        array<pseudolegal_move, 218> checking_moves = moves;//copy moves onto a temporary array
        
        for(int i = 0; i < 218; i++){
            pseudolegal_move move = checking_moves[i];
            if(move.square_from == -1){
                break;
            }

            int sq_to = move.square_to;
            int sq_from = move.square_from;

            int sq_reset = board[sq_to];
            int piece_moved = board[sq_from];

            board[sq_to] = board[sq_from];
            board[sq_from] = -6;//update board

            board_12x12[get_12x12(sq_to)] = board_12x12[get_12x12(sq_from)];
            board_12x12[get_12x12(sq_from)] = -6;//update board_12x12
            //we don't need to worry about updating castling rights etc as this won't change whether the move if legal or not
            if(ischeck(5,board, board_12x12) == false){//if move doesn't leave us in check

                int promote_counter;
                promote_counter = 0;

                Move move;
                move.square_from = sq_from;
                move.square_to = sq_to;
                move.square_reset = sq_reset;
                move.fifty_moves_reset = fifty_moves;
                move.wkca_reset = white_kingside_castling;
                move.wqca_reset = white_queenside_castling;
                move.bkca_reset = black_kingside_castling;
                move.bqca_reset = black_queenside_castling;
                move.ep_square = en_passant_square;
                move.type = normal;//initialise as values as if move isn't promotion
                move.promote_to = -1;//then if it is a promotion, thes get updated below

                if(piece_moved == 0 and get_rank(sq_to) == 8){//if promotion
                    switch(promote_counter){//add a different piece depending on how many times pieces have already been added
                        case 0:
                            move.promote_to = 4;//queen
                            move.type = promotion;
                            promote_counter ++;
                            legal_moves[legal_count] = move;
                            legal_count ++;
                            break;
                        case 1:
                            move.promote_to = 3;//rook
                            move.type = promotion;
                            promote_counter ++;
                            legal_moves[legal_count] = move;
                            legal_count ++;
                            break;
                        case 2:
                            move.promote_to = 2;//bishop
                            move.type = promotion;
                            promote_counter ++;
                            legal_moves[legal_count] = move;
                            legal_count ++;
                            break;
                        case 3:
                            move.promote_to = 1;//knight
                            move.type = promotion;
                            promote_counter ++;
                            legal_moves[legal_count] = move;
                            legal_count ++;
                            break;                        
                    }

                }
                else{//not a promotion
                    legal_moves[legal_count] = move;
                    legal_count ++;
                }            

            }

            board[sq_from] = board[sq_to];
            board[sq_to] = sq_reset;//reset board

            board_12x12[get_12x12(sq_from)] = board_12x12[get_12x12(sq_to)];
            board_12x12[get_12x12(sq_to)] = sq_reset;//reset board_12x12



        }

    }

    else{//black to move
        get_b_pseudolegal(board, board_12x12);//first get white's pseudolegal moves
        array<pseudolegal_move, 218> checking_moves = moves;//copy moves onto a temporary array
        
        for(int i = 0; i < 218;i++){
            pseudolegal_move move = checking_moves[i];
            if(move.square_from == -1){
                break;
            }

            int sq_to = move.square_to;
            int sq_from = move.square_from;

            int sq_reset = board[sq_to];
            int piece_moved = board[sq_from];

            board[sq_to] = board[sq_from];
            board[sq_from] = -6;//update board

            board_12x12[get_12x12(sq_to)] = board_12x12[get_12x12(sq_from)];
            board_12x12[get_12x12(sq_from)] = -6;//update board_12x12

            if(ischeck(29,board, board_12x12) == false){//if move doesn't leave us in check

                int promote_counter;
                promote_counter = 0;

                Move move;
                move.square_from = sq_from;
                move.square_to = sq_to;
                move.square_reset = sq_reset;
                move.fifty_moves_reset = fifty_moves;
                move.wkca_reset = white_kingside_castling;
                move.wqca_reset = white_queenside_castling;
                move.bkca_reset = black_kingside_castling;
                move.bqca_reset = black_queenside_castling;
                move.ep_square = en_passant_square;
                move.type = normal;//initialise as values as if move isn't promotion
                move.promote_to = -1;//then if it is a promotion, thes get updated below

                if(piece_moved == 24 and get_rank(sq_to) == 1){//if promotion
                    switch(promote_counter){
                        case 0:
                            move.promote_to = 4;
                            move.type = promotion;
                            promote_counter ++;
                            legal_moves[legal_count] = move;
                            legal_count ++;
                        case 1:
                            move.promote_to = 3;
                            move.type = promotion;
                            promote_counter ++;
                            legal_moves[legal_count] = move;
                            legal_count ++;
                            break;
                        case 2:
                            move.promote_to = 2;
                            move.type = promotion;
                            promote_counter ++;
                            legal_moves[legal_count] = move;
                            legal_count ++;
                            break;
                        case 3:
                            move.promote_to = 1;
                            move.type = promotion;
                            promote_counter ++;
                            legal_moves[legal_count] = move;
                            legal_count ++;
                            break;                        
                    }

                }
                else{
                    legal_moves[legal_count] = move;
                    legal_count ++;
                }
                


                
            }

            board[sq_from] = board[sq_to];
            board[sq_to] = sq_reset;//reset board

            board_12x12[get_12x12(sq_from)] = board_12x12[get_12x12(sq_to)];
            board_12x12[get_12x12(sq_to)] = sq_reset;

        }

    }
    

}

