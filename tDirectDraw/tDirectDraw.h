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
	UINT CreateOffScreenSurface(UINT width,UINT height);//������� ����������� �����������
	BOOL LoadImageFile(LPCSTR szBitmap);
	BOOL CopyDibToSurface(UINT surface,char szBitmap[],//�������� ����������� �� ������ ��
	int x,int y,int cx,int cy);//���������� �����������
//	BOOL SetPalette(char szBitmap[]);//������������� �������
	BOOL BlitImage(int x,int y,//��������� ����������� � ����������� �����������
	UINT surfaceNum,RECT* rect);//�� ��������� �����������
	BOOL FlipSurfaces();//��������� ������������ ������������
    //������������� ���������� �����
	BOOL SetTransparentColor(UINT surface,UINT lowColor,UINT hiColor);
	void DeleteDirectDraw();//������� ������� DirectDraw
   	LPDIRECTDRAWSURFACE lpDDSOffSurface[101];//������ �� 101 ����������� �����������
protected:
	BOOL CopyBMP(LPDIRECTDRAWSURFACE *lpSurf,HBITMAP hbm);
	void MakeFalse();//�������������� ��������� �����
	protected:
	
		UINT m_currentSurfaceNum;//������� ���������� ����������� ������������
	    LPDIRECTDRAW lpDD;//������ DirectDraw
    	LPDIRECTDRAWSURFACE lpDDSPrimary;//��������� �����������
    	LPDIRECTDRAWSURFACE lpDDSBack;//��������� �����������
//	    LPDIRECTDRAWPALETTE lpDDPal;//�������
    	BOOL m_colorKeySet[101];//���� �� �������� ����(�� ������ ����������� �����������)?

};
#endif _TDIRECTDRAW_H
