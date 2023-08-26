#include <stdio.h>
#include <Windows.h>

//Ŀ���� �ش� ��ġ�� �̵��ϴ� �Լ�
void GotoXY(int _x, int _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Ŀ���� x, y ��ġ�� �˷��ִ� �Լ� 
COORD GetXY(void)
{
	COORD pos;
	CONSOLE_SCREEN_BUFFER_INFO curInfor;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);
	pos.X = curInfor.dwCursorPosition.X;
	pos.Y = curInfor.dwCursorPosition.Y;

	return pos;
}

//ȭ���� ����� �Լ�
void Clear(void)
{
	system("cls");
}

//Ÿ��Ʋ�� �����ϴ� �Լ�
void SetTitle(const char* _szConsoleName)
{
	SetConsoleTitle(_szConsoleName);
}

//���ڻ�, ������ �����ϴ� �Լ�
//���� 0 ~ 15, ���ڻ� 0~ 15 ���� 16�� ����ؼ� �����ϴ� �Լ�
void SetColor(unsigned char _BgColor, unsigned char _TextColor)
{
	if (_BgColor > 15 || _TextColor > 15) return;

	//������ ���ڻ��� ���ÿ� �����ϴ� �� �� - high 4bit: ����, Low 4 bit: ���ڻ�
	//0x00f0 �̸� f�� ��� ��� 0�� ���� �۾�
	unsigned short ColorNum = (_BgColor << 4) | _TextColor;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorNum);
}

//Ŀ���� ���̰� �� ���̰� �ϴ� �Լ�
/*
void SetCursor(BOOL _bShow)
{
	CONSOLE_CURSOR_INFO curInfor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);
	curInfor.bVisible = _bShow;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);
}
*/
