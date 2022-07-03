#ifndef _TDIRECTDRAW_H_
#define _TDIRECTDRAW_H_

#include "..\tWindow\tWindow.h"
#include "..\tFile\tFile.h"

const BACKBUFFERNUM=0;

class ENGINE_DLL tDirectDraw : public tWindow,
                               public tFile
{
public:
	tDirectDraw();
    virtual ~tDirectDraw();
	//
	BOOL InitDirectDraw(HWND hWindow,int width,int height,byte color);
	BYTE CreateOffScreenSurface(UINT width,UINT height);//создает внеэкранную поверхность
	BOOL LoadImageFile(LPCSTR szBitmap);
	BOOL CopyDibToSurface(BYTE surface,char szBitmap[],//копирует изображение из растра на
	                        int x,int y,int cx,int cy);//внеэранную поверхность
//	BOOL SetPalette(char szBitmap[]);//устанавливает палитру
	inline void /*BOOL*/ BlitImage(int x,int y,//переносит изображение с внеэкранной поверхности
	BYTE &surfaceNum,RECT* rect);//на вторичную поверхность
	inline void /*BOOL*/ FlipSurfaces();//выполняет переключение поверхностей
    void ClearScreen(void);
	void VLine(int x,int y,int yend,DWORD c);
	void HLine(int x,int y,int xend,DWORD c);
	void DEBar(int x,int y,int lx,int ly,DWORD c);//DrawEmptyBar
		//устанавливает прозрачные цвета
	BOOL SetTransparentColor(BYTE surface,int r,int g,int b);
    BOOL SetTransparentColor(BYTE surface,int low,int high);
	DWORD DDConvertRGB(LPDIRECTDRAWSURFACE pdds, COLORREF rgb);
	void DeleteDirectDraw();//удаляет объекты DirectDraw
   	LPDIRECTDRAWSURFACE lpDDSOffSurface[101];//массив на 101 внеэкранную поверхность
protected:
	BOOL CopyBMP(LPDIRECTDRAWSURFACE *lpSurf,HBITMAP hbm);
	void MakeFalse();//инициализирует начальные флаги
	protected:
	
		BYTE m_currentSurfaceNum;//текущее количество внеэкранных поверхностей
	    LPDIRECTDRAW lpDD;//объект DirectDraw
    	LPDIRECTDRAWSURFACE lpDDSPrimary;//первичная поверхность
    	LPDIRECTDRAWSURFACE lpDDSBack;//вторичная поверхность
//	    LPDIRECTDRAWPALETTE lpDDPal;//палитра
    	BOOL m_colorKeySet[101];//есть ли цветовой ключ(на каждую внеэкранную поверхность)?
		DWORD transFlag;
		HRESULT result;
		BOOL exitLoop;
};
#endif _TDIRECTDRAW_H