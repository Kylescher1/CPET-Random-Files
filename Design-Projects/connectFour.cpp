#include <iostream>
#include <iomanip>
#include <vector>

bool userInput(int userTurn, int board[][7], int *R, int *C){ // User Input function
    int userClm;//Selected user column
    
    do{
        std::cout << "Player #" << userTurn <<"'s Turn ("; 
        if(userTurn == 1){
            std::cout << "X";
        }
        else{
            std::cout <<  "O";
        } 
        std::cout << ")  :  Enter Your Move  :";

        std::cin >> userClm;
        if(userClm > 0 && userClm <= 7){
            for(int i = 0; i < 7; i++){
                if(board[i][userClm - 1] == 0 ){
                    *R = i;
                    *C = userClm - 1;
                    return true;
                }
            }
        }
        else{
            std::cout << " \n\n Invalid move please try again \n" << std::endl;
            continue;
        }
    }while(userClm);
}

bool winFunc(int board[][7], bool win){ // Win Check
    int count = 0;
    int curP; // Current Piece

    //Horizontal Win Check
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){ 
            if(board[i][j] != 0){
                count += 1;
                for(int k = 1; k < 5; k++){
                    curP = board[i][j];
                    if(board[i][j + k] == curP){
                        count += 1;
                        if(count == 4){
                            return true;
                        }
                    }
                    else {
                        count = 0;
                        break;
                    }
                }
            }
            else{
                count = 0;
            }
        }
    }

    //Vertial Win Check
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){ 
            if(board[i][j] != 0){
                count += 1;
                for(int k = 1; k < 5; k++){
                    curP = board[i][j];
                    if(board[j + k][i] == curP){
                        count += 1;
                        if(count == 4){
                            return true;
                        }
                    }
                    else {
                        count = 0;
                        break;
                    }
                }
            }
            else{
                count = 0;
            }
        }
    }

    //Diagonal Win Check
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){ 
            if(board[i][j] != 0){
                count += 1;
                for(int k = 1; k < 4; k++){
                    curP = board[i][j];
                    if(board[i + k][k + j] == curP){
                        count += 1;
                        if(count == 4){
                            return true;
                        }
                    }
                    else {
                        count = 0;
                        break;
                    }
                }
            }
            else{
                count = 0;
            }
        }
    }
    return(win);
}

int startFunc(int userTurn){
    userTurn = std::rand() %  2;
    std::cout << "         Welcome to Connect4!" << std::endl << "The goal is to have 4 X's or O's in a row!" << std::endl;
    std::cout << "   Player: " << userTurn << " was selected to go first " << std::endl;
    std::cout << "\n\n     Please enter your first move: \n";

    return (userTurn);
}

int displayFunc(int board[][7]){
    std::cout <<"\n\n\n\n-----------------------------" << std::endl;
    std::cout << "  1   2   3   4   5   6   7 " << std::endl;
    std::cout <<"-----------------------------" << std::endl;
    for(int i = 5; i >= 0; i--){
        for(int j = 0; j < 6; j ++){
            std::cout <<"| "; 
            if(board[i][j] == 1){
                std::cout << "X";
            }
            else if (board[i][j] == 2){
                std::cout << "O";                                        
            }
            else {
                std::cout << " ";
            }
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout <<"-----------------------------" << std::endl;
}

int main(){
    int board[6][7];
    int userClm = 0;
    int userTurn = 1;
    int C,R;
    bool validMove = true;
    bool winCheck = false;
    int playerWin, user1W = 0, user2W = 0;
    std::string nextGame;
    
    while(nextGame != "N"){
        userTurn = startFunc(userTurn);
    
        
        for(int i = 0; i < 6; i++){ //Clears Board
            for(int j = 0; j < 7; j ++){
                board[i][j] = 0;
            }
        }
    
        while(!winCheck){

            if(userTurn == 1){ //This if else branch modifys the board based on the user input
                validMove = userInput(userTurn, board, &R, &C);
                if(validMove == true){
                    board[R][C] = 1;
                    userTurn = 2;
                    R = 0;
                    C = 0;
                    winCheck = winFunc(board, winCheck);
                    playerWin = 1;
                    if(winCheck){
                        user1W =+ 1;
                        break;
                    }
                    else{
                        displayFunc(board);
                    }
                }
            }
            else if(userTurn == 2){
                validMove = userInput(userTurn, board, &R, &C);
                if(validMove == true){
                    board[R][C] = 2;
                    userTurn = 1;
                    R = 0;
                    C = 0;
                    winCheck = winFunc(board, winCheck);
                    playerWin = 2;
                    if(winCheck){
                        user2W =+ 1;
                        break;
                    }
                    else{ 
                        displayFunc(board);
                    }
                
                }
            }
        }

        displayFunc(board);
        std::cout <<"-----------------------------" << std::endl;
        std::cout << "Player #" << playerWin << " has won! \n";
        std::cout << "Statistics: \n";
        std::cout <<"Player #1 Wins :" << user1W;
        std::cout <<"\nPlayer #2 Wins :" << user2W;
        std::cout <<"\n-----------------------------" << std::endl;
        std::cout <<"If you would to continue please enter , to quit enter N  [Y/N]:";
        std::cin >> nextGame;

        if(nextGame == "N"){
            break;
        }
        else{
            std::cout << "\n\n\n\n";
            winCheck = false;
            continue;
        }
        
    }

    return (0);
}