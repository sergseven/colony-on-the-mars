////////////////////////////////////////////////////////////
//
//Функция DllMain.
//
////////////////////////////////////////////////////////////

#include "Units.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

/*void tInfantry::Blit(void)
{}*/

/*
for(RectLI=RectList.begin(); RectLI!=RectList.end(); RectLI++)
{
	pRect=*RectLI;
	if (pRect->Rect.left<=mx&&
		pRect->Rect.right>=mx&&
		pRect->Rect.top<=my&&
		pRect->Rect.bottom>=my&&
		pRect->pUnit)
		    pRect->pUnit->Alloted=TRUE;
}*/

