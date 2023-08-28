#include <iostream>
#include <string>
#include <array>
#include "search.cpp"
#include <chrono>//used for testing

using namespace std;
using namespace chrono;

/**
 * This file is the only file containing main(), so it is the only one that can be run. It calls functions
 * from other files and handles input/output. * 
*/

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
        move.make_move(board, board_10x12);//make move on board
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
    move.make_move(board, board_10x12);//make move on board
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

    if(engine_plays_white == true){
        for(int i = 0; i < 500;i++){
            cout << "\n";
            cout << "\n";
            cout << "thinking..." << endl;

            auto start = high_resolution_clock::now();
            int move_chosen = choose_move();

            get_legal(board, board_10x12);
            Move move = legal_moves[move_chosen];

            output_engine_move(move);//outputs engine's move
            move.make_move(board, board_10x12);

            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<seconds>(stop - start);

            cout << "time: "<< duration.count() << "s" <<  "\n";

            cout << "Enter your move: " << endl;

            get_user_move();//gets and parses user's move
            cout << "\n";
            cout << "\n";
        }
    }
    else{
        for(int i = 0; i < 500;i++){//here we need to flip the order of get_user_move() and output_engine_move()
            cout << "Enter your move: " << endl;
            get_user_move();//gets and parses user's move
            cout << "\n";
            cout << "\n";
            cout << "thinking..." << endl;

            auto start = high_resolution_clock::now();

            int move_chosen = choose_move();

            get_legal(board, board_10x12);
            Move move = legal_moves[move_chosen];

            output_engine_move(move);//outputs engine's move
            move.make_move(board, board_10x12);

            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<seconds>(stop - start);

            cout << "time: "<< duration.count() << "s" <<  "\n";

            cout << "\n";
            cout << "\n";
        }
    }

    return 0;
}

