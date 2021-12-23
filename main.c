#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h> 
#elif linux
#include <unistd.h> // Linux: Sleep() func
#endif
#pragma warning(disable : 4996) // Compiler warning lvl3 of khbit() func

enum direction_stages {
	LEFT = 1, DOWN, RIGHT, UP
};

#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 20


int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;

void setup() // generate the fruit within the boundary
{
	gameover = 0;
	x = height / 2; // Coord's of the fruit
	y = width / 2; // X , Y Axis
	
	while (fruitx == 0) {  
		fruitx = rand() % SCREEN_WIDTH;
	}

label:
	fruity = rand() % SCREEN_HEIGHT; // Another Option
	if (fruity == 0)
		goto label;

	score = 0;
}

void draw()
{

#ifdef _WIN32
	system("cls");
#elif __unix__
	clrscr();
#endif
 
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1) //  //Print the boundary
			{
				printf("#");
			}
			else {
				if (i == x && j == y) // While the x,y coords in the boundary
									//your're in the game, still print the snake
					printf("@");
				else if (i == fruitx && j == fruity)  // When the snake eats the fruit
					printf("*");
				else                               // present clean area of game
					printf(" ");
			}
		}
		printf("\n");
	}

	// Print the score after the
	// game ends
	printf("score = %d", score);
	printf("\n");
	printf("press X to quit the game");
}



void input()
{
	if (kbhit()) {
		switch (getch()) {
		case 'a':
			flag=LEFT;
			break;
		case 's':
			flag=DOWN;
			break;
		case 'd':
			flag=RIGHT;
			break;
		case 'w':
			flag=UP;
			break;
		case 'x':
			gameover = 1;
			break;
		}
	}
}


void logic()
{
	Sleep(0.1); // Snake movement
	switch (flag) {
	case 1:
		y--;
		break;
	case 2:
		x++;
		break;
	case 3:
		y++;
		break;
	case 4:
		x--;
		break;
	default:
		break;
	}

	// If the game is over
	if (x < 0 || x > height
		|| y < 0 || y > width)
		gameover = 1;

	// If snake reaches the fruit
	// then update the score
	if (x == fruitx && y == fruity) {
	label3:
		fruitx = rand() % SCREEN_WIDTH;
		if (fruitx == 0)
			goto label3;

		// After eating the above fruit
		// generate new fruit
	label4:
		fruity = rand() % SCREEN_HEIGHT;
		if (fruity == 0)
			goto label4;

		score += 10;
	}
}

void main()
{
	int m, n;

	// Generate boundary
	setup();

	// Until the game is over
	while (!gameover) {

		// Function Call
		draw();
		input();
		logic();
	}
}

