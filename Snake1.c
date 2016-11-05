#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
typedef struct _snake
{
     int x;
     int y;
     struct _snake* body;
} Snake;
const int W = 24;
const int H = 30;
HANDLE hOut; 
COORD pos= {0, 0}; 
CONSOLE_CURSOR_INFO cur_info = {1, 0};  //隐藏光标
void background();
void gameinfo(int , int , char *, int , int);
void refresh();
void food(Snake*);
void initialization(Snake*);//初始化
void body(Snake*);
void run(Snake*);
void getkeys();
void eat(Snake*);
void add(Snake*);
int door(Snake*);
void release_list(Snake*);
int foodx = 0;
int foody = 0;
int refreshn = 0;
char direction = 'a';
int scoring = 0;
int Endx;
int Endy;
int main()
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //标准输出句柄获得
	SetConsoleCursorInfo(hOut, &cur_info);  //隐藏光标
	while(1)
	{
		system("cls");/*清屏*/
		Snake* head = (Snake*)malloc(sizeof(Snake));
		initialization(head);
		background();
		while(1)
		{
			Sleep(500);
			refresh();
			getkeys();
			run(head);
			eat(head);
			if(door(head)) break;
			food(head);
		}
		release_list(head);
		SetConsoleCursorPosition(hOut, pos);
		SetConsoleTextAttribute(hOut, 0x07);
		system("cls");/*清屏*/
		printf("得分：%d\n空格重新开始\n",scoring);
		while(1)
		{
			int w = getch();
			if(w == ' ')
			{
				break;
			}
			else
			{
				continue;
			}
		}
	}
	return 0;
}
void background()
{
	for(int i = 0;i < W; i++)
	{
		for(int j = 0;j < H; j++)
		{
			if(i != 0 && j != 0 && i != W-1 && j != H-1)
				printf("  ");
			else
			printf("□");
		}
		printf("\n");
	}
}
void gameinfo(int x, int y, char *s, int n, int col)
{
	pos.X = x*2;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
	SetConsoleTextAttribute(hOut, col);
	if (n<0)
		printf("%s", s);
	else
		printf("%s%d", s, n);
}
void refresh()
{
	int i = 0,j = 2;
	if(refreshn >= 500)
	{
		for(i = 1;i < (W - 1); i++)
		{
			for(j = 1;j < (H - 2); j++)
			{
				if((i == foodx && j == foody) || (i == foodx && j == (foody + 1)))
					continue;
				gameinfo(j, i, "  ", -1, 0x07);
			}
		}
		refreshn = 0;
	}
	else
	{
		refreshn++;
	}
}
void food(Snake* head)
{
	int kk;
	Snake* vernier = head;
	if(foodx == 0||foody == 0)
	{
		do
		{
			kk = 0;
			srand(time(NULL));
			foodx = 1 + rand() % 22;
			foody = 2 + rand() % 26;
			if(foody % 2 != 0)
			{
				foody++;
			}
			while(vernier != NULL)
			{
				if(foodx == vernier->x && foody == vernier->y)
				{
					kk = 1;break;
				}
				vernier = vernier->body;
			}
		}while (kk == 1);
	}
	gameinfo(foody, foodx, "★", -1, 0x0e);
}
void initialization(Snake* head)
{
	direction = 'a';
	foodx = 0;
	foody = 0;
	refreshn = 0;
	head->x = 3; head->y = 26;
	Snake* tail = head;
	tail->body = (Snake*)malloc(sizeof(Snake));
	tail = tail->body;
	tail->x = 3; tail->y = 27;
	tail->body = (Snake*)malloc(sizeof(Snake));
	tail = tail->body;
	tail->x = 3; tail->y = 28;
	tail->body = NULL;
}
void body(Snake* head)
{
	Snake* vernier = head;
	while(vernier != NULL)
	{
		if((vernier->x > 0 && vernier->x < 23) && (vernier->y > 0 && vernier->y < 29))
		{
			gameinfo(vernier->y, vernier->x, "●", -1, 0x04);
		}
		vernier = vernier->body;
	}
}
void run(Snake* head)
{
	Snake* vernier = head;
	while(vernier->body != NULL)
	{
		vernier = vernier->body;
	}
	Endx = vernier->x;
	Endy = vernier->y;
	gameinfo(vernier->y, vernier->x, "  ", -1, 0x01);
	int x,y,x1,y1;
	vernier = head;
	x = vernier->x;
	y = vernier->y;
	switch(direction)
	{
		case 'w': vernier->x = vernier->x - 1; break;
		case 's': vernier->x = vernier->x + 1; break;
		case 'a': vernier->y = vernier->y - 1; break;
		case 'd': vernier->y = vernier->y + 1; break;
	}
	x1 = x;
	y1 = y;
	vernier = vernier->body;
	while(vernier != NULL)
	{
		x = vernier->x;
		y = vernier->y;
		vernier->x = x1;
		vernier->y = y1;
		x1 = x;
		y1 = y;
		vernier = vernier->body;
	}
	body(head);
}
void getkeys()  //获取方向键 
{
	char ch;
	if (kbhit())
	{
		ch = getch();
		if((ch == 'a' && direction != 'd')||(ch == 'd' && direction != 'a')||(ch == 'w' && direction != 's')||(ch == 's' && direction != 'w'))
		{
			switch (ch)
			{
				case 'a': direction = ch;break;
				case 'd': direction = ch;break;
				case 'w': direction = ch;break;
				case 's': direction = ch;break;
			}
		}
		if(ch == ' ')
		{
			getch();
		}
	}
}
void eat(Snake* head)
{
	Snake* vernier = head;
	if(foodx == 0 || foody == 0)
	{
		food(head);
	}
	if(head->x == foodx && head->y == foody)
	{
		foodx = 0;
		foody = 0;
		food(head);
		scoring++;
		add(head);
	}
}
void add(Snake* head)
{
	Snake* vernier = head;
	while(vernier->body != NULL)
	{
		vernier = vernier->body;
	}
	vernier->body = (Snake*)malloc(sizeof(Snake));
	vernier->body->body = NULL;
	vernier->body->x = Endx;
	vernier->body->y = Endy;
	body(head);
}
int door(Snake* head)
{
	Snake* vernier = head->body;
	if(head->x < 1 || head->x > 22 || head->y < 2 || head->y > 29)
	{
		
		return 1;
	}
	while(vernier != NULL)
	{
		if(head->x == vernier->x && head->y == vernier->y)
		{
			return 1;
		}
		vernier = vernier->body;
	}
	return 0;
}
void release_list(Snake* head)
{
	Snake* vernier = head;
	while(vernier != NULL)
	{
		vernier = head->body;
		free(head);
		head = vernier;
	}
	return;
}