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
	BYTE CreateOffScreenSurface(UINT width,UINT height);//������� ����������� �����������
	BOOL LoadImageFile(LPCSTR szBitmap);
	BOOL CopyDibToSurface(BYTE surface,char szBitmap[],//�������� ����������� �� ������ ��
	                        int x,int y,int cx,int cy);//���������� �����������
//	BOOL SetPalette(char szBitmap[]);//������������� �������
	inline void /*BOOL*/ BlitImage(int x,int y,//��������� ����������� � ����������� �����������
	BYTE &surfaceNum,RECT* rect);//�� ��������� �����������
	inline void /*BOOL*/ FlipSurfaces();//��������� ������������ ������������
    void ClearScreen(void);
	void VLine(int x,int y,int yend,DWORD c);
	void HLine(int x,int y,int xend,DWORD c);
	void DEBar(int x,int y,int lx,int ly,DWORD c);//DrawEmptyBar
		//������������� ���������� �����
	BOOL SetTransparentColor(BYTE surface,int r,int g,int b);
    BOOL SetTransparentColor(BYTE surface,int low,int high);
	DWORD DDConvertRGB(LPDIRECTDRAWSURFACE pdds, COLORREF rgb);
	void DeleteDirectDraw();//������� ������� DirectDraw
   	LPDIRECTDRAWSURFACE lpDDSOffSurface[101];//������ �� 101 ����������� �����������
protected:
	BOOL CopyBMP(LPDIRECTDRAWSURFACE *lpSurf,HBITMAP hbm);
	void MakeFalse();//�������������� ��������� �����
	protected:
	
		BYTE m_currentSurfaceNum;//������� ���������� ����������� ������������
	    LPDIRECTDRAW lpDD;//������ DirectDraw
    	LPDIRECTDRAWSURFACE lpDDSPrimary;//��������� �����������
    	LPDIRECTDRAWSURFACE lpDDSBack;//��������� �����������
//	    LPDIRECTDRAWPALETTE lpDDPal;//�������
    	BOOL m_colorKeySet[101];//���� �� �������� ����(�� ������ ����������� �����������)?
		DWORD transFlag;
		HRESULT result;
		BOOL exitLoop;
};
#endif _TDIRECTDRAW_H