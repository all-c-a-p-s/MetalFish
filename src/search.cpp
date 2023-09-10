#include <iostream>
#include <array>
#include "eval.cpp"

/**
 * This file handles the engine's search, containing the negamax function and also the function to choose 
 * the best move. 
*/
using namespace std;

int sq_moved_onto;//to be used in recapture search

int recapture_search(int board[], int board_12x12[], int alpha, int beta, int depth){

    /**This is essentially a mini version of a quiescence function. Instead of considering all captures, it only considers captures 
     * on the square that was just moved onto (hugely decreasing the number of nodes searched). I thought this was an interesting idea,
     * although a well-designed quiescence function would certainly be better. 
    */

    int eval = evaluate(board);//lower bound for best score for side to move, assuming they are not in zugzwang


    if(eval >= beta){//black had a better option earlier
        return beta;
    }
    alpha = max(alpha, eval);



    if(depth != 0){//no point generating moves if they have already been generated in negamax()
        get_legal(board, board_12x12);
        if(legal_moves[0].square_from == -1){
            return ischeckmate(board, board_12x12);//check for game ends
        }
    }

    array <Move, 100> recaptures;
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

    for(int i = 0;i < 100;i++){
        recaptures[i] = blank_move;
    }//reset recaptures array

    int recaptures_count;
    recaptures_count = 0;

    for(int i = 0;i < 100;i++){
        Move move = legal_moves[i];
        if(move.square_from == -1){
            break;
        }
        if(move.square_to == sq_moved_onto){
            recaptures[recaptures_count] = move;
            recaptures_count ++;
        }
    }

    if(recaptures[0].square_from == -1){//there are no recaptures available
        return eval;//side to move doesn't matter here
    }

    int max_eval = eval;//otherwise good positions in which all captures are bad will be evaluated as bad
    for(int i = 0;i < recaptures_count;i++){
        Move recapture = recaptures[i];

        recapture.make_move(board, board_12x12);
        sq_moved_onto = recapture.square_to;

        int new_eval =  - recapture_search(board, board_12x12, alpha, beta, depth + 1);//negated as this will be from opponent's perspective

        max_eval = max(max_eval, new_eval);
        recapture.undo_move(board, board_12x12);
    }
    return max_eval;

}

int negamax(int depth, int board[], int board_12x12[], int alpha, int beta){

    /**
     * Negamax is used to evaluate the position by searching. It is based on minimax, but it instead evaluates positions from the
     * perspective of the side to move, rather than always from white perspective. It calls recapture_search() to evaluate positions
     * to try to prevent the horizon effect.
    */

    if(fifty_moves == 100){//100 tempi - fifty move rule draw
        return 0;
    }

    get_legal(board, board_12x12);//first get legal moves
    if(legal_moves[0].square_from == -1){
        return ischeckmate(board, board_12x12);//if game ends
    }

    if(depth == 0){
        return recapture_search(board, board_12x12, alpha, beta, 0);//has already been negated in recursive function call        
    }

    int max_eval = negative_infinity;
    array <Move, 100> child_nodes = legal_moves;

    int temp_board[64];
    int temp_12x12[144];

    for(int i = 0; i < 64;i++){
        temp_board[i] = board[i];
    }
    for(int i = 0; i < 144;i++){
        temp_12x12[i] = board_12x12[i];
    }//make copies of both boards

    for(int i = 0;i < 100;i ++){//loop through child nodes
        //here alpha keeps track of white's best option on this node, and beta keeps track of black's best option on the previous node
        Move move = child_nodes[i];
        if(move.square_from == -1){
            break;//break if we reach the last used slot of the array
        }

        move.make_move(temp_board, temp_12x12);//make move on temp_board
        sq_moved_onto = move.square_to;
        int new_eval = - negamax(depth - 1, temp_board, temp_12x12, - beta, - alpha);//recursively call negamax at depth - 1, negating result from opponent's perspective
        max_eval = max(new_eval,max_eval);//see if new eval beats previous best
        
        move.undo_move(temp_board,temp_12x12);
        if(new_eval >= beta){
            return beta;
        }
        alpha = max(alpha, new_eval);
                        
    }
    return max_eval;//return max

}

int choose_move(){//function to choose the best move in the current position by calling negamax()   
    get_legal(board, board_12x12);
    array <Move, 100> legal_moves_reset = legal_moves;
 
    int best_score = negative_infinity;//initialise as being mated as any move will beat this score
    //we are trying to get the lowest score possible, since it is from the opponent's perspective
    int move_index = 0;
    int best_index = 0;

    int search_board[64];
    int search_12x12[144];//create copies of the current board to search on

    for(int i = 0;i < 64; i++){
        search_board[i] = board[i];
    }
    for(int i = 0;i < 144; i++){
        search_12x12[i] = board_12x12[i];
    }//copies content of arrays
    
    array <Move, 100> search_moves = legal_moves;
    for(int i = 0;i < 100;i++){//loops through child nodes
        Move move = search_moves[i];
        if(move.square_from == -1){
            break;
        }

        move.make_move(search_board, search_12x12);
        int score = - negamax(4, search_board, search_12x12, negative_infinity, positive_infinity);//negated because it is called from opponents perspective
        move.undo_move(search_board, search_12x12);

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







