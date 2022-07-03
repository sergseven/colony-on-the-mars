#ifndef _COMMON_H_
#define _COMMON_H_

/*#ifdef ENGINE_EXPORTS
#define ENGINE_DLL __declspec(dllexport)
#else
#define ENGINE_DLL __declspec(dllimport)
#endif*/

#define DIRECTINPUT_VERSION 0x0500

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#include <ddraw.h>
#include "ddutil.h"
#include <Dinput.h>

#include <string>
#include <vector>
#include <list> 
//#include <stack>
using namespace std;

#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "ddraw.lib")

#pragma warning(disable: 4251)

#endif _COMMON_H_