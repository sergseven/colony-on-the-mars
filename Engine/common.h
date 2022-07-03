#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL __declspec(dllexport)
#else
#define ENGINE_DLL __declspec(dllimport)
#endif

#define DIRECTINPUT_VERSION 0x0500

//Координаты(и длинна) картинок на главных поверхностях
#define x_grnd_length 26
#define y_grnd_length 14

#define x_grnd1 0
#define y_grnd1 0

#define x_grnd2 16
#define y_grnd2 0

#define x_grnd3 32
#define y_grnd3 0

#define x_grnd4 48
#define y_grnd4 0

#define x_grnd5 0
#define y_grnd5 16

#define x_grnd6 16
#define y_grnd6 16

#define x_grnd7 32
#define y_grnd7 16

#define x_grnd8 48
#define y_grnd8 16

#define x_grnd9 0
#define y_grnd9 32

#define x_grnd10 16
#define y_grnd10 32

#define x_grnd11 32
#define y_grnd11 32

#define x_grnd12 48
#define y_grnd12 32

#define x_grnd13 0
#define y_grnd13 48

#define x_grnd14 16
#define y_grnd14 48

#define x_grnd15 32
#define y_grnd15 48

#define x_grnd16 48
#define y_grnd16 48

#define CursorLengthX 16
#define CursorLengthY 16

#define MaxX 800
#define MaxY 600

#define ViewedMapSizeI 59
#define ViewedMapSizeJ 30

#define FaceLengthX 40
#define FaceLengthY 40

typedef struct
{
	int i;		// строка
	int j;		// столбец
}INDEX;

#define QUEUE struct queue

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#include <ddraw.h>
#include "ddutil.h"
#include <Dinput.h>
#include <math.h> 
#include <malloc.h>
#include <mmsystem.h>
#include <string>
#include <vector>
#include <list>
//#include <stack>
using namespace std;

#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "ddraw.lib" )
#pragma comment (lib, "dinput.lib")
#pragma comment (lib, "winmm.lib")

#pragma warning(disable: 4251)

#endif _COMMON_H_