#include <iostream>
#include "movegen.cpp"
using namespace std;

int legal_moves[218][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
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
                    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};//this time LEGAL moves only



void get_w_pseudolegal(){

    for(int i = 0;i<218;i++){
        moves[i][0] = -1;
        moves[i][1] = -1;
    }  

    piece w_pawn;
    w_pawn.board_code = 0;
    w_pawn.fen_code = 'p';
    w_pawn.slider = false;
    w_pawn.piece_count = 8;
    w_pawn.moveset[0] = 12;
    w_pawn.moveset[1] = 24;
    w_pawn.moveset[2] = 13;
    w_pawn.moveset[3] = 11;

    piece w_knight1;//forward moves
    w_knight1.board_code = 1;
    w_knight1.fen_code = 'n';
    w_knight1.slider = false;
    w_knight1.piece_count = 2;
    w_knight1.moveset[0] = 14;
    w_knight1.moveset[1] = 25;
    w_knight1.moveset[2] = 23;
    w_knight1.moveset[3] = 10;

    piece w_knight2;//backward moves
    w_knight2.board_code = 1;
    w_knight2.fen_code = 'n';
    w_knight2.slider = false;
    w_knight2.piece_count = 2;
    w_knight2.moveset[0] = -14;
    w_knight2.moveset[1] = -25;
    w_knight2.moveset[2] = -23;
    w_knight2.moveset[3] = -10;

    piece w_bishop;
    w_bishop.board_code = 2;
    w_bishop.fen_code = 'b';
    w_bishop.slider = true;
    w_bishop.piece_count = 2;
    w_bishop.moveset[0] = 11;
    w_bishop.moveset[1] = 13;
    w_bishop.moveset[2] = -11;
    w_bishop.moveset[3] = -13;

    piece w_rook;
    w_rook.board_code = 3;
    w_rook.fen_code = 'r';
    w_rook.slider = true;
    w_rook.piece_count = 2;
    w_rook.moveset[0] = 12;
    w_rook.moveset[1] = 1;
    w_rook.moveset[2] = -1;
    w_rook.moveset[3] = -12;

    piece w_queen1;//like rook
    w_queen1.board_code = 4;
    w_queen1.fen_code = 'q';
    w_queen1.slider = true;
    w_queen1.piece_count = 1;
    w_queen1.moveset[0] = 12;
    w_queen1.moveset[1] = 1;
    w_queen1.moveset[2] = -1;
    w_queen1.moveset[3] = -12;

    piece w_queen2;
    w_queen2.board_code = 4;
    w_queen2.fen_code = 'q';
    w_queen2.slider = true;
    w_queen2.piece_count = 1;
    w_queen2.moveset[0] = 11;
    w_queen2.moveset[1] = 13;
    w_queen2.moveset[2] = -11;
    w_queen2.moveset[3] = -13;

    piece w_king1;//moves like rook
    w_king1.board_code = 5;
    w_king1.fen_code = 'k';
    w_king1.slider = false;
    w_king1.piece_count = 1;
    w_king1.moveset[0] = 12;
    w_king1.moveset[1] = 1;
    w_king1.moveset[2] = -1;
    w_king1.moveset[3] = -12;

    piece w_king2;//moves like bishop
    w_king2.board_code = 5;
    w_king2.fen_code = 'k';
    w_king2.slider = false;
    w_king2.piece_count = 1;
    w_king2.moveset[0] = 11;
    w_king2.moveset[1] = 13;
    w_king2.moveset[2] = -11;
    w_king2.moveset[3] = -13;

    moves_count = 0;

    w_pawn.find_piece();

    for(int i = 0;i < 10;i++){//never more than 10 of a certain piece on the board
        if(squares_found[i] == -1){
            break;
        }
        w_pawn.movegen(squares_found[i]);
        
    }

    w_knight1.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        w_knight1.movegen(squares_found[i]);
        
    }

    w_knight2.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        w_knight2.movegen(squares_found[i]);
        
    }

    w_bishop.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        w_bishop.movegen(squares_found[i]);
        
    }

    w_rook.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        w_rook.movegen(squares_found[i]);
        
    }

    w_queen1.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        w_queen1.movegen(squares_found[i]);
        
    }

    w_queen2.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        w_queen2.movegen(squares_found[i]);
        
    }

    w_king1.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        w_king1.movegen(squares_found[i]);
        
    }

    w_king2.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        w_king2.movegen(squares_found[i]);
        
    }

        
}

