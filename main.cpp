#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

typedef enum { cross_X = -1, empty = 0, circle_O = 1 }status;
typedef enum { pcross = -1, pcircle = 1 }pstatus;
typedef enum { wcross = -1, goon = 0, wcircle = 1 }winner;
typedef enum { row, col, lb_rt, lt_rb }model;

void Draw(status chessboard[3][3]);
winner Judge(status chessboard[3][3], int x, int y);
void crosswin(void);
void circlewin(void);
void gamedraw(void);
void (*Finish[3])(void) = { crosswin,gamedraw,circlewin };
void GetLine(status chessboard[3][3], int x, int y, model m);
status IsFilledWith(status line[3]);

status arr[3];
int count = 0;

int main(void)
{
	status chessboard[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			chessboard[i][j] = empty;
		}
	}
	initgraph(450, 450);
	setbkcolor(YELLOW);
	cleardevice();
	setlinecolor(BLUE);
	line(0, 150, 450, 150);
	line(0, 300, 450, 300);
	line(150, 0, 150, 450);
	line(300, 0, 300, 450);
	int x = 0, y = 0;
	pstatus p = pcross;
	winner w = goon;
	ExMessage m;
	while (true)
	{
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN)
		{
			x = m.x / 150;
			y = 2 - m.y / 150;
			if (chessboard[x][y] != empty)continue;
			chessboard[x][y] = (status)p;
			p = (pstatus)(-(int)p);
			Draw(chessboard);
			count++;
			w = Judge(chessboard, x, y);
			if (w != goon || count == 9) break;
		}
	}
	Finish[w + 1]();
	return 0;
}

void Draw(status chessboard[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (chessboard[i][j])
			{
			case cross_X:
				line(i * 150 + 75 - 20, (2 - j) * 150 + 75 + 20,
					i * 150 + 75 + 20, (2 - j) * 150 + 75 - 20);
				line(i * 150 + 75 - 20, (2 - j) * 150 + 75 - 20,
					i * 150 + 75 + 20, (2 - j) * 150 + 75 + 20);
				break;
			case circle_O:
				circle(i * 150 + 75, (2 - j) * 150 + 75, 25);
				break;
			case empty:
				break;
			}
			switch (j)
			{
			case 2:
				putchar('\n');
				break;
			default:
				putchar('  ');
				break;
			}
		}
	}
}

void GetLine(status chessboard[3][3], int x, int y, model m)
{
	switch (m)
	{
	case row:
		for (int i = 0; i < 3; i++)arr[i] = chessboard[x][i];
		break;
	case col:
		for (int i = 0; i < 3; i++)arr[i] = chessboard[i][y];
		break;
	case lb_rt:
		if (x + y != 2) return;
		for (int i = 0; i < 3; i++)arr[i] = chessboard[i][2 - i];
		break;
	case lt_rb:
		if (x != y) return;
		for (int i = 0; i < 3; i++)arr[i] = chessboard[i][i];
		break;
	default:
		break;
	}
	return;
}

status IsFilledWith(status line[3])
{
	if (line[0] == line[1] && line[0] == line[2])
		return line[0];
	return empty;
}

winner Judge(status chessboard[3][3], int x, int y)
{
	for (int m = (int)row; m < (int)lt_rb + 1; m++)
	{
		GetLine(chessboard, x, y, (model)m);

		if (IsFilledWith(arr))
		{
			return (winner)chessboard[x][y];
		}
	}
	return goon;
}

void crosswin(void)
{
	HWND hwnd = GetHWnd();
	MessageBox(hwnd, TEXT("PLAYER CROSS WON"), TEXT("GAME ENDS"), MB_OK);
}

void circlewin(void)
{
	HWND hwnd = GetHWnd();
	MessageBox(hwnd, TEXT("PLAYER CIRCLE WON"), TEXT("GAME ENDS"), MB_OK);
}
void gamedraw(void)
{
	HWND hwnd = GetHWnd();
	MessageBox(hwnd, TEXT("GAME DRAW"), TEXT("GAME ENDS"), MB_OK);
}