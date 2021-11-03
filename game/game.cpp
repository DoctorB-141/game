#define SETBIT(X,Y)     X|=(1ULL<<(Y))
#define UNSETBIT(X,Y)   X&=(~(1ULL<<(Y)))
#define ARRAYSIZE(X) sizeof(x) / sizeof(x[0])
#include<iostream>
#include<random>
#include<chrono>

#include<termios.h>
#include<unistd.h>
#include"conio.h"
int score = 0;
int lines[8];
int alive = 1;
int tim = time(NULL);
char iseven(int in)
{
	if(in % 2 == 0)
	{
		return '~';
	}
	else
	{
		return '*';
	}
}
int * renderline(int out)
{
	static int line[8];
	int count = 0;
	for(int i = 0; i < 8; i++)
	{
		std::cout << iseven(out);
		if(iseven(out) == '*')
		{
			line[count] = 1;
			count++;
		}
		out = out >> 1;
	}
	std::cout << '\n';	
	return line;
}
void renderscreen(int lines[8], int poffset)
{
	for(int i = 0; i < 8; i++)
	{
		renderline(lines[i]);
	}
	for(int x = 0; x < poffset; x++)
	{
		std::cout << " ";
	}
	std::cout << "^\n";
	std::cout << score << '\n';
}
void shootline(int y, int lines[8])
{
	if(tim != time(NULL))
	{
		int temp;
		for(int i = 7; i >= 0; i--)
		{
			temp = lines[i];
			UNSETBIT(lines[i], y);
			if(temp != (temp & lines[i]))
			{
				break;
			}
			tim = time(NULL);
	}
	}
}
void newline(int num)
{	
	if(lines[7] != 0)
	{
		alive = 0;
	}

	for(int i = 7; i > 0; i--)
	{
		lines[i] = lines[i - 1];
	}
	lines[0] = num;
	score++;
}
void newline(void)
{
	if(lines[7] != 0)
	{
		alive = 0;
	}
	for(int i = 7; i > 0; i--)
	{
		lines[i] = lines[i - 1];
	}
	lines[0] = rand() % 256;
	score++;
}
int main()
{
	srand(time(NULL));
	char input;
	int offset = 0;
	int past;
	const char* cmd = "clear";
	int check = 0;
	renderscreen(lines, 0);
	while(alive == 1)
	{
		if(time(NULL) % 2 == 0)
		{
			if(check == 1)
			{
				check = 0;
				if(score <= 50)
				{
					if(time(NULL) % 4 == 0)
					{
						newline(0);
						system(cmd);
						renderscreen(lines, offset);
					}
					else
					{
						newline();
						system(cmd);
						renderscreen(lines, offset);
					}

				}
				else
				{
					newline();
					system(cmd);
					renderscreen(lines, offset);
				}
			}	
		}
		else
		{
			check = 1;
		}
		if(kbhit())
		{
			input = getch();
		}
		if(input == 'd')
		{
			offset++;
			input = 0;
			if(offset > 7)
			{
				offset = 0;
			}
			system(cmd);
			renderscreen(lines, offset);
		}
		if(input == 'a')
		{
			offset--;
			input = 0;
			if(offset < 0)
			{
				offset = 7;
			}
			system(cmd);
			renderscreen(lines, offset);
		}
		if(input == 'w')
		{
			shootline(offset, lines);
			input = 0;
			system(cmd);
			renderscreen(lines, offset);
		}
		if(alive == 0)
		{
			std::cout << "lulw u ded";
		}
	}
}
