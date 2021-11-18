#include "geesespotter_lib.h"
#include <iostream> 
//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11

char * createBoard(std::size_t xdim, std::size_t ydim); //good
void hideBoard(char * board, std::size_t xdim, std::size_t ydim);//good
void cleanBoard(char * board);//good
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);//good 
void printBoard(char * board, std::size_t xdim, std::size_t ydim);//good 

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim);
void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim);//good 


char *createBoard(std::size_t xdim, std::size_t ydim) { //passed marmoset 
    std::size_t total = xdim*ydim; 
    char *arr{new char[total]{} }; 
    for(int i = 0; i < total; i++) {
        arr[i] = 0; 
    }

    return arr; 
}
void hideBoard(char *board, std::size_t xdim, std::size_t ydim) { //passed marmoset 
    for(int x = 0; x < ydim*xdim; x++) {
        board[x] = board[x] & 0x0F; 
        board[x] = hiddenBit(); 
    }

}
void cleanBoard(char *board) { //passed marmoset 
    delete[] board; 
    board = nullptr; 

}
void printBoard(char *board, std::size_t xdim, std::size_t ydim) { //works marmoset 
    std::size_t row, col; 
    for(row = 0; row < ydim; row++) {
        for(col = 0; col < xdim; col++) {
            std::size_t x = row * xdim + col; 
            if((board[x] & markedBit()) == 0x10) {
                    std::cout << "M";
                }
                else if((board[x] & hiddenBit()) == 32) {
                    std::cout << "*"; 
                } 
                else {
                    std::cout << (int(board[x]));
                }   
        }
    std::cout << std::endl;   
      }

}
int mark (char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,std::size_t yloc) { //works on marmoset 
    std::size_t value = yloc*xdim+xloc;
    if((board[value] & markedBit()) == 0x10) {
        board[value] = (board[value] & ~markedBit()); 
        return 2; 
        //unmarks something that is marked  
    }
    else if((board[value] & hiddenBit()) == 0x20) { //so this works for marmoset 
       board[value] = (board[value] | markedBit()); 
        return 0; 
    }

    return 0;
}
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) { //passed marmoset 

    for(int index = 0; index < (xdim * ydim); index++){
        int row = index / xdim;
        int col = index % xdim;
        int num_geese_neightbours = 0;
        char curr_board_value;

        if(board[index] != 9) {

            for(int i = row -1; i <= row+1; i++){
                for(int j = col -1; j <= col + 1; j ++){
                    if(i > -1 && i < ydim && j > -1 && j < xdim){
                        curr_board_value = board[i * xdim + j];
                        if(curr_board_value == 9){
                            num_geese_neightbours++;
                        }

                    }
                }
            }
            
            board[row * xdim + col] = num_geese_neightbours;

        }
    }

}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,std::size_t yloc) {
    std::size_t value = yloc*xdim+xloc;
     if((board[value] & markedBit()) == 0x10) {//pretty sure this works 
        return 1; 
    }
    else if((board[value] & hiddenBit()) == 0) {
        return 2; 
    }
    else if((board[value] & valueMask()) == 9) {
        board[value] &=~hiddenBit(); 
        return 9; 
    }
    else  {
        if((board[value] & valueMask()) == 0) {
            int row = value / xdim;
            int col = value % xdim;
            char curr_board_value;
            for(int i = row -1; i <= row+1; i++){
                for(int j = col -1; j <= col + 1; j ++){
                    if(i > -1 && i < ydim && j > -1 && j < xdim){
                        curr_board_value = board[i * xdim + j];
                        board[i * xdim + j] = board[i * xdim + j] &=~hiddenBit();

                    }
                }
            }   
        }

        //     if(board[value-1] > 0 || board[value-1] > xdim*ydim) {
        //         board[value -1] = board[value -1 ] &=~hiddenBit();  
        //         board[value+1] = board[value +1 ] &=~hiddenBit(); 
        //     }
        //     if(board[yloc-1] > 0 || board[yloc-1] > xdim*ydim) {
        //         board[(yloc-1) * (xloc)] =  board[(yloc-1) * (xloc)] &=~hiddenBit();
        //         board[(yloc+1) * (xloc)] =  board[(yloc+1) * (xloc)] &=~hiddenBit();
        //     }
        //     if(board[yloc-1] > 0 || board[yloc-1] > xdim*ydim) {
        //         board[(yloc-1) * (xloc-1)] =  board[(yloc-1) * (xloc-1)] &=~hiddenBit();
        //         board[(yloc+1) * (xloc+1)] =  board[(yloc+1) * (xloc+1)] &=~hiddenBit();
        //     }

        // }
        board[value] &=~hiddenBit(); 
        return 0; 
        }
        

return 0; 
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) { //passed marmoset 
    int count{};
    int result = xdim*ydim; 
    for(int i = 0; i < xdim*ydim; i++){
        if((board[i] & hiddenBit()) == 0) {
            count = count+1; 
        }
        if((board[i] & valueMask()) == 9 && (board[i] & hiddenBit()) == 32) {
            count = count+1; 
        }
        else if((board[i] & hiddenBit()) == 32) {
            return false; 
        }
        
    }
    if(count != result) {
        return false; 
    }
    else if(count == result) {
        return true;
    }
    return false; 

}
