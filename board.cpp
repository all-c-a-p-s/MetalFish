#include <iostream>
#include <string>

using namespace std;


int board[64] = {    3, 1, 2, 4, 5, 2, 1, 3,//all white pieces integer divide by 6 to 0, 
                     0, 0, 0, 0, 0, 0, 0, 0,//all black pieces integer divide by 6 to 4,
                    -6,-6,-6,-6,-6,-6,-6,-6,// empty squares integer divide by 6 to -1,  
                    -6,-6,-6,-6,-6,-6,-6,-6,//black pieces have been given these numbers so that product of white * black will always
                    -6,-6,-6,-6,-6,-6,-6,-6,//be between 24 and 145, and no other possible products give this range 
                    -6,-6,-6,-6,-6,-6,-6,-6,//white pawns will be counted as 1 not 0 in this calculation
                    24,24,24,24,24,24,24,24,//en passant square represented by 30
                    27,25,26,28,29,26,25,27};

int board_12x12[144] = {      -12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,//used for sliders and knights so that they don't 'teleport' 
                              -12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,//-12 integer divides by 6 to -2
                              -12,-12, 3,  1,  2,  4,  5,  2,  1,  3, -12,-12,
                              -12,-12, 0,  0,  0,  0,  0,  0,  0,  0, -12,-12,
                              -12,-12,-6, -6, -6, -6, -6, -6, -6, -6, -12,-12, 
                              -12,-12,-6, -6, -6, -6, -6, -6, -6, -6, -12,-12,
                              -12,-12,-6, -6, -6, -6, -6, -6, -6, -6, -12,-12,
                              -12,-12,-6, -6, -6, -6, -6, -6, -6, -6, -12,-12,
                              -12,-12,24, 24, 24, 24, 24, 24, 24, 24, -12,-12,
                              -12,-12,27, 25, 26, 28, 29, 26, 25, 27, -12,-12,
                              -12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,
                              -12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12};

int get_rank(int x){
    int rank;
    rank = (x + 8)/8;
    return rank;
}


int get_12x12(int x){

    return 22 + 4 * (get_rank(x)) + 8 * (get_rank(x)) - (8 - x % 8);//add one extra row, then remove unnecessary squares

}

int get_12x12_rank(int x){

    int rank;
    rank = (x + 12)/12;
    return rank;

}

int get_8x8(int x){

return (8 * ((get_12x12_rank(x) - 2) - 1)) + ((x % 12) - 2);

}

int white_to_move(int x){   

    return x % 2;
}

bool isenemy(int x, int y){
    if(x == 0){
        x = 1;//otherwise (white pawn * empty) gives same result as (white pawn * enemy)
    }

    if(y == 0){
        y = 1;//as above
    }

    if(x == 5 and y == 5){
        x = 4;//otherwise two white kings will be 'enemies'
    }

    bool is_enemy = false;
    if(23 < (x * y) and (x * y) < 151){//en passant also counts as enemy

        is_enemy = true;
        
    } 

    return is_enemy;
}

bool iswhite(int x){

    bool is_white = false;
    int foo;
    foo = x/6;
    if(foo == 1){
        is_white = true;
    }
    return is_white;
}

bool isblack(int x){

    bool is_black = false;
    int foo;
    foo = x/6;
    if(foo == 4){
        is_black = true;
    }
    return is_black;
}

int get_type(int x){
    return x % 6;
}

int get_colour(int x){
    int foo;
    foo = x / 6; 
    return foo;
}

int fifty_moves = 0;
int tempi = 0;