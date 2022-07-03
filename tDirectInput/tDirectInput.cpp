#include "tDirectInput.h"

tDirectInput::tDirectInput()
{
}


int tDirectInput::InitDirectInput(LPCREATESTRUCT lpCreateStruct)
{
// HRESULT r=DirectInputCreate(GetInstanceHandle(),
//   DIRECTINPUT_VERSION, &dinput, 0 );
// if (r!=DI_OK)
 //  return -1;
 if (InitMouse()==FALSE)
  return -1;
 if (InitKeyboard()==FALSE)
  return -1;
 //if (tDirectDraw::OnCreate(lpCreateStruct) == -1)
 //return -1;
 return 0;
}

BOOL tDirectInput::InitMouse()
{
 HRESULT r;
 r = dinput->CreateDevice( GUID_SysMouse, &mouse, 0 );
 if (r!=DI_OK)
  return FALSE;
// r = mouse->SetDataFormat( &c_dfDIMouse );
 if (r!=DI_OK)
  return FALSE;
// r = mouse->SetCooperativeLevel( GetSafeHwnd(),
 // DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
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
 HRESULT r;
 r = dinput->CreateDevice( GUID_SysKeyboard, &keyboard, 0 );
 if (r!=DI_OK)
  return FALSE;
// r = keyboard->SetDataFormat( &c_dfDIKeyboard );
 if (r!=DI_OK)
  return FALSE;
// r=keyboard->SetCooperativeLevel( GetSafeHwnd(),
  // DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
 if (r!=DI_OK)
  return FALSE;
 return TRUE;
}

void tDirectInput::OnActivate()
{
// DirectDrawWin::OnActivate(nState, pWndOther, bMinimized);
 if (keyboard)
   keyboard->Acquire();
  if (mouse)
   mouse->Acquire();
}

void tDirectInput::DrawScene()
{
 static char key[256];
 keyboard->GetDeviceState( sizeof(key), &key );
 if ( key[DIK_ESCAPE] & 0x80 )
//  PostMessage( WM_CLOSE );
 BOOL done=FALSE;
 while (0)//!done)
 {
  DIDEVICEOBJECTDATA data;
  DWORD elements=1;
  HRESULT r=mouse->GetDeviceData( sizeof(data), &data,
    &elements, 0 );
  if (r==DI_OK && elements==1)
  {
   switch(data.dwOfs)
   {
   case DIMOFS_X:
    x+=data.dwData;
    break;
   case DIMOFS_Y: 
    y+=data.dwData;
    break;
   }
  }
  //else if (elements==0)
//   done=TRUE;
 }

// BltSurface( primsurf, sphere, x, y, TRUE );
}

tDirectInput::~tDirectInput()
{
 /*if (dinput)
  dinput->Release(), dinput=0;
 if (keyboard)
 {
  keyboard->Unacquire();
  keyboard->Release(), keyboard=0;
 }

 if (mouse)
 {
  mouse->Unacquire();
  mouse->Release(), mouse=0;
 }*/
}



