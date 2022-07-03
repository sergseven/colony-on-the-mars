#include "tDirectDraw.h"
tDirectDraw::tDirectDraw()
{
}

tDirectDraw::~tDirectDraw()
{
}

BOOL tDirectDraw::InitDirectDraw(HWND hWindow,int width,int height, byte color)
{
	hWnd=hWindow;
	m_currentSurfaceNum=0;
	DDSURFACEDESC ddsd;
	DDSCAPS ddscaps;
	HRESULT result= DirectDrawCreate(NULL,&lpDD,NULL);
	if(result!=DD_OK)return FALSE;
	result=lpDD->SetCooperativeLevel(
	hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
	if(result!=DD_OK)return FALSE;
	result=lpDD->SetDisplayMode(width,height,color);
	if(result!=DD_OK)return FALSE;
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
	                      DDSCAPS_FLIP |
	                      DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 1;
	result = lpDD->CreateSurface( &ddsd, &lpDDSPrimary,NULL );
	if(result!=DD_OK)return FALSE;
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	result = lpDDSPrimary->GetAttachedSurface(&ddscaps,&lpDDSBack);
	if(result!=DD_OK)return FALSE;
	MakeFalse();
//	if(!success) DeleteDirectDraw();
	return TRUE;
}

void tDirectDraw::DeleteDirectDraw()
{
    tFile::LogMessage("running DeleteDD.....\n");
//	if(lpDDPal!=NULL)
//	  lpDDPal->Release();
    tFile::LogMessage("Step 1 complite.....\n");
	if(lpDDSPrimary!=NULL)
	  lpDDSPrimary->Release();
    tFile::LogMessage("Step 2 complite.....\n");
	for(UINT x=1;x<=m_currentSurfaceNum;++x)
	  lpDDSOffSurface[x]->Release();
    tFile::LogMessage("Step 3 complite.....\n");
	if(lpDD!=NULL)lpDD->Release();
    tFile::LogMessage("All Steps complite.....\n");
}
UINT tDirectDraw::CreateOffScreenSurface(UINT width,UINT height)
{
	if(m_currentSurfaceNum==100)return 0;
	++m_currentSurfaceNum;
	DDSURFACEDESC ddSurfaceDesc;
	memset(&ddSurfaceDesc,0,sizeof(DDSURFACEDESC));
	ddSurfaceDesc.dwSize=sizeof(DDSURFACEDESC);
	ddSurfaceDesc.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	ddSurfaceDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddSurfaceDesc.dwWidth=width;
	ddSurfaceDesc.dwHeight =height;
	HRESULT result=lpDD->CreateSurface(&ddSurfaceDesc,

		&lpDDSOffSurface[m_currentSurfaceNum],NULL);
	if(result!=DD_OK)
	return 0;
	return m_currentSurfaceNum;
}

/*IDirectDrawSurface * tDirectdraw::DDLoadBitmap(IDirectDraw *pdd, LPCSTR szBitmap, int dx, int dy)
{
    HBITMAP             hbm;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    IDirectDrawSurface *pdds;

    //
    //  try to load the bitmap as a file
    //
	hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, dx, dy, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (hbm == NULL)
	return NULL;

    //
    // get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

    //
    // create a DirectDrawSurface for this bitmap
    //
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = bm.bmWidth;
    ddsd.dwHeight = bm.bmHeight;

    if (pdd->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
	return NULL;

    DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);

    DeleteObject(hbm);

    return pdds;
}

HRESULT tDirectDraw::DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy)
{
    HDC                 hdcImage;
    HDC                 hdc;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    HRESULT             hr;

    if (hbm == NULL || pdds == NULL)
	return E_FAIL;

    //
    // make sure this surface is restored.
    //
    pdds->Restore();

    //
    //  select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
	OutputDebugString("createcompatible dc failed\n");
    SelectObject(hdcImage, hbm);

    //
    // get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap
    dx = dx == 0 ? bm.bmWidth  : dx;    // use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;

    //
    // get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
	StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, dx, dy, SRCCOPY);
	pdds->ReleaseDC(hdc);
    }

    DeleteDC(hdcImage);

    return hr;
}*/


int tDirectDraw::LoadImageFile(LPCSTR szBitmap)
{
    HBITMAP hbm;
	BITMAP bm;
	// загружаем изображение из файла
	hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE |
 							      LR_CREATEDIBSECTION);
	if (hbm == NULL) return 0;
	GetObject (hbm, sizeof(bm), &bm);
	// создаем поверхность требуемого размера
	int nSurf = CreateOffScreenSurface(bm.bmWidth, bm.bmHeight);
	if (nSurf == 0) return 0;
	// копируем изображение на поверхность
	if(CopyBMP(&lpDDSOffSurface[m_currentSurfaceNum],hbm) == 0) return 0;
	DeleteObject (hbm);
	return nSurf;


};

