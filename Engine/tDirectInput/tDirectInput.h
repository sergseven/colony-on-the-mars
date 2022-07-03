#ifndef _TDIRECTINPUT_H_
#define _TDIRECTINPUT_H_

#include "..\tDirectDraw\tDirectDraw.h"


class ENGINE_DLL tDirectInput : public tDirectDraw
{
public:
	tDirectInput();
    virtual ~tDirectInput();
	void DrawScene();
	bool cLB,cRB;//был клик 
	bool pLB,pRB;//Нажата ли кнопка
	int mx, my;
protected:
	BYTE nCSurf;
	RECT r;
	BOOL InitDirectInput();
    void Destroy();
    void Activate();
private:
//	BOOL CreateFlippingSurfaces();
//	int SelectDriver();
//	int SelectInitialDisplayMode();
//	BOOL CreateCustomSurfaces();
//	void RestoreSurfaces();
	BOOL InitKeyboard();
	BOOL InitMouse();
private:
	LPDIRECTINPUT dinput;
	LPDIRECTINPUTDEVICE mouse;
	HRESULT hr;
	DIDEVICEOBJECTDATA data;
	DWORD elements;
	BOOL done;
	int xb, yb;
};

#endif _TDIRECTINPUT_H_