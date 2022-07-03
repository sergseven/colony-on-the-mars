#pragma comment (lib,"winmm.lib")

#include "Engine.h"

tEngine* engine = new tEngine;

MyListIterator iter;
MyListIterator iter2;
tUnit* pUnit2;

//LRESULT APIENTRY WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
//int randint(int w);

void Null(void)
{}

void Update(void)
{
	engine->LogMessage("run Update Thread\n");
	for (i = 0;i<20;i++)
	for (j = 0;j<38;j++)
	{
		engine->LogMessage("run For \n");
		switch (Field[i][j]->nSprt)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			SetRect(&rect,Field[i][j]->nSprt*16-16,0,16,16);
		break;
		case 5:
		case 6:
		case 7:
		case 8:
			SetRect(&rect,Field[i][j]->nSprt*16-16,15,16,16);
		break;
		case 9:
		case 10:
		case 11:
		case 12:
			SetRect(&rect,Field[i][j]->nSprt*16-16,31,16,16);
		break;
		case 13:
		case 14:
        case 15:
		case 16:
			SetRect(&rect,Field[i][j]->nSprt*16-16,47,16,16);
		break;
		}
		engine->BlitImage(j*16+15,i*16+24,nABGSurf,&rect);
	}
	engine->LogMessage("run Part 1\n");
	
	// Часть 1 – обработка внутренних данных, и т.д.
	iter = List.begin(); // Настраиваемся на первый элемент…
	// Для всех элементов…
	while(iter!= List.end())
	{
		pUnit=*iter;
		if(!pUnit->Move()) // Объект просит себя уничтожить?
		{
			delete pUnit; // Удаляем объект 
			// Удаляем элемент списка и получаем следующий
			iter = List.erase(iter); 
		}
		else
			iter++; // Следующий элемент
	} // while

		engine->LogMessage("run Part 2\n");

	// Часть 2 - обработка взаимодействия
	iter = List.begin();
	while(iter != List.end())
	{
		pUnit=*iter;
		iter2 = List.begin();
		tUnit* pUnit2;
		while(iter2 != List.end())
		{
			pUnit2 = *iter2;
			// Проверяем…
			if(pUnit && pUnit2 && pUnit != pUnit2)
				pUnit->Process(pUnit2); // И обрабатываем
			iter2++;
		} // while
		iter++;
	} // while
	
	for(iter=List.begin(); iter != List.end();iter++)
	{
		pUnit=*iter;
		pUnit->Blit();
	} 
	
	engine->FlipSurfaces();//выполняет переключение поверхностей
	engine->SetEngineThread(Null);
}

void InitGameDemo()
{
	engine->LogMessage("run InitGameDemo Thread\n");
	for (i=1;i<=10;i++)
	{
		engine->LogMessage("Добавляем солдата в позиции 2 \n");
		// Добавляем солдата в позиции (2,i)
		tInfantry* pInfantry = new tInfantry(2,i);
		List.push_front(pInfantry); 
	}
	engine->SetEngineThread(Update);
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
		engine->RunEngine();
		engine->LogMessage("Realease\n ");
		engine->ReleaseEngine();
	}
    catch(tError &error)
    {
        error.AddErrorHistory(" <-WinMain <-Game.exe");
        const char* errorMessage = error.GetErrorMessage();
        // Выводим сообщение об ошибке в log-файл
        engine->LogMessage("\n%s\n",errorMessage);
        // Выводим сообщение об ошибке на экран
        MessageBox(NULL,errorMessage,"Critical error!",MB_OK|MB_ICONERROR);
        delete engine;
        return 1;
    }

    delete engine;
	return 0;
}