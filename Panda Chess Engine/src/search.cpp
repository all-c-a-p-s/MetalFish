#include <iostream>
#include <array>
#include "eval.cpp"

using namespace std;

/**
 * This file handles the engine's search, containing the negamax function and also the function to choose 
 * the best move. 
*/


int sq_moved_onto;//to be used in recapture search

array <pseudolegal_move, 100> pseudolegal_recaptures;//pseudolegal recaptures
array <Move, 100> recaptures;

void get_recaptures(int square, int board[], int board_10x12[]){//technically does not generate en passant captures, but these are unilkely to make a difference

    int piece_moved = board[square];//piece that is currently on the target square

    square = get_10x12(square);

    array <pseudolegal_move, 100> moves_reset;
    moves_reset = moves;
    int moves_count_reset;
    moves_count_reset = moves_count;

    moves_count = 0;

    int recaptures_count;
    recaptures_count = 0;

    int pseudolegal_recaptures_count;
    pseudolegal_recaptures_count = 0;

    int last_queen1_move;

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
    blank_move.move_order_score = negative_infinity;

    for(int i = 0; i < 100; i++){
        recaptures[i] = blank_move;
    }//reset legal moves array

    pseudolegal_move blank_pseudolegal;
    blank_pseudolegal.square_from = -1;
    blank_pseudolegal.square_to = -1;

    for(int i = 0;i < 100;i ++){
        pseudolegal_recaptures[i] = blank_pseudolegal;
    }    

    //uses similar code to ischeck() function
    
    piece queen_check_1;//also rook
    queen_check_1.board_code = piece_moved;
    queen_check_1.slider = true;
    queen_check_1.moveset[0] = 10;
    queen_check_1.moveset[1] = -10;
    queen_check_1.moveset[2] = 1;
    queen_check_1.moveset[3] = -1;

    piece queen_check_2;//also bishop
    queen_check_2.board_code = piece_moved;
    queen_check_2.slider = true;
    queen_check_2.moveset[0] = 11;
    queen_check_2.moveset[1] = 9;
    queen_check_2.moveset[2] = -11;
    queen_check_2.moveset[3] = -9;

    int knight_moveset[8] = {12, 21, 19, 8, -12, -21, -19, -8};
    int king_moveset[8] = {10, 11, 9, 1, -10, -11, -9, -1};//since these aren't passed into movegen(), all moves can be in one array

    if(get_colour(piece_moved) == 0){//if white piece has just moved
        if(board_10x12[square + 11] == 24){
            pseudolegal_move pseudolegal_recapture;
            pseudolegal_recapture.square_from = get_8x8(square + 11);
            pseudolegal_recapture.square_to = get_8x8(square);
            pseudolegal_recaptures[pseudolegal_recaptures_count] = pseudolegal_recapture;
            pseudolegal_recaptures_count ++;//black pawn captures
        } 
        if(board_10x12[square + 9] == 24){
            pseudolegal_move pseudolegal_recapture;
            pseudolegal_recapture.square_from = get_8x8(square + 9);
            pseudolegal_recapture.square_to = get_8x8(square);
            pseudolegal_recaptures[pseudolegal_recaptures_count] = pseudolegal_recapture;
            pseudolegal_recaptures_count ++;

        }
    }
    else{//if black piece has just moved
        if(board_10x12[square - 11] == 0){ 
            pseudolegal_move pseudolegal_recapture;
            pseudolegal_recapture.square_from = get_8x8(square - 11);
            pseudolegal_recapture.square_to = get_8x8(square);
            pseudolegal_recaptures[pseudolegal_recaptures_count] = pseudolegal_recapture;
            pseudolegal_recaptures_count ++;
        }
        if(board_10x12[square - 9] == 0){
            pseudolegal_move pseudolegal_recapture;
            pseudolegal_recapture.square_from = get_8x8(square  - 9);
            pseudolegal_recapture.square_to = get_8x8(square);
            pseudolegal_recaptures[pseudolegal_recaptures_count] = pseudolegal_recapture;
            pseudolegal_recaptures_count ++;
        }
    }

    for(int i = 0;i < 8;i++){
        if(get_type(board_10x12[square + knight_moveset[i]]) == 1 and isenemy(piece_moved, board_10x12[square + knight_moveset[i]])){
            pseudolegal_move pseudolegal_recapture;
            pseudolegal_recapture.square_from = get_8x8(square + knight_moveset[i]);
            pseudolegal_recapture.square_to = get_8x8(square);
            pseudolegal_recaptures[pseudolegal_recaptures_count] = pseudolegal_recapture;
            pseudolegal_recaptures_count ++;//knight of opposite colour recapture
        }
    }

    for(int i = 0;i < 8;i++){
        if(get_type(board_10x12[square + king_moveset[i]]) == 5 and isenemy(piece_moved, board_10x12[square + king_moveset[i]])){
            pseudolegal_move pseudolegal_recapture;
            pseudolegal_recapture.square_from = get_8x8(square + king_moveset[i]);
            pseudolegal_recapture.square_to = get_8x8(square);
            pseudolegal_recaptures[pseudolegal_recaptures_count] = pseudolegal_recapture;
            pseudolegal_recaptures_count ++;//opposite colour recapture
        }
    }

    queen_check_1.movegen(square, board, board_10x12);

    for(int i = 0;i < 100;i++){//loop through rook-like moves
        pseudolegal_move move = moves[i];
        if(move.square_from == 0 and move.square_to == 0){
            last_queen1_move = i;
            break;
        }

        if(isenemy(piece_moved, board[move.square_to]) == true){//is of opposite colour
            if(get_type(board[move.square_to]) == 4 or get_type(board[move.square_to]) == 3){//queen or rook
                pseudolegal_move pseudolegal_recapture;
                pseudolegal_recapture.square_from = move.square_to;
                pseudolegal_recapture.square_to = get_8x8(square);
                pseudolegal_recaptures[pseudolegal_recaptures_count] = pseudolegal_recapture;
                pseudolegal_recaptures_count ++;
            }
        }
    }

    queen_check_2.movegen(square, board, board_10x12);

    for(int i = last_queen1_move;i < 100;i++){//loop through bishop-like moves
        pseudolegal_move move = moves[i];
        if(move.square_from == 0 and move.square_to == 0){
            break;
        }
        if(isenemy(piece_moved, board[move.square_to]) == true){//is of opposite colour
            if(get_type(board[move.square_to]) == 4 or get_type(board[move.square_to]) == 2){//queen or bishop
                pseudolegal_move pseudolegal_recapture;
                pseudolegal_recapture.square_from = move.square_to;
                pseudolegal_recapture.square_to = get_8x8(square);
                pseudolegal_recaptures[pseudolegal_recaptures_count] = pseudolegal_recapture;
                pseudolegal_recaptures_count ++;
            }
        }
    }

    for(int i = 0;i < pseudolegal_recaptures_count;i++){
        pseudolegal_move move = pseudolegal_recaptures[i];
        if(islegal(move, board, board_10x12) == true){
            Move recapture;           
            
            recapture.square_from = move.square_from;
            recapture.square_reset = board_10x12[square];
            recapture.square_to = move.square_to;
            recapture.type = normal;
            
            recapture.wkca_reset = white_kingside_castling;
            recapture.wqca_reset = white_queenside_castling;
            recapture.bkca_reset = black_kingside_castling;
            recapture.bqca_reset = black_queenside_castling;

            recapture.ep_square = en_passant_square;
            recapture.fifty_moves_reset = fifty_moves;
            recapture.promote_to = -1;//will be changed later if it is a promotion

            recaptures[recaptures_count] = recapture;
            recaptures_count ++;

            if((get_rank(move.square_to) == 1 or get_rank(move.square_to) == 8) and get_type(board[move.square_from]) == 0){
                recapture.type = promotion;
                recapture.promote_to = 4 * get_colour(board[move.square_from]);//only includes queen promotions
            }
        }

    }

    moves = moves_reset;
    moves_count = moves_count_reset;
}

