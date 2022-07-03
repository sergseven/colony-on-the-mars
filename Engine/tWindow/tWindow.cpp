#include "tWindow.h"

LRESULT APIENTRY WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

tWindow::tWindow()
{
}

tWindow::~tWindow()
{
}

void tWindow::CreateWnd(/*HINSTANCE hCurrentInst,int nCmdShow*/)
{
	WNDCLASS wndClass;//Используется для регистрации класса окна
	wndClass.style=CS_HREDRAW|CS_VREDRAW;//определяет свойства окна
	wndClass.lpfnWndProc=WndProc;//определяет адрес функции окна
	wndClass.cbClsExtra=0;//число байт, которое необходимо запросить у Windows. Обычно равна 0
	wndClass.cbWndExtra=0;//число байт, которое необходимо запросить у Windows. Обычно равна 0
	wndClass.hInstance =hCurrentInst;//сообщает Windows о том, кто создает определение класса
	wndClass.hIcon =LoadIcon(hCurrentInst,"");//загружает иконку, в данном случае ее нет
	wndClass.hCursor =LoadCursor(NULL,IDC_ARROW);//стандартный курсор
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//фон приложения
	wndClass.lpszMenuName=NULL;//определяет меню. В данной ситуации меню отсутствует
	wndClass.lpszClassName="Game";//указатель на строку, содержащую имя класса
	RegisterClass(&wndClass);//регистрация окна
	hInstance=hCurrentInst;
	hWnd= CreateWindow( //создание окна
		"Game",
		"Game",
		WS_POPUP,
		0,0,MaxX,MaxY,
		NULL,
		NULL,
		hCurrentInst,
		NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
}

LRESULT CALLBACK WndProc(HWND hWnd,
UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY://Вызывается при разрушении окна
		PostQuitMessage(0);
		break;
	/*case WM_SETCURSOR:
		SetCursor (NULL);
		break;*/ 
	}
	return DefWindowProc(hWnd,message,wParam,lParam);
}


				   

