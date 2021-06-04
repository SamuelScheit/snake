#include "stdafx.h"
#include "Snake.h"
#include <mmsystem.h>
static int test = 0;
static int Board_Y = 22;
static int Board_X = 22;
static int Flag;
static int randomX;
static int randomY;
static int x;
static int y;
static volatile int GameOver;
static int Score;
static int Board[100][100];
static char input[2];
typedef struct SnakeTailType {
	int SnakeTailX;
	int SnakeTailY;
};
static SnakeTailType SnakeTail[4840];


// Function -->
static int Food(int Zahl = 2);
static void SaveMovement();
static void SnakeTailEndEditing();
// Functions <---

int GetBoardSizeX() {
	return Board_X;
}

int GetBoardSizeY() {
	return Board_Y;
}

int GetScore() {
	return Score;
}

int GetGameOver() {
	return GameOver;
}

int GetFlag() {
	return Flag;
}

int GetStatusBoard(int y, int x) {
	return Board[y][x];
}

void SetInput(char Value) {
	input[0] = Value;
}

int GetStatusSnakeTail() {

	switch (input[0]) {
	case 'a':
		if (SnakeTail[0].SnakeTailX == x - 1) {
			return 1;
		} else if (x == 0) {
			if (SnakeTail[0].SnakeTailX == Board_X - 1) {
				return 1;
			}
		}

		break;
	case 'd':
		if (SnakeTail[0].SnakeTailX == x + 1) {
			return 1;
		} else if (x == Board_X) {
			if (SnakeTail[0].SnakeTailX == 0) {
				return 1;
			}
		}
		break;
	case 'w':
		if (SnakeTail[0].SnakeTailY == y - 1) {
			return 1;
		} else if (y == 0) {
			if (SnakeTail[0].SnakeTailY == Board_Y - 1) {
				return 1;
			}
		}
		break;
	case 's':
		if (SnakeTail[0].SnakeTailY == y + 1) {
			return 1;
		} else if (y == Board_Y) {
			if (SnakeTail[0].SnakeTailY == 0) {
				return 1;
			}
		}
		break;
	default:
		break;
	}

	return 0;
}

void SetBoard(int y, int x, int value) {
	Board[y][x] = value;
}


int Food(int Zahl) {
	Flag = !Flag;

	if (Zahl == 2) {

		Score = Score + 1;
	}



	randomX = rand() % Board_X;
	randomY = rand() % Board_Y;


	//PlaySound((LPCWSTR)"C:\Users\samue\OneDrive - kreism\Dokumente\Andere\Programmieren\Visual Studio\workspace\workspace\Debug\test.wav",NULL, SND_ASYNC);

	Board[randomY][randomX] = Zahl;

	return 0;
}

void reset() {

	//board = (int*)malloc(Board_Y*Board_X);

	for (int y = 0; y < Board_Y; y++) {
		for (int x = 0; x < Board_X; x++) {
			Board[y][x] = 0;
			//board[y + x * Board_X];
		}
	}

	Flag = 0;
	x = 0;
	y = 0;
	Score = 1;
	Food();
	GameOver = 0;
	input[0] = 'd';
}

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

void SnakeTailEndEditing() {

	if (Board[SnakeTail[Score].SnakeTailY][SnakeTail[Score].SnakeTailX] != 2) {
		Board[SnakeTail[Score].SnakeTailY][SnakeTail[Score].SnakeTailX] = 0;
	}

}

void SetBoardSize(int BoardX, int BoardY) {
	test++;
	Board_X = BoardX;
	Board_Y = BoardY;
	x = 0;
	y = 0;
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++)
		{
			if (Board[y][x] > 0) {
				Board[y][x] = 0;
			}
		}
	}
	Food();
	Score = Score - 1;
}

int BoardEditing() {

	char tmpinput = input[0];

	int again = 1;

	if (tmpinput != 'x') {
		SaveMovement();
		SnakeTailEndEditing();
		if (GameOver == 1) {
			reset();
			again = 0;
		}
	}

	while (again == 1) {
		again = 0;
		switch (tmpinput) {
		case 'w':
			if (GetStatusSnakeTail() == 1) {
				tmpinput = 's';
				again = 1;
			}
			else {
				if (y == 0) {
					if (Board[Board_Y - 1][x] == 1) {
						GameOver = 1;
						break;
					}
					y = Board_Y - 1;
					if (Board[y][x] == 2) {
						Food();
					}
					Board[y][x] = 1;

				}
				else {
					if (Board[y - 1][x] == 1) {
						GameOver = 1;
					}
					else if (Board[y - 1][x] == 2) {
						Food();
					}
					Board[y -= 1][x] = 1;

				}
			}
			break;
		case 's':
			if (GetStatusSnakeTail() == 1) {
				tmpinput = 'w';
				again = 1;
			}
			else {
				if (y == Board_Y - 1) {
					if (Board[0][x] == 1) {
						GameOver = 1;
						break;
					}
					y = 0;
					if (Board[y][x] == 2) {
						Food();
					}
					Board[y][x] = 1;

				}
				else {
					if (Board[y + 1][x] == 1) {
						GameOver = 1;
					}
					else if (Board[y + 1][x] == 2) {
						Food();
					}
					Board[y += 1][x] = 1;
				}
			}
			break;
		case 'a':
			if (GetStatusSnakeTail() == 1) {
				tmpinput = 'd';
				again = 1;
			}
			else {
				if (x == 0) {
					if (Board[y][Board_X - 1] == 1) {
						GameOver = 1;
						break;
					}
					x = Board_X - 1;
					if (Board[y][x] == 2) {
						Food();
					}
					Board[y][x] = 1;

				}
				else {
					if (Board[y][x - 1] == 1) {
						GameOver = 1;
					}
					else if (Board[y][x - 1] == 2) {
						Food();
					}
					Board[y][x -= 1] = 1;
					break;
				}
			}
			break;
		case 'd':
			if (GetStatusSnakeTail() == 1) {
				tmpinput = 'a';
				again = 1;
			}
			else {
				if (x == Board_X - 1) {
					if (Board[y][0] == 1) {
						GameOver = 1;
						break;
					}
					x = 0;
					if (Board[y][x] == 2) {
						Food();
					}
					Board[y][x] = 1;

				}
				else {
					if (Board[y][x + 1] == 1) {
						GameOver = 1;
					}
					else if (Board[y][x + 1] == 2) {
						Food();
					}
					Board[y][x += 1] = 1;
				}
			}
			break;
		case 'q':
			GameOver = 1;
			break;
		default:
			break;
		}
	}

	return GameOver;
}