int recapture_search(int board[], int board_10x12[], int alpha, int beta){

    /**This is essentially a mini version of a quiescence function. Instead of considering all captures, it only considers captures 
     * on the square that was just moved onto (hugely decreasing the number of nodes searched). I thought this was an interesting idea,
     * although a well-designed quiescence function would certainly be better. 
    */

    int eval = evaluate(board);//lower bound for best score for side to move, assuming they are not in zugzwang


    if(eval >= beta){//opponent had a better option earlier
        return beta;
    }
    alpha = max(alpha, eval);
    
    get_recaptures(sq_moved_onto, board, board_10x12);

    if(recaptures[0].square_from == -1){//there are no recaptures available
        return eval;//side to move doesn't matter here
    }

    array <Move, 100> child_recaptures;
    child_recaptures = recaptures;

    int max_eval = eval;//otherwise good positions in which all captures are bad will be evaluated as bad
    for(int i = 0;i < 100;i++){

        Move recapture = child_recaptures[i];

        if(recapture.square_from == -1){
            break;
        }

        int temp_board[64];
        int temp_10x12[120];

        for(int i = 0; i < 64;i++){
            temp_board[i] = board[i];
        }
        for(int i = 0; i < 120;i++){
            temp_10x12[i] = board_10x12[i];
        }//make copies of both boards

        recapture.make_move(temp_board, temp_10x12);

        int new_eval =  - recapture_search(temp_board, temp_10x12, alpha, beta);//negated as this will be from opponent's perspective

        max_eval = max(max_eval, new_eval);
        recapture.undo_move(temp_board, temp_10x12);
    }
    return max_eval;

}

