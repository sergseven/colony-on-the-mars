// Engine.cpp : Defines the entry point for the DLL application.
//

#include "Engine.h"

int randint(int w)
{
	int r=rand();
	if (r<0) r=-r;
	return r=1+r%w;
}

void tEngine::InitEngine(HINSTANCE _hCurrentInst,int _nCmdShow)
{
	nCmdShow = _nCmdShow;
	hCurrentInst = _hCurrentInst;
    tFile::OpenLogFile("tEngine.log");
}

void tEngine::InitDD()
{
	tWindow::CreateWnd();
    tFile::LogMessage("InitWindow complite succesful.....\n");
	if (!tDirectDraw::InitDirectDraw(hWnd,640,480,24))
		tFile::LogMessage("InitDD Failed");
	else tFile::LogMessage("InitDD Succesfull!\n");
}

void tEngine::RunEngine()
{
	MSG msg;//сообщения
	InitGame();
	tFile::LogMessage("InitGmae Thread Complite\n");
    try
    {
		while(1)
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        {
			if(msg.message==WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
        }
        else
			//// Запуск задачи
            (*m_thread)();

		
    tFile::LogMessage("Quit doing.....");
    }
    catch(tError &error)
    {
        error.AddErrorHistory(" <-tEngine::RunEngine <-tEngine.dll");
        throw;
    }

}

void tEngine::SetEngineThread(void (*thread)(void))
{
    // Сохранение ссылки на задачу
    m_thread = thread;
}

void tEngine::ReleaseEngine()
{
	for (i=0;i<20;i++)
	for (j=0;j<38;j++)
		delete Field[i][j];//Деинициалзация карты
	//
	for(MyListIterator iterator=List.begin(); iterator !=List.end(); iterator++)
	{
		pUnit=*iterator;
		delete pUnit;
	}
	// Очищаем список
	List.clear(); 
	//
	tDirectDraw::DeleteDirectDraw();
    tFile::LogMessage("DeleteDD complite succesful.....\n");
    // Конец log-сообщений
    tFile::CloseLogFile();
}

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

void tEngine::InitGame(void)
{
	try
    {
		InitDD();
		tFile::LogMessage("InitMain not Failed\n");
		tField* Field[20][38];
		for (i=0;i<20;i++)
		for (j=0;j<38;j++)
			Field[i][j] = new tField;//Инициалзация карты
		/*int cU = 0;//Общее число юнитов
		const MaxCUnits = 10;
		//tField *Map[50][50];
		tUnit *UnitMass[MaxCUnits];
		for (int i=0;i<=9;i++)
		{
			UnitMass[++cU]=new tUnit;
			//Задание характеристик объекту
			UnitMass[cU]->Whose = 1;//Чьей рассы?
			UnitMass[cU]->Pos.x = 2;//Начальная позиция на карте
			UnitMass[cU]->Pos.y = i;
			UnitMass[cU]->Action.x = 2;//Начальное действие.
			UnitMass[cU]->Action.y = i;//Совпадает с позицией - стоять.
			//UnitMass[cU]->BitMap = ;
			UnitMass[cU]-> PathMass = NULL;//Сразу идти никуда не надо:)
		}*/
		tFile::LogMessage("Begin to load BitMap\n");
		//Загружаем изображение на плоскости:
		nIWSurf = tDirectDraw::LoadImageFile("IW.bmp");//Загружаем окно интерфейса
		tFile::LogMessage("IW BitMap Loaded\n");
		nABGSurf = tDirectDraw::LoadImageFile("allgrnd.bmp");//Территории
		tFile::LogMessage("AllGraund BitMap Loaded\n");
		//int nASSurf = engine->LoadImageFile("allsol.bmp");//Изображения солдат
		SetRect(&rect,0,0,640,480);
		tDirectDraw::BlitImage(0,0,nIWSurf,&rect);
	}
    catch(tError &error)
    {
        error.AddErrorHistory(" <-tEngine::InitGame <-tEngine.dll");
        throw;
    }
}


tField::tField()
{
	nSprt = randint(16);
}

tField::~tField()
{}

tUnit::tUnit()
{}

tUnit::~tUnit()
{}

// This is the constructor of a class that has been exported.
// see Engine.h for the class definition
tEngine::tEngine()
{ 
}

tEngine::~tEngine()
{ 
}

tInfantry::tInfantry(int x, int y)
{
    tFile::LogMessage("Infantry Created in pos ",x," ",y);
	Pos.x = x;
	Pos.y = y;
	Field[x][y]->pUnit = this;
}

tInfantry::~tInfantry()
{
	Field[Pos.x][Pos.y]->pUnit = NULL;
}

void tInfantry::Process(tUnit* pUnit)
{
	// на всякий случай…
	if(bDie) return;
	// Получим тип объекта, с которым взаимодействуем…
	BYTE Type = pUnit->GetType();
	// Если другой объект – взрыв, дальнейшая обработка не нужна
	if(Type == UNITTYPE_INFANTRY) return;
	// Если есть столкновение…
	if(Collision(pUnit))
	{
		switch(pUnit->GetType())
		{
			// Взрывом задело объект типа “игрок”
			case UNITTYPE_INFANTRY:
				pUnit->Kill(); // Убиваем игрока
			break;
			default:
			break;
		} // switch
	} // if
} // Process()


BOOL tInfantry::Move()
{
	// Уничтожить?
	if(bDie) return FALSE;
	if ((Pos.x!=Action.x)&&(Pos.y!=Action.y))

	// Изменяем счетчик анимации
	if(Counter < 3) Counter++;
	else
	{
		Counter = 0;
		if(Frame < 8) // Изменяем текущий кадр
			Frame++;
		else
			return FALSE; // Уничтожить
	}
	return TRUE; // Не уничтожать
} // Move() 

void tInfantry::Blit(void)
{}

BOOL tUnit::Collision(tUnit* pUnit)
{
	return 0;
}

