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
	WNDCLASS wndClass;//������������ ��� ����������� ������ ����
	wndClass.style=CS_HREDRAW|CS_VREDRAW;//���������� �������� ����
	wndClass.lpfnWndProc=WndProc;//���������� ����� ������� ����
	wndClass.cbClsExtra=0;//����� ����, ������� ���������� ��������� � Windows. ������ ����� 0
	wndClass.cbWndExtra=0;//����� ����, ������� ���������� ��������� � Windows. ������ ����� 0
	wndClass.hInstance =hCurrentInst;//�������� Windows � ���, ��� ������� ����������� ������
	wndClass.hIcon =LoadIcon(hCurrentInst,"");//��������� ������, � ������ ������ �� ���
	wndClass.hCursor =LoadCursor(NULL,IDC_ARROW);//����������� ������
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//��� ����������
	wndClass.lpszMenuName=NULL;//���������� ����. � ������ �������� ���� �����������
	wndClass.lpszClassName="Game";//��������� �� ������, ���������� ��� ������
	RegisterClass(&wndClass);//����������� ����
	hInstance=hCurrentInst;
	hWnd= CreateWindow( //�������� ����
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
	case WM_DESTROY://���������� ��� ���������� ����
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,message,wParam,lParam);
}


				   