int negamax(int depth, int board[], int board_10x12[], int alpha, int beta){

    /**
     * Negamax is used to evaluate the position by searching. It is based on minimax, but it instead evaluates positions from the
     * perspective of the side to move, rather than always from white perspective. It calls recapture_search() to evaluate positions
     * to try to prevent the horizon effect.
    */

    if(depth == 0){
        return recapture_search(board, board_10x12, alpha, beta);//has already been negated in recursive function call        
    }

    if(fifty_moves == 100){//100 tempi - fifty move rule draw
        return 0;
    }

    get_legal(board, board_10x12);//get ordered moves

    if(legal_moves[0].square_from == -1){ 
        return - ischeckmate(board, board_10x12);//if game ends. negated to "cancel out" negamax call being negated
    }    
    //this is risky as we can't detect if leaf nodes are checkmate. however, this way we can detect 
    //checkmate in other nodes at 0 cost since we needed to generate moves anyway. this should greatly improve search speed.

    int max_eval = negative_infinity;
    array <Move, 100> child_nodes = legal_moves;

    int temp_board[64];
    int temp_10x12[120];

    for(int i = 0; i < 64;i++){
        temp_board[i] = board[i];
    }
    for(int i = 0; i < 120;i++){
        temp_10x12[i] = board_10x12[i];
    }//make copies of both boards

    for(int i = 0;i < 100;i ++){//loop through child nodes
        //here alpha keeps track of our best option on this node, and beta keeps track of opponent's best option on the previous node
        Move move = child_nodes[i];

        if(move.square_from == -1){            
            break;//break if we reach the last used slot of the array
        }

        move.make_move(temp_board, temp_10x12);//make move on temp_board
        sq_moved_onto = move.square_to;
        int new_eval = - negamax(depth - 1, temp_board, temp_10x12, - beta, - alpha);//recursively call negamax at depth - 1, negating result from opponent's perspective
        max_eval = max(new_eval,max_eval);//see if new eval beats previous best        
        move.undo_move(temp_board,temp_10x12);

        if(new_eval >= beta){//opponent had a better option earlier on
            return beta;
        }
        alpha = max(alpha, new_eval);
                        
    }

    return max_eval;//return max

}

int choose_move(){//function to choose the best move in the current position by calling negamax()   
    get_legal(board, board_10x12);
    array <Move, 100> legal_moves_reset = legal_moves;
 
    int best_score = negative_infinity;//initialise as being mated as any move will beat this score
    //we are trying to get the lowest score possible, since it is from the opponent's perspective
    int move_index = 0;
    int best_index = 0;

    int search_board[64];
    int search_10x12[120];//create copies of the current board to search on

    for(int i = 0;i < 64; i++){
        search_board[i] = board[i];
    }
    for(int i = 0;i < 120; i++){
        search_10x12[i] = board_10x12[i];
    }//copies content of arrays
    
    array <Move, 100> search_moves = legal_moves;
    for(int i = 0;i < 100;i++){//loops through child nodes
        Move move = search_moves[i];
        if(move.square_from == -1){
            break;
        }

        move.make_move(search_board, search_10x12);
        int score = - negamax(4, search_board, search_10x12, negative_infinity, positive_infinity);//negated because it is called from opponents perspective
        move.undo_move(search_board, search_10x12);        

        if(score > best_score){//side-to-move always trying to maximise their own eval
            best_index = move_index;
            best_score = score;            
        }            
        move_index ++;
    }

    cout << "Eval: " << best_score << "\n";

    legal_moves = legal_moves_reset;
    return best_index;//return index of best move
}







