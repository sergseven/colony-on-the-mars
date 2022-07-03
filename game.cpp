#pragma comment (lib,"winmm.lib")

#include "Engine\Engine.h"

tEngine* engine = new tEngine;

//LRESULT APIENTRY WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
//int randint(int w);

void Null(void){}

void RunUpdate(void){
	engine->Update();
}

void InitGameDemo()
{
	try
	{
		engine->LogMessage("run InitGameDemo Thread\n");
		CurRival=1;
		for (j=5;j<=20;j++)
		{
			engine->LogMessage("Добавляем солдата в позиции 6 %d\n",j);
			//Добавляем солдата в позиции (6,j)
			NewUnit(7,j,UNITTYPE_INFANTRY);  
		}
		NewUnit(65,2,UNITTYPE_INFANTRY);  
		CurRival=2;
		for (i=5;i<=20;i++)
		{
			engine->LogMessage("Добавляем солдата в позиции 50 %d\n",j);
			//Добавляем солдата в позиции (6,j)
			NewUnit(i,25,UNITTYPE_INFANTRY);  
		}
		NewUnit(60,5,UNITTYPE_TURRET);  
		NewUnit(65,5,UNITTYPE_BARRAKS);  
		engine->SetEngineThread(RunUpdate);
	}
    catch(tError &error)
    {
        error.AddErrorHistory(" <-thread 0x%x",&InitGameDemo);
        throw;
    }
}

int APIENTRY WinMain(HINSTANCE hCurrentInst,
					 HINSTANCE hPreviousInst,LPSTR lpCmdLine,int nCmdShow)
{ 
	try
	{
		engine->InitEngine(hCurrentInst,nCmdShow);
		engine->LogMessage("runSetThread\n");
		engine->SetEngineThread(InitGameDemo);
		engine->LogMessage("runEng\n");
		engine->RunEngine(150,75);
		engine->LogMessage("Realease\n");
		engine->ReleaseEngine();
	}
    catch(tError &error)
    {
        error.AddErrorHistory(" <-WinMain <-Game.exe");
        const char* errorMessage = error.GetErrorMessage();
        // Выводим сообщение об ошибке в log-файл
        engine->LogMessage("\n%s\n",errorMessage);
        // Выводим сообщение об ошибке на экран
        MessageBox(NULL,errorMessage,"Критическая ошибка!",MB_OK/*|MB_ICONERROR*/);
        delete engine;
        return 1;
    }
	// Очищаем списки
	/*if (!UnitList.empty())
		UnitList.clear();
	/*if (!AUnitList.empty())
		AUnitList.clear();
	if (!RectList.empty())
		RectList.clear();*/
    delete engine;
	return 0;
}