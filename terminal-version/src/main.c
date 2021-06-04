//
//  main.c
//  Game
//
//  Created by Samuel on 29.07.16.
//  Copyright © 2016 Samuel. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define Board_X 12
#define Board_Y 12

//global Var
int randomX;
int randomY;
int Finish = 10;
_Bool Over = 0;
int Round = 0;
int Score = 0;
int Turn = 0;
int Board[Board_Y][Board_X];
//Snake
struct SnakeTail {
    
    int SnakeTailX;
    int SnakeTailY;
    
}SnakeTail[Board_X * Board_Y];
//Snake end
char input[64];
//x & y Cordinate from Board[8][8]
int x = 0;
int y = 0;
//x & y Cordinate from Board[8][8] end
//random X & Y Cordinate from second Number

//random X & Y Cordinate from second Number end
//global Var end

//Functions

void Informations() {
    
    float Version = 1.3;
    char Autor[] = {"Samuel"} ;
    char GameName[] = {"Snake"};
    //Autor Infos
    printf("-----------------Game-%s Version %0.1-----------------\nCopyright � 2016 %s. All rights reserved.\nScore = %i | Turn =  %i | Round = %i | Finish = %i\n", GameName,Version,Autor,Score,Turn,Round,Finish);
    // Moving
    printf("| w - up | s - down | a - left | d - right | touching tail of snake - Game Over |\n");
    
    return;
}

void BoardOutput() {
    
    int j = 0;
    int i = 0;
    for (; i < 100; i++) {
        printf("\n");
    }
    
    Informations();
    
    for (int i = 0; i < Board_Y; i++) {
        
        for (j = 0; j < Board_X; j++) {
            
            printf("%i ", Board[i][j]);
        }
        
        printf("\n");
        
    }
    
}

void SnakeTailEndEditing() {
    
    Board[SnakeTail[Score].SnakeTailY][SnakeTail[Score].SnakeTailX] = 0;
    BoardOutput();
    
}

// The coordinates of the snakehead are stored chronologically to SnakeTail board_Y * Board_Y(because the Board is board_Y * Board_Y large)
void SaveMovement() {
    
    for (int i = (Board_Y * Board_X) - 1; i > 0; i--) {
        
        if (i < 0) {
            break;
        }
        
        SnakeTail[i].SnakeTailX = SnakeTail[i - 1].SnakeTailX;
        SnakeTail[i].SnakeTailY = SnakeTail[i - 1].SnakeTailY;
        
    }
    
    SnakeTail[0].SnakeTailX = x;
    SnakeTail[0].SnakeTailY = y;
    
}

int Food(int Initialization) {
    
    if (Initialization == 1) {
        
        srand ( (unsigned) time(NULL) );
        do {
            randomX = rand() % Board_X;
            randomY = rand() % Board_Y;
        } while (randomY == y && randomX == x);
        
        Board[randomY][randomX] = 1;

    }
    else {
        
        srand ( (unsigned) time(NULL) );
        
        if (x == randomX && y == randomY) {
            
            Score = Score + 1;
            
            do {
                randomX = rand() % Board_X;
                randomY = rand() % Board_Y;
            } while (randomY == y && randomX == x);
            
        }
        
        Board[randomY][randomX] = 1;
        BoardOutput();
        
    }
    
    return 0;
}


void Input() {
    
    do {
        
        input[0] = getchar();
        BoardOutput();
    } while (input[0] != 'w' && input[0] != 'a' && input[0] != 's' && input[0] != 'd');
    
    Turn = Turn + 1;
    SaveMovement();
    
}

