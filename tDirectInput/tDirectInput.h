#ifndef _TDIRECTINPUT_H_
#define _TDIRECTINPUT_H_

#include "..\tDirectDraw\tDirectDraw.h"


class tDirectInput : public tDirectDraw
{
public:
	tDirectInput();
    virtual ~tDirectInput();
	//
protected:
	int InitDirectInput(LPCREATESTRUCT lpCreateStruct);
    void OnDestroy();
    void OnActivate();
    //DECLARE_MESSAGE_MAP()
private:
	BOOL CreateFlippingSurfaces();
private:
	int SelectDriver();
	int SelectInitialDisplayMode();
	BOOL CreateCustomSurfaces();
	void DrawScene();
	void RestoreSurfaces();
private:
	BOOL InitKeyboard();
	BOOL InitMouse();
private:
	LPDIRECTINPUT dinput;
	LPDIRECTINPUTDEVICE mouse;
	LPDIRECTINPUTDEVICE keyboard;
	LPDIRECTDRAWSURFACE sphere;
	int x, y;

};

#endif _TDIRECTINPUT_H_