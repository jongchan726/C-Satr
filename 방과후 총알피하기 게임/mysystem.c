#include <stdio.h>
#include <Windows.h>

//커서를 해당 위치로 이동하는 함수
void GotoXY(int _x, int _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//커서의 x, y 위치를 알려주는 함수 
COORD GetXY(void)
{
	COORD pos;
	CONSOLE_SCREEN_BUFFER_INFO curInfor;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);
	pos.X = curInfor.dwCursorPosition.X;
	pos.Y = curInfor.dwCursorPosition.Y;

	return pos;
}

//화면을 지우는 함수
void Clear(void)
{
	system("cls");
}

//타이틀을 변경하는 함수
void SetTitle(const char* _szConsoleName)
{
	SetConsoleTitle(_szConsoleName);
}

//글자색, 배경색을 변경하는 함수
//배경색 0 ~ 15, 글자색 0~ 15 까지 16색 사용해서 변경하는 함수
void SetColor(unsigned char _BgColor, unsigned char _TextColor)
{
	if (_BgColor > 15 || _TextColor > 15) return;

	//배경색과 글자색을 동시에 설정하는 함 수 - high 4bit: 배경색, Low 4 bit: 글자색
	//0x00f0 이면 f은 흰색 배경 0은 검정 글씨
	unsigned short ColorNum = (_BgColor << 4) | _TextColor;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorNum);
}

//커서를 보이게 안 보이게 하는 함수
/*
void SetCursor(BOOL _bShow)
{
	CONSOLE_CURSOR_INFO curInfor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);
	curInfor.bVisible = _bShow;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);
}
*/