void get_b_pseudolegal(){

    for(int i = 0;i<218;i++){
        moves[i][0] = -1;
        moves[i][1] = -1;
    } 
        //BLACK PIECES:

    piece b_pawn;
    b_pawn.board_code = 24;
    b_pawn.fen_code = 'P';
    b_pawn.slider = false;
    b_pawn.piece_count = 8;
    b_pawn.moveset[0] = -12;
    b_pawn.moveset[1] = -24;
    b_pawn.moveset[2] = -13;
    b_pawn.moveset[3] = -11;

    piece b_knight1;//backward moves
    b_knight1.board_code = 25;
    b_knight1.fen_code = 'N';
    b_knight1.slider = false;
    b_knight1.piece_count = 2;
    b_knight1.moveset[0] = 14;
    b_knight1.moveset[1] = 25;
    b_knight1.moveset[2] = 23;
    b_knight1.moveset[3] = 10;

    piece b_knight2;//forward moves
    b_knight2.board_code = 25;
    b_knight2.fen_code = 'N';
    b_knight2.slider = false;
    b_knight2.piece_count = 2;
    b_knight2.moveset[0] = -14;
    b_knight2.moveset[1] = -25;
    b_knight2.moveset[2] = -23;
    b_knight2.moveset[3] = -10;

    piece b_bishop;
    b_bishop.board_code = 26;
    b_bishop.fen_code = 'B';
    b_bishop.slider = true;
    b_bishop.piece_count = 2;
    b_bishop.moveset[0] = 11;
    b_bishop.moveset[1] = 13;
    b_bishop.moveset[2] = -11;
    b_bishop.moveset[3] = -13;

    piece b_rook;
    b_rook.board_code = 27;
    b_rook.fen_code = 'R';
    b_rook.slider = true;
    b_rook.moveset[0] = 12;
    b_rook.moveset[1] = 1;
    b_rook.moveset[2] = -1;
    b_rook.moveset[3] = -12;

    piece b_queen1;//like rook
    b_queen1.board_code = 4;
    b_queen1.fen_code = 'Q';
    b_queen1.slider = true;
    b_queen1.piece_count = 1;
    b_queen1.moveset[0] = 12;
    b_queen1.moveset[1] = 1;
    b_queen1.moveset[2] = -1;
    b_queen1.moveset[3] = -12;

    piece b_queen2;
    b_queen2.board_code = 28;
    b_queen2.fen_code = 'Q';
    b_queen2.slider = true;
    b_queen2.piece_count = 1;
    b_queen2.moveset[0] = 11;
    b_queen2.moveset[1] = 13;
    b_queen2.moveset[2] = -11;
    b_queen2.moveset[3] = -13;

    piece b_king1;//moves like rook
    b_king1.board_code = 29;
    b_king1.fen_code = 'K';
    b_king1.slider = false;
    b_king1.piece_count = 1;
    b_king1.moveset[0] = 12;
    b_king1.moveset[1] = 1;
    b_king1.moveset[2] = -1;
    b_king1.moveset[3] = -12;

    piece b_king2;//moves like bishop
    b_king2.board_code = 29;
    b_king2.fen_code = 'K';
    b_king2.slider = false;
    b_king2.piece_count = 1;
    b_king2.moveset[0] = 11;
    b_king2.moveset[1] = 13;
    b_king2.moveset[2] = -11;
    b_king2.moveset[3] = -13;

    
    moves_count = 0;
  
    b_pawn.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        b_pawn.movegen(squares_found[i]);
        
    }

    b_knight1.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        b_knight1.movegen(squares_found[i]);
        
    }

    b_knight2.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        b_knight2.movegen(squares_found[i]);
        
    }

    b_bishop.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        b_bishop.movegen(squares_found[i]);
        
    }

    b_rook.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        b_rook.movegen(squares_found[i]);
        
    }

    b_queen1.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        b_queen1.movegen(squares_found[i]);
        
    }

    b_queen2.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        b_queen2.movegen(squares_found[i]);
        
    }

    b_king1.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        b_king1.movegen(squares_found[i]);
        
    }

    b_king2.find_piece();

    for(int i = 0;i < 10;i++){
        if(squares_found[i] == -1){
            break;
        }
        b_king2.movegen(squares_found[i]);
        
    }
}

