#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include "makemove.cpp"

using namespace std;

string convert_to_notation(int square){

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

int convert_to_num(string notation){

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

int main(){



    srand((unsigned) time(NULL));

    
    int move_chosen;
    int last_used_move;
    
    for(int i = 0;i < 500;i++){
        get_all_moves(white_kingside_castling, white_queenside_castling, black_kingside_castling, black_queenside_castling);
        if(legal_moves[0][0] == -1){//check for checkmate or stalemate to end the game
            break;
        }
        last_used_move = 0;

        for(int i = 0;i < 218;i++){
            
            if(legal_moves[i][0] == -1){
                last_used_move = i - 1;
                break;
            }
        }
   
        move_chosen =  0 + (rand() % last_used_move);
        cout << convert_to_notation(legal_moves[move_chosen][0]) << endl;
        cout << convert_to_notation(legal_moves[move_chosen][1]) << endl;
        cout << tempi << endl;
        
    
        

        make_move(legal_moves[move_chosen][0], legal_moves[move_chosen][1]);
        sleep(5);

        
    }   
    
    return 0;
}