/*
LPDIRECTDRAWSURFACE tDirectDraw::CreateSurface(LPCTSTR filename)
{
 int imagew, imageh;
 GetBmpDimensions( filename, imagew, imageh );
 LPDIRECTDRAWSURFACE surf=CreateOffScreenSurface( imagew, imageh );
 if (surf==0)
  return 0;
 ifstream bmp( filename, ios::binary | ios::nocreate );
 if (!bmp.is_open())
  return 0;
 BITMAPFILEHEADER bmpfilehdr;
 bmp.read( (char*)&bmpfilehdr, sizeof(bmpfilehdr) );
 char* ptr=(char*)&bmpfilehdr.bfType;
 if (*ptr!='B' || *++ptr!='M')
  return 0;
 BITMAPINFOHEADER bmpinfohdr;
 bmp.read( (char*)&bmpinfohdr, sizeof(bmpinfohdr) );
 bmp.seekg( sizeof(bmpfilehdr)+bmpinfohdr.biSize, ios::beg );
 int imagebitdepth=bmpinfohdr.biBitCount;
 int imagesize=bmpinfohdr.biSizeImage;
 if (imagesize==0)
  imagesize=((imagew*(imagebitdepth/8)+3) & ~3)*imageh;
 if (bmpinfohdr.biCompression!=BI_RGB)
  return 0;
 /*if (imagebitdepth==8)
 {
  int ncolors;
  if (bmpinfohdr.biClrUsed==0)
   ncolors=256;
  else
   ncolors=bmpinfohdr.biClrUsed;

  RGBQUAD* quad=new RGBQUAD[ncolors];
  bmp.read( (char*)quad, sizeof(RGBQUAD)*ncolors );
  if (installpalette)
   CreatePalette( quad, ncolors );
  delete [] quad;
 }

 BYTE* buf=new BYTE[imagesize];
 bmp.read( buf, imagesize );
 if (!Copy_Bmp_Surface( surf, &bmpinfohdr, buf ))
 {
  delete [] buf;
  surf->Release();
  return 0;
 }

 delete [] buf;

 return surf;
}

BOOL DirectDrawWin::Copy_Bmp_Surface( LPDIRECTDRAWSURFACE surf,
   BITMAPINFOHEADER* bmphdr, BYTE* buf)
{
 if (surf==0 || bmphdr==0 || buf==0)
  return FALSE;

 int imagew=bmphdr->biWidth;
 int imageh=bmphdr->biHeight;
 int imagebitdepth=bmphdr->biBitCount;

 BOOL ret=FALSE;
 if (imagebitdepth==8)
 {
  if (displaydepth==8)
   ret=Copy_Bmp08_Surface08( surf, buf, imagew, imageh );
 }
 else if (imagebitdepth==24)
 {
  if (displaydepth==16)
   ret=Copy_Bmp24_Surface16( surf, buf, imagew, imageh );
  else if (displaydepth==24)
   ret=Copy_Bmp24_Surface24( surf, buf, imagew, imageh );
  else if (displaydepth==32)
   ret=Copy_Bmp24_Surface32( surf, buf, imagew, imageh );
 }

 return ret;
}

BOOL DirectDrawWin::Copy_Bmp24_Surface24( LPDIRECTDRAWSURFACE surf,
       BYTE* bmpbuf, int w, int h )
{
 if (surf==0 || bmpbuf==0)
  return FALSE;

 DDSURFACEDESC desc;
 ZeroMemory( &desc, sizeof(desc) );
 desc.dwSize = sizeof(desc);
 HRESULT r=surf->Lock( 0, &desc,
    DDLOCK_WAIT | DDLOCK_WRITEONLY, 0 );
 if (r!=DD_OK)
 {
  TRACE("Copy_Bmp24_Surface24: Lock() failed\n");
  return FALSE;
 }
 int bytesrequired=w*3;
 int bytesgiven=(bytesrequired+3) & ~3;
 BYTE* surfbits = (BYTE*)desc.lpSurface;
 BYTE* imagebits = (BYTE*)(&bmpbuf[(h-1)*bytesgiven]);

 // Проверить, совпадает ли формат файла с форматом поверхности
 // Если совпадает, пересылку можно ускорить функцией memcpy()
 if (loREDbit==16 && loGREENbit==8 && loBLUEbit==0)
 {
  TRACE("using optimized code...\n");
  for (int i=0;i<h;i++)
  {
   memcpy( surfbits, imagebits, bytesrequired );
   surfbits += desc.lPitch;
   imagebits -= bytesgiven;
  }
 }
 else
 {
  TRACE("not using optimated code...\n");
  for(int i=0; i>h; i++ )
  {
   RGBTRIPLE* surf=(RGBTRIPLE*)surfbits;
   RGBTRIPLE* image=(RGBTRIPLE*)imagebits;
   for (int p=0;p<w;p++)
   {
    DWORD r=image->rgbtRed << loREDbit;
    DWORD g=image->rgbtGreen << loGREENbit;
    DWORD b=image->rgbtBlue << loBLUEbit;
    DWORD* data=(DWORD*)surf;
    *data = r|g|b;
    surf++;
    image++;
   }
   surfbits += desc.lPitch;
   imagebits -= bytesgiven;
  }
 }
 surf->Unlock( 0 );

 return TRUE;
}*/