bool ischeck(int colour_to_test, int square_from, int square_to){

    
    int check_count = 0;
    int temp;
    int moves_count_reset = 0;
    moves_count_reset = moves_count;
    


    temp = board_12x12[get_12x12(square_to)];
    board_12x12[get_12x12(square_to)] = board_12x12[get_12x12(square_from)];
    board_12x12[get_12x12(square_from)] = -6;

    board[square_to] = board[square_from];
    board[square_from] = -6;

    int king_square;//will be assigned a value once king is found
    
    int first_knight1_move;
    int first_knight2_move;
    int first_queen1_move;
    int first_queen2_move;
    int first_king1_move;
    int first_king2_move;
    int last_move;//used so I don't have to loop through the whole moves array

    piece knight_check_1;
    knight_check_1.slider = false;
    knight_check_1.board_code = colour_to_test;//this way isenemy() calculations will always work
    knight_check_1.moveset[0] = 14;
    knight_check_1.moveset[1] = 25;
    knight_check_1.moveset[2] = 23;
    knight_check_1.moveset[3] = 10;

    piece knight_check_2;
    knight_check_2.slider = false;
    knight_check_2.board_code = colour_to_test;
    knight_check_2.moveset[0] = -14;
    knight_check_2.moveset[1] = -25;
    knight_check_2.moveset[2] = -23;
    knight_check_2.moveset[3] = -10;

    piece queen_check_1;//also rook
    queen_check_1.slider = true;
    queen_check_1.board_code = colour_to_test;
    queen_check_1.moveset[0] = 12;
    queen_check_1.moveset[1] = 1;
    queen_check_1.moveset[2] = -12;
    queen_check_1.moveset[3] = -1;

    piece queen_check_2;//also bishop
    queen_check_2.slider = true;
    queen_check_2.board_code = colour_to_test;
    queen_check_2.moveset[0] = 11;
    queen_check_2.moveset[1] = 13;
    queen_check_2.moveset[2] = -11;
    queen_check_2.moveset[3] = -13;

    piece king_check_1;
    king_check_1.board_code = colour_to_test;
    king_check_1.slider = false;
    king_check_1.moveset[0] = 12;
    king_check_1.moveset[1] = 1;
    king_check_1.moveset[2] = -12;
    king_check_1.moveset[3] = -1;

    piece king_check_2;
    king_check_2.board_code = colour_to_test;
    king_check_2.slider = false;
    king_check_2.moveset[0] = 13;
    king_check_2.moveset[1] = 11;
    king_check_2.moveset[2] = -13;
    king_check_2.moveset[3] = -11;

    for(int i = 0;i < 64; i++){
        if(board[i] == colour_to_test){
            king_square = get_12x12(i);
            break;
        }
    }


    if(colour_to_test == 5){
        if(board_12x12[king_square + 11] == 24 or board_12x12[king_square + 13] == 24){            
            check_count++;
            
        }
    }
    else{
        if(board_12x12[king_square - 11] == 0 or board_12x12[king_square - 13] == 0){
            check_count++;
            
        }

    }

    first_knight1_move = moves_count;
    knight_check_1.movegen(king_square);  
    first_knight2_move = moves_count;//also last knight1 move

    for(int i = first_knight1_move;i < first_knight2_move;i++ ){
        if(get_type(board_12x12[get_12x12(moves[i][1])]) == 1 and isenemy(colour_to_test, board_12x12[get_12x12(moves[i][1])]) == true){
            check_count++;            
            
        }
    }

    knight_check_2.movegen(king_square);
    first_queen1_move = moves_count;
    

    for(int i = first_knight2_move;i < first_queen1_move;i++ ){
        if(get_type(board_12x12[get_12x12(moves[i][1])]) == 1 and isenemy(colour_to_test, board_12x12[get_12x12(moves[i][1])])==true){
            check_count++;
            
            
        }
    }

    queen_check_1.movegen(king_square);
    first_queen2_move = moves_count;

    for(int i = first_queen1_move;i < first_queen2_move;i++ ){
        if(get_type(board_12x12[get_12x12(moves[i][1])]) == 4 or get_type(board_12x12[get_12x12(moves[i][1])]) == 3){//either queen or rook
            if(isenemy(colour_to_test, board_12x12[get_12x12(moves[i][1])]) == true){
                check_count++;
                
                
            }
            
        }
    }

    queen_check_2.movegen(king_square);
    first_king1_move = moves_count;
    

    for(int i = first_queen2_move;i < first_king1_move;i++ ){
        if(get_type(board_12x12[get_12x12(moves[i][1])]) == 4 or get_type(board_12x12[get_12x12(moves[i][1])]) == 2){//either queen or bishop
            if(isenemy(colour_to_test, board_12x12[get_12x12(moves[i][1])]) == true){
                check_count++;
                
                
            }
            
        }
    }

    king_check_1.movegen(king_square);
    first_king2_move = moves_count;

    for(int i = first_king1_move;i < first_king2_move;i++ ){
        if(get_type(board_12x12[get_12x12(moves[i][1])]) == 5){//if king
            if(isenemy(colour_to_test, board_12x12[get_12x12(moves[i][1])]) == true){
                check_count++;                
                
            }
            
        }
    }

    king_check_2.movegen(king_square);
    last_move = moves_count;

    for(int i = first_king2_move;i < 218;i++ ){
        if(moves[i][0] == -1){
            break;
        }
        if(get_type(board_12x12[get_12x12(moves[i][1])]) == 5){//if king
            if(isenemy(colour_to_test, board_12x12[get_12x12(moves[i][1])]) == true){
                check_count++;               
                
            }
            
        }
    }


    board_12x12[get_12x12(square_from)] = board_12x12[get_12x12(square_to)];
    board_12x12[get_12x12(square_to)] = temp;//reset board

    board[square_from] = board[square_to];
    board[square_to] = temp;




    for(int i = moves_count_reset;i<218;i++){

        moves[i][0] = -1;
        moves[i][1] = -1;

    }//reset moves array

    for(int i = 0;i < 218;i++){
        if(moves[i][0] == -1){
            break;
        }
    }

    moves_count = moves_count_reset;
 

    if(check_count == 0){
        return false;
    }
    return true;
    

}

