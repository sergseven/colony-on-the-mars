#ifndef _TDIRECTDRAW_H_
#define _TDIRECTDRAW_H_

#include "..\tWindow\tWindow.h"
#include "..\tFile\tFile.h"


const BACKBUFFERNUM = 0;

class tDirectDraw : public tWindow,
                               public tFile
{
public:
	tDirectDraw();
    virtual ~tDirectDraw();
	//
	BOOL InitDirectDraw(HWND hWindow,int width,int height,byte color);
	UINT CreateOffScreenSurface(UINT width,UINT height);//создает внеэкранную поверхность
	BOOL LoadImageFile(LPCSTR szBitmap);
	BOOL CopyDibToSurface(UINT surface,char szBitmap[],//копирует изображение из растра на
	int x,int y,int cx,int cy);//внеэранную поверхность
//	BOOL SetPalette(char szBitmap[]);//устанавливает палитру
	BOOL BlitImage(int x,int y,//переносит изображение с внеэкранной поверхности
	UINT surfaceNum,RECT* rect);//на вторичную поверхность
	BOOL FlipSurfaces();//выполняет переключение поверхностей
    //устанавливает прозрачные цвета
	BOOL SetTransparentColor(UINT surface,UINT lowColor,UINT hiColor);
	void DeleteDirectDraw();//удаляет объекты DirectDraw
   	LPDIRECTDRAWSURFACE lpDDSOffSurface[101];//массив на 101 внеэкранную поверхность
protected:
	BOOL CopyBMP(LPDIRECTDRAWSURFACE *lpSurf,HBITMAP hbm);
	void MakeFalse();//инициализирует начальные флаги
	protected:
	
		UINT m_currentSurfaceNum;//текущее количество внеэкранных поверхностей
	    LPDIRECTDRAW lpDD;//объект DirectDraw
    	LPDIRECTDRAWSURFACE lpDDSPrimary;//первичная поверхность
    	LPDIRECTDRAWSURFACE lpDDSBack;//вторичная поверхность
//	    LPDIRECTDRAWPALETTE lpDDPal;//палитра
    	BOOL m_colorKeySet[101];//есть ли цветовой ключ(на каждую внеэкранную поверхность)?

};
#endif _TDIRECTDRAW_H
