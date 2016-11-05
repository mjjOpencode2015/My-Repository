#include <stdio.h>
#include <windows.h>
#include <stdlib.h> 
#include <time.h>
#include "myH.h"
void Show();
void snake();
void initialization(Snake*);//初始化
char key();
void body(Snake* );
void run(Snake*);
int door(Snake*);
void food();
void eat(Snake*);
void add(Snake*);
void release_list(Snake*);
int main()
{
//	int i = 0;
	Snake* head = (Snake*)malloc(sizeof(Snake));
	initialization(head);
	while(1)
	{
		body(head);
		eat(head);
		Show();
		char k;
		k = key();
		if(k)
		{
			if((n == 'a' && k != 'd')||(n == 'd' && k != 'a')||(n == 'w' && k != 's')||(n == 's' && k != 'w'))
			{
				n = k;
			}
		}
		if(door(head)) {break;}
		run(head);
		Sleep(250);
		system("cls");/*清屏*/
	}
	system("cls");
	printf("Game over!\n得分：%d\n",scoring);
	release_list(head);
	return 0;
}
void Show()
{
	for(int i = 0; i < 24; i++)
		{
			printf("%s",z[i]);
		}
}
void initialization(Snake* head)
{
	head->x = 3; head->y = 46;
	Snake* tail = head;
	tail->body = (Snake*)malloc(sizeof(Snake));
	tail = tail->body;
	tail->x = 3; tail->y = 48;
	tail->body = (Snake*)malloc(sizeof(Snake));
	tail = tail->body;
	tail->x = 3; tail->y = 50;
	tail->body = NULL;
}
void body(Snake* head)
{
	Snake* vernier = head;
	char l[] = "●";
	for(int i = 1; i < 23; i++)
	{
		for(int j = 2; j < 52; j++)
		{
			z[i][j] = ' ';
		}
	}
	while(vernier != NULL)
	{
		if((vernier->x > 0 && vernier->x < 23) && (vernier->y > 1 && vernier->y < 52))
		{
			z[vernier->x][vernier->y] = l[0];
			z[vernier->x][vernier->y + 1] = l[1];
		}
		vernier = vernier->body;
	}
}
char key()
{
	if(GetAsyncKeyState('W'))
		return 'w';
	else if(GetAsyncKeyState('S'))
		return 's';
	else if(GetAsyncKeyState('A'))
		return 'a';
	else if(GetAsyncKeyState('D'))
		return 'd';
	else
		return 0;
}
void run(Snake* head)
{
	int x,y,x1,y1;
	Snake* vernier = head;
	x = vernier->x;
	y = vernier->y;
	switch(n)
	{
		case 'w': vernier->x = vernier->x - 1; break;
		case 's': vernier->x = vernier->x + 1; break;
		case 'a': vernier->y = vernier->y - 2; break;
		case 'd': vernier->y = vernier->y + 2; break;
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
}
int door(Snake* head)
{
	Snake* vernier = head->body;
	if(head->x < 1 || head->x > 22 || head->y < 2 || head->y > 51)
	{
		
		return 1;
	}
//	int i = 0;
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
void food()
{
	srand(time(NULL));
	x = 1 + rand() % 22;
	y = 2 + rand() % 50;
	if(y % 2 != 0)
	{
		y++;
	}
}
void eat(Snake* head)
{
	Snake* vernier = head;
	if(x == -1 || y == -1)
	{
		food();
	}
	char k[] = "★";
	z[x][y] = k[0];
	z[x][y+1] = k[1];
	if(head->x == x && head->y == y)
	{
		food();
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
	switch(n)
	{
		case 'w': vernier->body->x = vernier->x - 1; break;
		case 's': vernier->body->x = vernier->x + 1; break;
		case 'a': vernier->body->y = vernier->y - 2; break;
		case 'd': vernier->body->y = vernier->y + 2; break;
	}
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