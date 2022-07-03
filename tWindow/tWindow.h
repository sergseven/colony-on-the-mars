#include "..\common.h"

class tWindow
{
public:
	tWindow();
	virtual ~tWindow();
    void CreateWnd();
protected:
	int nCmdShow;
	HINSTANCE hCurrentInst;
    HINSTANCE hInstance;//дескриптор
    HWND hWnd;//Окно
};
