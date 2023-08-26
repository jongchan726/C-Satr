#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#include "mysystem.h"

#define MAX 50
#define BACKCOLOR 0

int x = 70;
int y = 38;

int player = 1;

int score = 0;


struct Enemy
{

	int ex[MAX];
	int ey[MAX];
	int enemy[MAX];
} ene;


void Spawn(void)
{
	for (int i = 0; i < MAX; i++)
	{
		if (!ene.enemy[i])
		{
			ene.ex[i] = (rand() % 85) + 30;
			ene.ey[i] = 0;
			ene.enemy[i] = 1;

			break;
		}
	}
 }

void InputProcess(void)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//왼쪽
	{
		x--;

		if (x <= 30)
		{
			x = 98;
		}

	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)//오른쪽
	{
		x++;

		if (x >= 98)
		{
			x =30;
		}
	}
	/*
		if (GetAsyncKeyState(VK_UP) & 0x8000)//위
		{
			y--;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)//아래
		{
			y++;
		}
		*/
}

int EnemyProcess(void)
{
	int count = 0;

	for (int i = 0; i < MAX; i++)
	{
		if (ene.enemy[i])
		{
			SetColor(BACKCOLOR, 14);
			count++;
			GotoXY(ene.ex[i], ene.ey[i]);
			printf("★");
			ene.ey[i]++;
			if (ene.ey[i] == y)
			{
				if (ene.ex[i] == x)
				{
					player = 0;
				}
			}
			if (ene.ey[i] > y)
			{
				ene.enemy[i] = 0;
			}
		}
	}

	return count;
}
void Init(void)
{
	srand(time(NULL));

	system("mode con cols=100 lines=40");
	ene.enemy[0] = 0;

	system("title avoid Stars");
	SetColor(BACKCOLOR, 0);
}

void RanderPlayer(void)
{
	if (player)
	{
		SetColor(BACKCOLOR, 2);
		GotoXY(x, y);
		printf("▲");
	}
	else
	{
		SetColor(BACKCOLOR, 12);
		GotoXY(x, y);
		printf("▩");
	}
}

void Score(void)
{
	if (player)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (ene.ey[i] == y)
			{
				score++;
			}
			GotoXY(0, 0);
			printf("SCORE : %d", score);
		}
	}
	GotoXY(0, 0);
	printf("SCORE : %d", score);
}

void StartMenu(void)
{
	while (_kbhit())
	{
		_getch();
	}

	while (1)
	{
		SetColor(BACKCOLOR, 15);
		Clear();
		GotoXY(44, 17);
		printf("별 피하기");
		GotoXY(40, 28);
		printf("Press any key....");


		if (_kbhit())
		{
			break;
		}
	}
}

void GameMain(void)
{

	int state = 0;

	while (1)
	{
		if (player)
		{
			//플레이어 이동
			InputProcess();


			//별 생성
			Spawn();
			Sleep(10);
		}

		//플레이어 출력
		RanderPlayer();

		//점수 출력
		Score();

		GotoXY(0, 0);

		//별 이동
		state = EnemyProcess();
		GotoXY(0, 0);
		system("cls");

		if (state == 0)
		{
			break;
		}
	}
}

int ResultMenu(void)
{
	int bRet = 0;
	while (1)
	{
		SetColor(BACKCOLOR, 15);
		Clear();
		GotoXY(45, 17);
		printf("──────────");
		GotoXY(45, 19);
		printf(" 게임 오버");
		GotoXY(45, 21);
		printf("SCORE : %d", score);
		GotoXY(45, 23);
		printf("──────────");
		GotoXY(44, 25);
		printf("continue...Y/N");
		if (GetAsyncKeyState('Y') & 0x8000)
		{
			bRet = 0;
			player = 1;
			score = 0;
			break;
		}
		if (GetAsyncKeyState('N') & 0x8000)
		{
			bRet = 1;
			player = 0;
			break;
		}
	}
	return bRet;
}
	
int main()
{
	int state = 0;
	
	Init();

	while (1)
	{
		StartMenu();
		GameMain();
		if (ResultMenu())
		{
			break;
		}
	}
	Clear();

	return 0;
}