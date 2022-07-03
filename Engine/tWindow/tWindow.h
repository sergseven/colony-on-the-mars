#include "..\common.h"

class ENGINE_DLL tWindow
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