int BoardEditing() {
    
    SnakeTailEndEditing();
    
    if (y == 0 && input[0] == 'w') {
        
        y = Board_Y - 1;
        Board[y][x] = 5;
        input[0] = x;

    }else if (y == 0 && input[0] == 'w' && Board[Board_Y - 1][x] == 5) {
        
        Over = 1;
        
    }
    
    if (y == Board_Y - 1 && input[0] == 's') {
        
        y = 0;
        Board[y][x] = 5;
        input[0] = x;

    }else if (y == Board_Y - 1 && input[0] == 's' && Board[0][x] == 5) {
        
        Over = 1;
        
    }
    
    if (x == Board_X - 1 && input[0] == 'd') {
        
        x = 0;
        Board[y][x] = 5;
        input[0] = x;

    }else if (x == Board_X - 1 && input[0] == 'd' && Board[y][0] == 5) {
        
        Over = 1;
        
    }
    
    if (x == 0 && input[0] == 'a') {
        
        x = Board_X - 1;
        Board[y][x] = 5;
        input[0] = x;

    }else if (x == 0 && input[0] == 'a' && Board[y][Board_X - 1] == 5) {
        
        Over = 1;
        
    }
    
    switch (input[0]) {
        case 'w':
            if (Board[y - 1][x] == 5) {
                Over = 1;
            }
            Board[y -= 1][x] = 5;
            break;
        case 'a':
            if (Board[y][x - 1] == 5) {
                Over = 1;
            }
            Board[y][x -= 1] = 5;
             break;
        case 's':
            if (Board[y + 1][x] == 5) {
                Over = 1;
            }
            Board[y += 1][x] = 5;
            break;
        case 'd':
            if (Board[y][x + 1] == 5) {
                Over = 1;
            }
            Board[y][x += 1] = 5;
            break;
        default:
            break;
    }
    
    Food(0);
    BoardOutput();
    
    return Over;
}

void BoardInitialization() {
    
    //SnakeTail's
    for (int i = 0; i < (Board_Y * Board_X) - 1; i++) {
        
        SnakeTail[i].SnakeTailX = 0;
        SnakeTail[i].SnakeTailY = 0;
        
    }
    //SnakeTail's end
    //Set fields from board to 0
    int j = 0;
    for (int i = 0; i <= Board_Y - 1; i++) {
        
        for (j = 0; j <= Board_X - 1; j++) {
            
            Board[i][j] = 0;
            
        }
        
        Board[i][j] = 0;
        
    }
     //Set fields from board to 0 end
    
    //Random Number
    Food(1);
    //Random Number end
    
    //Board SnakeHead
    Board[0][0] = 5;
    //Board SnakeHead end
    
    return;
}

int EndScreen(_Bool WinOrLose) {
    if (WinOrLose == 1) {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nGeschafft\n\n1)zum Weitermachen eine beliebige Taste drücken\n2)Zum Neustarten die 2 drücken\n");
    }else if (WinOrLose == 0) {
        
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nGame Over\n\n");
        
    }
    return getchar();
}

void Restart() {
    
    Round++;
    x = 0;
    y = 0;
    Over = 0;
    Finish = 10;
    Score = 0;
    Turn = 0;
    randomX = 0;
    randomY = 0;
    
    for (int j = 0; j <= Board_Y - 1; j++) {
        
        for (int i = 0; i <= Board_X - 1; i++) {
            
            Board[j][i] = 0;
            
        }
        
    }
    
    Board[0][0] = 5;
    Food(1);
    BoardOutput();
    Input();
    
}

int EndscreenTest() {
    int ContinueOrStop;
    if (Score == Finish) {
        
        ContinueOrStop = EndScreen(1);
        Finish = Finish + (int)((Board_X + Board_Y) / 2);
        
    }
    
    return ContinueOrStop;
}


//Funktionen end

//main
int main(int argc, const char * argv[]) {

    BoardInitialization();
    BoardOutput();
    Input();
Restart:
    while (1) {
        if (BoardEditing() == 1) {
            
            EndScreen(0);
            break;
            
        }
        if (EndscreenTest() == '2') {
            
            break;
            
        }
        BoardOutput();
        Input();
    }
    
    Restart();
    goto Restart;
    
    return 0;
}
//main End
