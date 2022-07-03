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
	WNDCLASS wndClass;//»спользуетс€ дл€ регистрации класса окна
	wndClass.style=CS_HREDRAW|CS_VREDRAW;//определ€ет свойства окна
	wndClass.lpfnWndProc=WndProc;//определ€ет адрес функции окна
	wndClass.cbClsExtra=0;//число байт, которое необходимо запросить у Windows. ќбычно равна 0
	wndClass.cbWndExtra=0;//число байт, которое необходимо запросить у Windows. ќбычно равна 0
	wndClass.hInstance =hCurrentInst;//сообщает Windows о том, кто создает определение класса
	wndClass.hIcon =LoadIcon(hCurrentInst,"");//загружает иконку, в данном случае ее нет
	wndClass.hCursor =LoadCursor(NULL,IDC_ARROW);//стандартный курсор
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//фон приложени€
	wndClass.lpszMenuName=NULL;//определ€ет меню. ¬ данной ситуации меню отсутствует
	wndClass.lpszClassName="Game";//указатель на строку, содержащую им€ класса
	RegisterClass(&wndClass);//регистраци€ окна
	hInstance=hCurrentInst;
	hWnd= CreateWindow( //создание окна
		"Game",
		"Game",
		WS_POPUP,
		0,0,640,480,
		NULL,
		NULL,
		hCurrentInst,
		NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
}

LRESULT APIENTRY WndProc(HWND hWnd,
UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY://¬ызываетс€ при разрушении окна
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,message,wParam,lParam);
}


				   

