////////////////////////////////////////////////////////////
//
//Модуль инициалилаций движка.
//
////////////////////////////////////////////////////////////

#include "Additional.h"

// This is the constructor of a class that has been exported.
// see Engine.h for the class definition
tEngine::tEngine()
{}

tEngine::~tEngine()
{}

tInfantry::tInfantry(int ip, int jp,BYTE whose)
          :tUnit(ip,jp,whose)
{
	Frame = 0;     // Текущий кадр
	Field[ip][jp]->pUnit = this;
	bBuilding=FALSE;
	FRadius=75;
	MinDimage=1;
	MaxDimage=5;
	MinDefend=5;
	MaxDefend=6;
	Action.i = ip; //Координаты текущего действия
	Action.j = jp;
	PassCounter=20;
	SetR(rFoto,0,0,FaceLengthX,FaceLengthY);
	MessageAllUnitsAboutMe(Pos);
	MessageMeAboutAllUnits(Pos);
}

tInfantry::~tInfantry()
{
	Field[Pos.i][Pos.j]->pUnit = NULL;
}

tGunTurret::tGunTurret(int ip, int jp,BYTE whose)
          :tUnit(ip,jp,whose)
{
	Field[ip][jp]->pUnit = this;
	Field[ip][jp]->Passability=0;
	Field[ip-2][jp]->pUnit = this;
	Field[ip-2][jp]->Passability=0;
	Field[ip-1][jp]->pUnit = this;
	Field[ip-1][jp]->Passability=0;
	if (ip%2==0){//четное ip 
		Field[ip-1][jp-1]->pUnit = this;
		Field[ip-1][jp-1]->Passability=0;
	}
	else{//нечетное ip
		Field[ip-1][jp+1]->pUnit = this;
		Field[ip-1][jp+1]->Passability=0;
	}
	bBuilding=TRUE;
	FRadius=1125;
	MinDimage=5;
	MaxDimage=5;
	MinDefend=25;
	MaxDefend=55;
	SetR(rFoto,0,0,FaceLengthX,FaceLengthY);
	MessageAllUnitsAboutMe(Pos);
	MessageMeAboutAllUnits(Pos);
}

tGunTurret::~tGunTurret()
{ 
	Field[Pos.i][Pos.j]->pUnit = NULL;
	Field[Pos.i][Pos.j]->Passability=1;
	Field[Pos.i-2][Pos.j]->pUnit = NULL;
	Field[Pos.i-2][Pos.j]->Passability=1;
	Field[Pos.i-1][Pos.j]->pUnit = NULL;
	Field[Pos.i-1][Pos.j]->Passability=1;
	if (Pos.i%2==0){//четное ip 
		Field[Pos.i-1][Pos.j-1]->pUnit = NULL;
		Field[Pos.i-1][Pos.j-1]->Passability=1;
	}
	else{//нечетное ip
		Field[Pos.i-1][Pos.j+1]->pUnit = NULL;
		Field[Pos.i-1][Pos.j+1]->Passability=1;
	}
}

tBarraks::tBarraks(int ip, int jp,BYTE whose)
          :tUnit(ip,jp,whose)
{
	Field[ip][jp]->pUnit = this;
	Field[ip][jp]->Passability=0;
	Field[ip-2][jp]->pUnit = this;
	Field[ip-2][jp]->Passability=0;
	Field[ip-1][jp]->pUnit = this;
	Field[ip-1][jp]->Passability=0;
	if (ip%2==0){//четное ip 
		Field[ip-1][jp-1]->pUnit = this;
		Field[ip-1][jp-1]->Passability=0;
	}
	else{//нечетное ip
		Field[ip-1][jp+1]->pUnit = this;
		Field[ip-1][jp+1]->Passability=0;
	}
	bBuilding=TRUE;
	FRadius=0;
	ThreadInd=0;
	Complite=0;
	MinDimage=0;
	MaxDimage=0;
	MinDefend=25;
	MaxDefend=55;
	SetR(rFoto,0,0,FaceLengthX,FaceLengthY);
	MessageAllUnitsAboutMe(Pos);
	MessageMeAboutAllUnits(Pos);
}

tBarraks::~tBarraks()
{ 
	Field[Pos.i][Pos.j]->pUnit = NULL;
	Field[Pos.i][Pos.j]->Passability=1;
	Field[Pos.i-2][Pos.j]->pUnit = NULL;
	Field[Pos.i-2][Pos.j]->Passability=1;
	Field[Pos.i-1][Pos.j]->pUnit = NULL;
	Field[Pos.i-1][Pos.j]->Passability=1;
	if (Pos.i%2==0){//четное ip 
		Field[Pos.i-1][Pos.j-1]->pUnit = NULL;
		Field[Pos.i-1][Pos.j-1]->Passability=1;
	}
	else{//нечетное ip
		Field[Pos.i-1][Pos.j+1]->pUnit = NULL;
		Field[Pos.i-1][Pos.j+1]->Passability=1;
	}
}