BOOL tDirectDraw::CopyBMP(LPDIRECTDRAWSURFACE *lpSurf,HBITMAP hbm)
{
	HDC                  hdcImage;
	HDC                  hdc;
	BITMAP               bm;

	// создаем DC картинки
	hdcImage = CreateCompatibleDC(NULL);
	if(!hdcImage) return 0;
	SelectObject (hdcImage, hbm);
	GetObject (hbm, sizeof(bm), &bm);
	// данная функция дает нам DC связанный с поверхностью
	//     после чего мы можем работать с ним как с обычным Windows DC
	(*lpSurf)->GetDC (&hdc);
	// "блиттим" нашу картинку на поверхность
	//     после этого на поверхности у нас будет храниться нужная нам картинка
	BitBlt (hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcImage, 0, 0, SRCCOPY);
	// нам нужно освободить DC, если вы этого не сделаете, то система зависнет
	(*lpSurf)->ReleaseDC (hdc);

	DeleteDC (hdcImage);
	return 1;
};


BOOL tDirectDraw::CopyDibToSurface(UINT surface,char szBitmap[],
int x,int y,int cx,int cy)
{
	if(surface>100||surface==0)return FALSE;
	HBITMAP hbm;
	hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap,
	IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION);
	if (hbm == NULL)return FALSE;
//	DDCopyBitmap(lpDDSOffSurface[surface], hbm, x,y,cx,cy);
	return TRUE;
}
//BOOL tDirectDraw::SetPalette(char szBitmap[])
//{
//	lpDDPal = DDLoadPalette(lpDD, szBitmap);
//	if (lpDDPal)lpDDSPrimary->SetPalette(lpDDPal);
//	return TRUE;
//}
BOOL tDirectDraw::BlitImage(int x,int y,
UINT surfaceNum,RECT* rect)
{
	DWORD transFlag=DDBLTFAST_NOCOLORKEY;
	if(m_colorKeySet[surfaceNum])transFlag=DDBLTFAST_SRCCOLORKEY;
	HRESULT result;
	BOOL exitLoop=FALSE;
	do
	{
		result=lpDDSBack->BltFast(x,
		y,lpDDSOffSurface[surfaceNum],rect,transFlag|
		DDBLTFAST_WAIT);
		if(result==DDERR_SURFACELOST)lpDDSPrimary->Restore();
		else exitLoop=TRUE;
	}
	while(!exitLoop);
	if(result!=DD_OK)return FALSE;
	return TRUE;
}

BOOL tDirectDraw::FlipSurfaces()
{
	HRESULT result;
	BOOL exitLoop=FALSE;
	do
	{
		result=lpDDSPrimary->Flip(NULL,DDFLIP_WAIT);
		if(result ==DDERR_SURFACELOST)lpDDSPrimary->Restore();
		else exitLoop=TRUE;
	}
	while(!exitLoop);
	if(result!=DD_OK)
	return FALSE;
	return TRUE;
}
BOOL tDirectDraw::SetTransparentColor(UINT surface,UINT
lowColor,UINT hiColor)
{
	DDCOLORKEY ddColorKey;
	ddColorKey.dwColorSpaceLowValue =lowColor;
	ddColorKey.dwColorSpaceHighValue = hiColor;
	HRESULT result = lpDDSOffSurface[surface]->SetColorKey(
	DDCKEY_SRCBLT,&ddColorKey);
	if(result!=DD_OK)return FALSE;
	m_colorKeySet[surface]=TRUE;
	return TRUE;
}

void tDirectDraw::MakeFalse()
{
	for(int i=0;i<100;i++)
		m_colorKeySet[i]=FALSE;
}


