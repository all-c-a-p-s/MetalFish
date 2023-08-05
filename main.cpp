#include <iostream>
#include <string>
#include <array>
#include "search.cpp"

/**
 * This file is the only file containing main(), so it is the only one that can be run. It calls functions
 * from other files and handles input/output. * 
*/

using namespace std;

string convert_to_notation(int square){//function to convert square number to algebraic notation

    string first_digit;
    char files_list[8] = {'a','b','c','d','e','f','g','h'};
    int second_digit;
    int temp = (square + 1) % 8 - 1;
    if(temp == -1){//otherwise it will search for element -1 of files_list
    temp = 7;
    }
    first_digit = files_list[temp];
    string final_string;
    for(int i = 0; i < 8; i++){

        if((i + 1) * 8 > square){//loop until correct rank found

            second_digit = i + 1;
            break;

        }

    }

    string second_digit_str = to_string(second_digit);
    final_string = first_digit + second_digit_str;
    return final_string;
}


int convert_to_num(string notation){//function to convert from algebraic notation to square number

    char files_list[8] = {'a','b','c','d','e','f','g','h'};
    string rank_str;
    rank_str += notation[1];//converts char to string
    char file_char;
    file_char = notation[0];
    int num_output;

    for(int i = 0; i < 9; i++){

        if(file_char == files_list[i]){

            num_output = (stoi(rank_str) - 1) * 8 + i;//(rank - 1) * 8 + file

            break;

        }

    }

    return num_output;

}

bool engine_plays_white;//which side engine plays as

void get_user_move(){//function to get and parse the user's input
    if(engine_plays_white == true){//engine is white
        Move move;
        string sq_to;
        string sq_from;
        cout << "square from: " << endl;
        cin >> sq_from ;
        cout << "square to: " << endl;
        cin >> sq_to;
        move.square_from = convert_to_num(sq_from);
        move.square_to = convert_to_num(sq_to);//convert's to engine numeric board notation
        move.square_reset = board[move.square_to];
        if(board[move.square_from] == 24 and (get_rank(move.square_to) == 1)){//black promotes pawn
            cout << "promote to: (capital letter used to notate piece)" << endl;
            char promote_char;
            cin >> promote_char;
            switch(promote_char){//allows user to choose which piece to promote to
                case 'Q':
                    move.promote_to = 28;
                    break;
                case 'R':
                    move.promote_to = 27;
                    break;
                case 'B':
                    move.promote_to = 26;
                    break;
                case 'N':
                    move.promote_to = 25;
            }
            move.type = promotion;
        }
        else{
            move.type = normal;
            move.promote_to = -1;
        }
        move.wkca_reset = white_kingside_castling;
        move.wqca_reset = white_queenside_castling;
        move.bkca_reset = black_kingside_castling;
        move.bqca_reset = black_queenside_castling;
        move.ep_square = en_passant_square;
        move.fifty_moves_reset = fifty_moves;//set values to before the move was made
        move.make_move(board, board_12x12);//make move on board
    }
    else{//engine is black
        Move move;
        string sq_to;
        string sq_from;
        cout << "square from: " << endl;
        cin >> sq_from ;
        cout << "square to: " << endl;
        cin >> sq_to;
        move.square_from = convert_to_num(sq_from);
        move.square_to = convert_to_num(sq_to);
        move.square_reset = board[move.square_to];
        if(get_type(board[move.square_from]) == 0 and (get_rank(move.square_to) == 1 or get_rank(move.square_to) == 8)){//pawn promotion
            cout << "promote to (capital letter used to notate piece): " << endl;
            char promote_char;
            cin >> promote_char;
            switch(promote_char){//allows user to choose which piece to promote to
                case 'Q':
                    move.promote_to = 4;
                    break;
                case 'R':
                    move.promote_to = 3;
                    break;
                case 'B':
                    move.promote_to = 2;
                    break;
                case 'N':
                    move.promote_to = 1;
            }
            move.type = promotion;
    }
    else{
        move.type = normal;
        move.promote_to = -1;
    }
    move.wkca_reset = white_kingside_castling;
    move.wqca_reset = white_queenside_castling;
    move.bkca_reset = black_kingside_castling;
    move.bqca_reset = black_queenside_castling;
    move.ep_square = en_passant_square;
    move.fifty_moves_reset = fifty_moves;//set values to before the move was made
    move.make_move(board, board_12x12);//make move on board
    }

}

void output_engine_move(Move move){//function to output engine's chosen move in algebraic notation
    cout << convert_to_notation(move.square_from);
    cout << convert_to_notation(move.square_to);
    string promote_to_letter;
    switch(get_type(move.promote_to)){//converts the type of piece engine wants to promote to to its notation
        case 4:
            promote_to_letter = "Q";
            break;
        case 3:
            promote_to_letter = "R";
            break;
        case 2:
            promote_to_letter = "B";
            break;
        case 1:
            promote_to_letter = "N";
            break;
        default:
            promote_to_letter = "";

    }
    if(move.type == promotion){
        cout << promote_to_letter;
    }
    cout << "\n";
    cout << "\n";
}


int main(){
 
    //first set up which colour is played by user/engine
    string user_colour;
    cout << "Which colour would you like to play?" << endl;
    cin >> user_colour;
    if(user_colour == "White" or user_colour == "white"){
        engine_plays_white = false;
    }
    else if(user_colour == "Black" or "black"){
        engine_plays_white = true;
    }
    else{
        cout << "Please enter colour in format (white) or (black) next time. " << endl;
        cout << "Engine will now play as white by default." << endl;
        engine_plays_white = true;
    }

    if(engine_plays_white == true){
        for(int i = 0; i < 500;i++){
            cout << "\n";
            cout << "\n";
            cout << "thinking..." << endl;
            get_legal(board, board_12x12);
            array <Move, 218> depth1_moves;//making a copy of legal_moves array so that the actual array 
            depth1_moves = legal_moves;//still contains only legal moves in the current position

            int move_chosen = choose_move();
            Move move = depth1_moves[move_chosen];

            output_engine_move(move);//outputs engine's move
            move.make_move(board, board_12x12);

            cout << "enter your move: " << endl;

            get_user_move();//gets and parses user's move
            cout << "\n";
            cout << "\n";
        }
    }
    else{
        for(int i = 0; i < 500;i++){//here we need to flip the order of get_user_move() and output_engine_move()
        cout << "enter your move: " << endl;
        get_user_move();//gets and parses user's move
        cout << "\n";
        cout << "\n";
        cout << "thinking..." << endl;

        get_legal(board, board_12x12);
        array <Move, 218> depth1_moves;//making a copy of legal_moves array so that the actual array 
        depth1_moves = legal_moves;//still contains only legal moves in the current position

        int move_chosen = choose_move();
        Move move = depth1_moves[move_chosen];

        output_engine_move(move);//outputs engine's move
        move.make_move(board, board_12x12);

        
        cout << "\n";
        cout << "\n";
    }
    }


    return 0;
}