tExplosion::tExplosion(int ip, int jp,int MnDi,int MxDi)
          :tUnit(ip,jp,0)
{
	LookUp.LogMessage("Run Explosion Constructor ip=%d jp=%d\n",ip,jp);
	bBuilding=FALSE;
	FRadius=30;
	MinDimage=MnDi;//Min 
	MaxDimage=MxDi;//Max Dimage 
	MinDefend=999;//Убить взрыв?? :)
	MaxDefend=999;
	/*Action.i = ip; //Координаты текущего действия
	Action.j = jp;*/
	OSx=randint(-7,7);
	OSy=randint(-7,7);
	//LookUp.LogMessage("До Field[ip][jp]->pUnit->health=%d",Field[ip][jp]->pUnit->health);
	if (Field[ip][jp]->pUnit)
		Field[ip][jp]->pUnit->health+=BYTE((randint(MinDimage,MaxDimage))/ 
	            (randint(Field[ip][jp]->pUnit->MinDefend,
				Field[ip][jp]->pUnit->MaxDefend)));
	//LookUp.LogMessage("После Field[ip][jp]->pUnit->health=%d",Field[ip][jp]->pUnit->health);
	SetR(rFoto,0,0,0,0);
}

tExplosion::~tExplosion()
{}

tRocket::tRocket(INDEX start,INDEX target,int MnDi,int MxDi)
          :tUnit(0,0,CurRival)
{
	LookUp.LogMessage("Run Rocket Constructor\n");
	bBuilding=FALSE;
	MinDimage=MnDi;//Min 
	MaxDimage=MxDi;//Max Dimage 
	MinDefend=1;
	MaxDefend=1;
	Start.x=start.j*26;
	Start.y=start.i*7;
	Target.x=target.j*26;
	Target.y=target.i*7;
	Xl=Target.x-Start.x;
	Yl=Target.y-Start.y;
	OSx=Start.x;
	OSy=Start.y;
	pr=0;
	max_pr=sqrt(Xl*Xl+Yl*Yl);
	Angle=GetAngle(Start.y,Start.x,Target.y,Target.x);
	xpr_temple=Xl/sqrt(Xl*Xl+Yl*Yl);
	ypr_temple=Yl/sqrt(Xl*Xl+Yl*Yl);
	SetR(rFoto,0,0,0,0);
}

tRocket::~tRocket()
{}


void tEngine::InitEngine(HINSTANCE _hCurrentInst,int _nCmdShow)
{
	nCmdShow = _nCmdShow;
	hCurrentInst = _hCurrentInst;
	randomize();
	Flips=0;
    tFile::OpenLogFile("tEngine.log");
    LookUp.OpenLogFile("Look.log");
}

void tEngine::InitDX()
{
	tWindow::CreateWnd();
    tFile::LogMessage("InitWindow complite succesful.\n");
	tDirectInput::InitDirectInput();
	tDirectDraw::InitDirectDraw(hWnd,MaxX,MaxY,16);
}

void tEngine::ReleaseEngine()
{
	tDirectDraw::DeleteDirectDraw();
    tFile::LogMessage("DeleteDD complite succesful.....\n");
	RectUnitLI=RectUnitList.begin();
	while (RectUnitLI!=RectUnitList.end())
	{
		pRectUnit=*RectUnitLI;
		delete pRectUnit;
		RectUnitLI=RectUnitList.erase(RectUnitLI);
	}
    tFile::LogMessage("Run ReleaseEngine() func\n");
	for(UnitLI=UnitList.begin();UnitLI!=UnitList.end();UnitLI++)
	{
		pUnit=*UnitLI;
		delete pUnit;
	}
	UnitLI=AUnitList.begin();
	while (UnitLI!=AUnitList.end())
	{
		//pUnit=*UnitLI;
		//delete pUnit;
		UnitLI=AUnitList.erase(UnitLI);
	}
	tFile::LogMessage("List items deleted\n");
	//
	for (i=0;i<MapSizeI;i++)
	for (j=0;j<MapSizeJ;j++)
		delete Field[i][j];//Деинициалзация карты
    // Конец log-сообщений
    tFile::CloseLogFile();
	LookUp.CloseLogFile();
}

