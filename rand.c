#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int n[27] = { 1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 };
	int i = 0;
	while (i != 1)
	{
		i = rand() % 2003;
	}
	while(1)
	{
		i = rand() % 26;
		if (n[i] != 0)
		{
			printf("%-2d,", n[i]);
			n[i] = 0;
		}
		int j;
		for (j = 0; j < 26; j++)
		{
			if (n[j] != 0)
			{
				break;
			}
		}
		if (j == 26)
		{
			break;
		}
	}
	getchar();
	return 0;
}
# My-Repository
创建于2016-7-21
