#ifndef _SNAKE_H_
#define _SNAKE_H_

//DEFINE --->
//DEFINE <---

//global Var --->
//global Var <---

//Function --->

int GetStatusBoard(int y, int x);
int GetBoardSizeX();
int GetBoardSizeY();
int GetScore();
int GetGameOver();
int GetFlag();
int BoardEditing();
int GetStatusSnakeTail();
void SetBoardSize(int BoardX, int BoardY);
void SetInput(char Value);
void reset();
void SetBoard(int y, int x, int value);

#endif