void tEngine::InitGame(void)
{
	try
    {
		InitDX();
		tFile::LogMessage("Begin to load BitMaps\n");
		//Загружаем изображение на плоскости:
		nFontCGbSurf = tDirectDraw::LoadImageFile("FontCG_Black.bmp");//Загружаем шрифт Century Gothic(черный и белый)
        tDirectDraw::SetTransparentColor(nFontCGbSurf,0,0);      //
		nFontCGwSurf = tDirectDraw::LoadImageFile("FontCG_White.bmp");//
        tDirectDraw::SetTransparentColor(nFontCGwSurf,0,0);      //
		nIWSurf = tDirectDraw::LoadImageFile("IW.bmp");//Загружаем окно интерфейса
        tDirectDraw::SetTransparentColor(nIWSurf,0,0);
		tFile::LogMessage("IW BitMap Loaded\n");
		nABGSurf = tDirectDraw::LoadImageFile("allgrnd_isom.bmp");//Территории
        tDirectDraw::SetTransparentColor(nABGSurf,0,0);
		tFile::LogMessage("AllGraund BitMap Loaded\n");
		nASSurf = tDirectDraw::LoadImageFile("allsol.bmp");//Изображения солдат
        tDirectDraw::SetTransparentColor(nASSurf,0,0);
		nAESurf = tDirectDraw::LoadImageFile("AllExpl.bmp");//Изображения солдат
        tDirectDraw::SetTransparentColor(nAESurf,0,0);
		nCSurf = tDirectDraw::LoadImageFile("Cursor.bmp");//курсор
        tDirectDraw::SetTransparentColor(nCSurf,0,0);
		nPic0Surf = tDirectDraw::LoadImageFile("pic0.bmp");//рамка для выдиления
        tDirectDraw::SetTransparentColor(nPic0Surf,0,0);
		nUnitFotosSurf = tDirectDraw::LoadImageFile("AllFotos.bmp");//рамка для выдиления
		//SetRect(&rect,0,0,640,480);
		//tDirectDraw::BlitImage(0,0,nIWSurf,&rect);
		tDirectDraw::ClearScreen();//очищаем екран 
		for (i=0;i<MapSizeI;i++)
		for (j=0;j<MapSizeJ;j++)
			Field[i][j] = new tField;//Инициалзация карты
		tFile::LogMessage("All Fields Created\n");
		for (i=0;i<ViewedMapSizeI*7+1;i++) Mulx7[i]=i*7;
		for (i=0;i<ViewedMapSizeI*7+1;i++) Mulx7p17[i]=i*7+17;
		for (j=0;j<ViewedMapSizeJ*26+1;j++) Mulx26[j]=j*28;
		for (j=0;j<ViewedMapSizeJ*26+1;j++) Mulx26p2[j]=j*28+2;
		TotalAU=0;
		InitPath();
		tFile::LogMessage("InitPath function executed\n");
	}
    catch(tError &error)
    {
        error.AddErrorHistory(" <-tEngine::InitGame <-tEngine.dll");
        throw;
    }
}

tRectUnit::tRectUnit(int xp,int yp,int xl,int yl,tUnit* pU)
{
	SetR(Rect,xp,yp,xl,yl);
	pUnit = pU;
}

tRectUnit::~tRectUnit()
{}

tRect::tRect(int xp,int yp,int xl,int yl,tUnit* pU)
{
	SetR(Rect,xp,yp,xl,yl);
	pUnit = pU;
}

tRect::~tRect()
{}

tField::tField()
{
	nSprt = randint(2,3);
	pUnit = NULL;
	Passability = TRUE;
}

tField::~tField()
{}

tUnit::tUnit(int ip,int jp,BYTE whose)
{
	Whose = whose;
	Pos.i = ip;
	Pos.j = jp;
	bDie = FALSE; // Флаг “смерти” – объект нужно уничтожить?
	Counter = 0;
	Frame = 0;     // Текущий кадр
	Alloted = FALSE;
	pAttUnit=NULL;
	health=H_ONE;
	OSx=0;
	OSy=0;
}

tUnit::~tUnit()
{}

void tEngine::InitPath()
{
	//инициализация массива в соответсвии с размером текущей карты
	for (i=0;i<MapSizeI+4;i++)
	for (j=0;j<MapSizeJ+4;j++)
		WA[i][j]=new PATHARRAY;
	// сброс всех параметров
	for(i=0;i<MapSizeI+4;i++)
	for(j=0;j<MapSizeJ+4;j++)
	{
		WA[i][j]->mark=0;
		WA[i][j]->block=1;
		//WA[i][j]->pI=i;
		//WA[i][j]->pJ=j;
	}
	//tFile::LogMessage("InitPath...Step 1 executed\n");
	/*//"облицовка" непроходимым квадратом массива
	for (i=0;i<MapSizeI+4;i++)
	{
		WA[i][0]->block=1;
		WA[i][1]->block=1;
		WA[i][MapSizeJ+2]->block=1;
		WA[i][MapSizeJ+3]->block=1;
	}
	//tFile::LogMessage("...........Step 2 executed\n");
	for (j=0;j<MapSizeJ+4;j++)
	{
		//tFile::LogMessage("\n");
		WA[0][j]->block=1;
		WA[1][j]->block=1;
		WA[MapSizeI+2][j]->block=1;
		WA[MapSizeI+3][j]->block=1;
	}*/
	//tFile::LogMessage("...........Step 3 executed\n");
}
