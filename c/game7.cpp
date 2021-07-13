#define _CRT_SECURE_NO_WARNINGS 1

#define WIDTH 10
#define HEIGHT 10

#include <stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<MMSystem.h>
#pragma comment(lib,"Winmm.lib")

int MAP[10][10] =
{
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 3, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 4, 1, 1, 1, 1, 0 },
	{ 1, 3, 0, 4, 2, 4, 0, 3, 1, 0 },
	{ 1, 1, 1, 1, 4, 1, 1, 1, 1, 0 },
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 3, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 }
};


//打印地图
void PrintMap()
{
	//清屏
	system("cls");

	/*推箱子*/
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (MAP[i][j])
			{
			case 0://空地
				printf("  ");
				break;
			case 1://墙
				printf("■");
				break;
			case 2://人
				printf("♀");
				break;
			case 3://目的地
				printf("☆");
				break;
			case 4://箱子
				printf("□");
				break;
			case 5://箱子和目的地重合
				printf("★");
				break;
			case 6://人站在目的地
				printf("♀");
				break;
			}
		}
		printf("\n");
	}
}

typedef struct s {
	int x;
	int y;
}S;

S person, up, down, left, right;

//设置地图
void start(int MAP[10][10]) {
	left.x = 3;
	left.y = 4;
	right.x = 5;
	right.y = 4;
	up.x = 4;
	up.y = 3;
	down.x = 4;
	down.y = 5;
	person.x = 4;
	person.y = 4;
}

void move(char input) {
	if (input == 'w' && person.x > 2 && person.y == 4) {
		if (person.x == left.x + 1) {
			MAP[left.x][left.y] = 0;
			left.x--;
			MAP[left.x][left.y] = 4;
		}
		if (left.x == 1) {
			MAP[left.x][left.y] = 5;
		}
		MAP[person.x][person.y] = 0;
		person.x--;
		MAP[person.x][person.y] = 6;
	}
	if (input == 's' && person.x < 7 && person.y == 4) {
		if (person.x == right.x - 1) {
			MAP[right.x][right.y] = 0;
			right.x++;
			MAP[right.x][right.y] = 4;
		}
		if (right.x == 8) {
			MAP[right.x][right.y] = 5;
		}
		MAP[person.x][person.y] = 0;
		person.x++;
		MAP[person.x][person.y] = 6;

	}
	if (input == 'a' && person.y > 2 && person.x == 4) {
		if (person.y == up.y + 1) {
			MAP[up.x][up.y] = 0;
			up.y--;
			MAP[up.x][up.y] = 4;
		}
		if (up.y == 1) {
			MAP[up.x][up.y] = 5;
		}
		MAP[person.x][person.y] = 0;
		person.y--;
		MAP[person.x][person.y] = 6;
	}
	if (input == 'd' && person.y < 6 && person.x == 4) {
		if (person.y == down.y - 1) {
			MAP[down.x][down.y] = 0;
			down.y++;
			MAP[down.x][down.y] = 4;
		}
		if (down.y == 7) {
			MAP[down.x][down.y] = 5;
		}
		{
			MAP[person.x][person.y] = 0;
			person.y++;
			MAP[person.x][person.y] = 6;
		}
	}
}

int ifbreak() {
	for (int i = 1; i < 8; i++) {
		for (int j = 1; j < 8; j++) {
			if (MAP[i][j] == 4) {
				return 0;
			}
		}
	}
	return 1;
}

/*void main() {
	start(MAP);
	PrintMap();
	char input = 0;

	while (input != 'q') {
		if (_kbhit()) {
			input = _getch();
			move(input);
			//moveleft(input);
			PrintMap();
			if (ifbreak()) {
				//system("cls");
				printf("你赢啦！");
				break;
			}
		}
	}
}*/