#include "tDirectInput.h"

tDirectInput::tDirectInput()
{
	pRB = FALSE;
	pLB = FALSE;
	cRB = false;
	cRB = false;
}


BOOL tDirectInput::InitDirectInput()
{
    tFile::LogMessage("InitDirectInput.....");
	HRESULT r=DirectInputCreate(hInstance,
	DIRECTINPUT_VERSION, &dinput,0 );
	if (r!=DI_OK)
		return 0;
	if (!InitMouse())
		return 0;
 //if (InitKeyboard()==FALSE)
 //return -1;
 //if (tDirectDraw::OnCreate(lpCreateStruct) == -1)
 //return -1;
    tFile::LogMessage("Done\n");
	return 1;
}

BOOL tDirectInput::InitMouse()
{
	mx = MaxX/2;// 640(800)/2
	my = MaxY/2;// 480(600)/2
	HRESULT r = dinput->CreateDevice( GUID_SysMouse, &mouse, 0 );
	if (r!=DI_OK)
		return FALSE;
	r = mouse->SetDataFormat(&c_dfDIMouse);
	if (r!=DI_OK)
		return FALSE;
	r = mouse->SetCooperativeLevel(hWnd,
		DISCL_EXCLUSIVE | DISCL_FOREGROUND );
	if (r!=DI_OK)
		return FALSE;
	DIPROPDWORD property;
	property.diph.dwSize=sizeof(DIPROPDWORD);
	property.diph.dwHeaderSize=sizeof(DIPROPHEADER);
	property.diph.dwObj=0;
	property.diph.dwHow=DIPH_DEVICE;
	property.dwData=64;
	r = mouse->SetProperty( DIPROP_BUFFERSIZE, &property.diph );
	if (r!=DI_OK)
		return FALSE;
	return TRUE;
}

BOOL tDirectInput::InitKeyboard()
{
 /*HRESULT r;
 r = dinput->CreateDevice( GUID_SysKeyboard, &keyboard, 0 );
 if (r!=DI_OK)
  return FALSE;
// r = keyboard->SetDataFormat( &c_dfDIKeyboard );
 if (r!=DI_OK)
  return FALSE;
// r=keyboard->SetCooperativeLevel( GetSafeHwnd(),
  // DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
 if (r!=DI_OK)*/
  return FALSE;
 //return TRUE;
}

void tDirectInput::Activate()
{
// DirectDrawWin::OnActivate(nState, pWndOther, bMinimized);
 //if (keyboard)
 // keyboard->Acquire();
  if (mouse)
   mouse->Acquire();
}

void tDirectInput::DrawScene()
{
	xb=0,yb=0;
	elements=1;
//	static char key[256];
//	keyboard->GetDeviceState( sizeof(key), &key );
//	if ( key[DIK_ESCAPE] & 0x80 )
//		PostQuitMessage(0);
	done=FALSE;
	cRB = false;
	cLB = false;
	while (!done)
	{
		hr=mouse->GetDeviceData( sizeof(data), &data,&elements, 0 );
		if (hr==DI_OK && elements==1)
		{
			switch(data.dwOfs)
			{
			case DIMOFS_X:
				xb=mx+data.dwData;
				if ((xb<=MaxX-CursorLengthX)&&(xb>=0))
					mx=xb;
			break;
			case DIMOFS_Y:
				yb=my+data.dwData;
				if ((yb<=MaxY-CursorLengthY)&&(yb>=0))
					my=yb;
			break;
			case DIMOFS_BUTTON0:
				pLB=!pLB;
				if (pLB) cLB = !cLB;
			break;
			case DIMOFS_BUTTON1:
				pRB=!pRB;
				if (pRB) cRB = !cRB;
			break;
			}
		}
		else 
			if (elements==0)
				done=TRUE;
	}
	r.top = 0; 
	r.left = 0;
	r.right = CursorLengthX;
	r.bottom = CursorLengthY;
	tDirectDraw::BlitImage(mx,my,nCSurf,&r);
    //tFile::LogMessage("Cursor Blitted in %d %d \n",x,y);
}

tDirectInput::~tDirectInput()
{
	if (dinput)
		dinput->Release(), dinput=0;
	//if (keyboard)
	//{
	//keyboard->Unacquire();
	// keyboard->Release(), keyboard=0;
	//}
	if (mouse)
	{
		mouse->Unacquire();
		mouse->Release(), mouse=0;
	}
}