int get_legal(){  

    int legal_count;
  

    if(white_to_move(tempi) == 0){

        int temp;

        get_w_pseudolegal();//first get white's pseudolegal moves
        temp = moves_count;


        legal_count = 0;//number of legal moves found
        for(int i = 0; i < 218; i++){

            if(moves[i][0] == -1){
                break;
            } 

            /**
             * NOW TO CHECK IF A PSEUDOLEGAL MOVE LEAVES OUR KING IN CHECK
             * - create objects with king's board code and move_set of inverse of black pieces
             * - use movegen() function on this piece
             * - if this function finds the piece whose moveset it is inversing, discard the move
             * - if after all movesets no enemy piece is found, add to legal_moves
            */ 

            if(ischeck(5, moves[i][0], moves[i][1]) == false){
                legal_moves[legal_count][0] = moves[i][0];
                legal_moves[legal_count][1] = moves[i][1];
                legal_count++;

            }                      
 

        }       

        

    }

    else{
        get_b_pseudolegal();//first get white's pseudolegal moves
        legal_count = 0;//number of legal moves found
        for(int i = 0; i < 218; i++){

            if(moves[i][0] == -1){
                break;
            } 

            if(ischeck(29, moves[i][0], moves[i][1]) == false){
                legal_moves[legal_count][0] = moves[i][0];
                legal_moves[legal_count][1] = moves[i][1];
                legal_count++;

            }   
                    
 

            /**
             * NOW TO CHECK IF A PSEUDOLEGAL MOVE LEAVES OUR KING IN CHECK
             * - create objects with king's board code and move_set of inverse of black pieces
             * - use movegen() function on this piece
             * - if this function finds the piece whose moveset it is inversing, discard the move
             * - if after all movesets no enemy piece is found, add to legal_moves
            */            

           

            

            
        }
    }

    return legal_count;

}

