#include <iostream>
#include <array>
#include "eval.cpp"

/**
 * This file handles the engine's search, containing the minimax function and also the function to choose 
 * the best move. 
*/

using namespace std;




int minimax(int depth, bool maximsing_player, int board[], int board_12x12[], int alpha, int beta){//function to get an evalution for child nodes using search

    /**
     * Minimax is an algorithm often used in zero-sum games such as chess, go and shogi. The function calls
     * itself recursively until a depth of 0 is reached, when it statically evaluates the position.
    */

    if(depth == 0){
        return evaluate(board);//static evaluation
    }

    if(maximsing_player){//white is the maximising player
        int max_eval  = negative_infinity;//initialise as very low so that any move will beat it
        get_legal(board, board_12x12);//first get legal moves

        array<Move, 218> child_nodes = legal_moves;//copy legal_moves onto another array so that the real
                                                   // array is not interfered with 
        int temp_board[64];
        int temp_12x12[144];

        for(int i = 0; i < 64;i++){
            temp_board[i] = board[i];
        }
        for(int i = 0; i < 144;i++){
            temp_12x12[i] = board_12x12[i];
        }//make copies of both boards

        for(int i = 0;i < 218;i ++){//loop through child nodes
            Move move = child_nodes[i];
            if(move.square_from == -1){
                break;//break if we reach the last used slot of the array
            }

            move.make_move(temp_board, temp_12x12);//make move on temp_board
            int new_eval = minimax(depth -1, false, temp_board, temp_12x12, alpha, beta);//recursively call minimax at depth -1
            max_eval = max(new_eval,max_eval);//see if new eval beats previous best
            alpha = max(alpha, new_eval);
            move.undo_move(temp_board,temp_12x12);
            if(beta <= alpha){
                break;//black would avoid this line anyway, so no point analysing further
            }
                        
        }
        return max_eval;//return max
    }
    else{//as above
        int min_eval = positive_infinity;
        get_legal(board, board_12x12);

        array<Move, 218> child_nodes = legal_moves;//copy legal_moves array

        int temp_board[64];
        int temp_12x12[144];

        for(int i = 0; i < 64;i++){
            temp_board[i] = board[i];
        }
        for(int i = 0; i < 144;i++){
            temp_12x12[i] = board_12x12[i];
        }//create temporary boards


        for(int i = 0;i< 218; i++){//loop through child nodes
            Move move = child_nodes[i];
            if(move.square_from == -1){
                break;
            }

            move.make_move(temp_board,temp_12x12);
            
            int new_eval = minimax(depth -1, true, temp_board, temp_12x12, alpha, beta);
            min_eval = min(new_eval,min_eval);
            beta = min(beta, new_eval);
            move.undo_move(temp_board,temp_12x12);
            if(beta <= alpha){
                break;//white would avoid this
            }
                        
        }
        return min_eval;//return min
    }
}

int choose_move(){//function to choose the best move in the current position by calling minimax()    


    if(white_to_move(tempi) == true){
        int best_score = negative_infinity;//initialise as being mated as any move will beat this score
        int move_index = 0;
        int best_index = 0;

        int search_board[64];
        int search_12x12[144];//creates copies of the board to perform the search on

        for(int i = 0;i < 64; i++){
            search_board[i] = board[i];
        }
        for(int i = 0;i < 144; i++){
            search_12x12[i] = board_12x12[i];
        }//copies contents of board arrays
    
        array <Move, 218> search_moves = legal_moves;//makes copy of legal_moves array
        for(int i = 0;i < 218;i++){
            Move move = search_moves[i];
            if(move.square_from == -1){
                break;
            }
            int score;
            move.make_move(search_board, search_12x12);
            if(white_to_move(tempi) == true){
                score = minimax(5, true,search_board, search_12x12, negative_infinity, positive_infinity);//calls minimax() to get eval of position
            }
            else{
                score = minimax(5, false, search_board, search_12x12, negative_infinity, positive_infinity);
            }
            if(score > best_score){//update if we find a new best move
                best_index = move_index;
                best_score = score;            
            }

            move.undo_move(search_board, search_12x12);
            move_index ++;
        }
        cout << "eval: " << best_score << endl;
        return best_index;
    }
    else{
        int best_score = positive_infinity;//initialise as being mated as any move will beat this score
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
    
        array <Move, 218> search_moves = legal_moves;
        for(int i = 0;i < 218;i++){//loops through child nodes
            Move move = search_moves[i];
            if(move.square_from == -1){
                break;
            }
            int score;
            move.make_move(search_board, search_12x12);
            if(white_to_move(tempi) == true){
                score = minimax(5, true,search_board, search_12x12, negative_infinity, positive_infinity);//gets score from minimax()
            }
            else{
                score = minimax(5, false, search_board, search_12x12, negative_infinity, positive_infinity);
            }
            if(score < best_score){//black is trying to minimise score
                best_index = move_index;
                best_score = score;            
            }

            move.undo_move(search_board, search_12x12);
            move_index ++;
        }
        cout << "eval: " << best_score << endl;
        return best_index;
    }
}