void get_all_moves(bool w_kside, bool w_qside, bool b_kside, bool b_qside){//includes castling and promotion
                     //this function should be called to get a complete list of legal moves in a position
                     // as it already calls get_legal()
    int last_move_index;
    int last_added_move_index;
    int promotion_vector;  

    for(int i = 0;i<218;i++){
        legal_moves[i][0] = -1;
        legal_moves[i][1] = -1;
    }  
    
    last_move_index = get_legal();
    last_added_move_index = last_move_index;

    for(int i = 0;i < last_move_index;i++){//promotion logic
        if(legal_moves[i][0] == -1){
            break;
        }
        if(board_12x12[get_12x12(legal_moves[i][0])] == 0 and get_rank(legal_moves[i][1]) == 8){
            //white pawn to 8th rank
            promotion_vector = legal_moves[i][1] - legal_moves[i][0];
            legal_moves[i][1] = promotion_vector * 10 + 1;//important because promotions can also be captures
            
            for(int j = 2;j < 5;j++){
                legal_moves[last_added_move_index][0] = legal_moves[i][0];//here j effectively becomes the piece we promtote to
                legal_moves[last_added_move_index][1] = promotion_vector * 10 + j;//in make_move() we then subtract 64 from the destination square
                last_added_move_index++;// to get the piece to promote to
            }
            
            
        }

        else if(board_12x12[get_12x12(legal_moves[i][0])] == 24 and get_rank(legal_moves[i][1]) == 1){
            //white pawn to 8th rank
            legal_moves[i][1] = promotion_vector * 10 - 1;//here promotion vector will be negative
            
            for(int j = 26;j < 29;j++){
                legal_moves[last_added_move_index][0] = legal_moves[i][0];//here j effectively becomes the piece we promtote to
                legal_moves[last_added_move_index][1] = promotion_vector * 10 - j;//in make_move() we then subtract 64 from the destination square
                last_added_move_index++;// to get the piece to promote to
            }
            
            
        }
    }


    if(white_to_move(tempi) == 0){//castling logic
        if(w_kside == true){//kside rights and white to move
            if(board_12x12[get_12x12(5)] == -6 and board_12x12[get_12x12(6)] == -6){//if nothing between king and rook
                if(ischeck(5,4,5) == false and ischeck(5,4,6) == false){
                    legal_moves[last_added_move_index][0] = 4;
                    legal_moves[last_added_move_index][1] = 6;  
                    last_added_move_index ++;              
                }
            }
        
        }

        if(w_qside == true){//qside right and white to move
            if(board_12x12[get_12x12(1)] == -6 and board_12x12[get_12x12(2)] == -6 and board_12x12[get_12x12(3)] == -6){//if nothing between king and rook
                if(ischeck(5,4,3) == false and ischeck(5,4,2) == false){
                    legal_moves[last_added_move_index][0] = 4;
                    legal_moves[last_added_move_index][1] = 2;
                    last_added_move_index ++;                 
                }
            }

        } 
    }

    else{
        if(b_kside == true){//kside rights and black to move
            if(board_12x12[get_12x12(61)] == -6 and board_12x12[get_12x12(62)] == -6){//if nothing between king and rook
                if(ischeck(29,60,61) == false and ischeck(29,60,62) == false){
                    legal_moves[last_added_move_index][0] = 60;
                    legal_moves[last_added_move_index][1] = 62; 
                    last_added_move_index ++;                
                }
            }
        
        }

        if(b_qside == true and white_to_move(tempi) == 0){//qside right and black to move
            if(board_12x12[get_12x12(57)] == -6 and board_12x12[get_12x12(58)] == -6 and board_12x12[get_12x12(59)] == -6){//if nothing between king and rook
                if(ischeck(29,60,59) == false and ischeck(29,60,58) == false){
                    legal_moves[last_added_move_index][0] = 60;
                    legal_moves[last_added_move_index][1] = 58; 
                    last_added_move_index ++;                
                }
            }

        } 
    }    
    


}

void make_move(int square_from, int square_to){    

    int promotion_square_to;

    for(int i = 0;i < 64;i++){
        if(board[i] == 30){
            board[i] = -6;//remove old en passant squares
            board_12x12[get_12x12(i)] = -6;
        }
    }

    if(white_to_move(tempi) == 0){
        
        if(square_to > 90){
            board[square_from] = -6;
            board_12x12[get_12x12(square_from)] = -6;
            promotion_square_to = square_from + 9;
            board[promotion_square_to] = square_to - 90;//see get_all_moves() for explanation
            board_12x12[get_12x12(promotion_square_to)] = square_to - 90;
            tempi ++; 
            return;

        }
        else if(square_to > 80){
            board[square_from] = -6;
            board_12x12[get_12x12(square_from)] = -6;
            promotion_square_to = square_from + 8;
            board[promotion_square_to] = square_to - 80;//see get_all_moves() for explanation
            board_12x12[get_12x12(promotion_square_to)] = square_to - 80;
            tempi ++; 
            return;

        }
        else if(square_to > 70){
            board[square_from] = -6;
            board_12x12[get_12x12(square_from)] = -6;
            promotion_square_to = square_from + 7;
            board[promotion_square_to] = square_to - 70;//see get_all_moves() for explanation
            board_12x12[get_12x12(promotion_square_to)] = square_to - 70; 
            tempi ++;
            return;

        }
    }
    else{
        if(square_to < -114){
            board[square_from] = -6;
            board_12x12[get_12x12(square_from)] = -6;
            promotion_square_to = square_from - 9;
            board[promotion_square_to] = (square_to - 90) * -1;//see get_all_moves() for explanation
            board_12x12[get_12x12(promotion_square_to)] = (square_to - 90) * -1;
            tempi ++;
            return;

        }
        else if(square_to < -104){
            board[square_from] = -6;
            board_12x12[get_12x12(square_from)] = -6;
            promotion_square_to = square_from - 8;
            board[promotion_square_to] = (square_to - 80) * -1;//see get_all_moves() for explanation
            board_12x12[get_12x12(promotion_square_to)] = (square_to - 80) * -1;
            tempi ++;
            return;

        }
        else if(square_to < -94){
            board[square_from] = -6;
            board_12x12[get_12x12(square_from)] = -6;
            promotion_square_to = square_from - 7;
            board[promotion_square_to] = (square_to - 70) * -1;//see get_all_moves() for explanation
            board_12x12[get_12x12(promotion_square_to)] = (square_to - 70) * -1;
            tempi ++;
            return;

        }
    }

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

    if(board[square_from] == 29){//if black king is moved
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

    if(board[square_from] != 0 and board[square_from] != 24 and board[square_to] == -6){//no pawn move or capture        
        fifty_moves ++;
        
    }
    else{//reset fifty move rule
        fifty_moves = 0;
    }

    if(board[square_from] == 0 and (square_to == square_from + 16)){
        board[square_from + 8] = 30;
        board_12x12[get_12x12(square_from) + 12] = 30;// add en passant square
    }

    else if(board[square_from] == 24 and (square_to == square_from - 16)){
        board[square_from - 8] = 30;
        board_12x12[get_12x12(square_from) - 12] = 30;//add en passant square
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
        tempi ++;
    }


}