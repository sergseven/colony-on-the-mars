// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ENGINE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ENGINE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

// This class is exported from the Engine.dll
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "tDirectInput\tDirectInput.h"
#include "tMusic\tMusic.h"

//Маска тайла для мыши
const Mask[y_grnd_length][x_grnd_length+2] = 
                     {{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3},
                      {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3},
					  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3},
					  {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3},
					  {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3},
                      {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3},
					  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
                      {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
                      {2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4},
                      {2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4},
                      {2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4},
                      {2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4},
                      {2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4},
					  {2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,4,4,4,4,4,4,4,4,4,4,4,4,3}};
ENGINE_DLL enum{UNITTYPE_UNIT=0,
                UNITTYPE_INFANTRY,
				UNITTYPE_TURRET,
				UNITTYPE_MEXPLOSION,
				UNITTYPE_ROCKET,
				UNITTYPE_BARRAKS};

enum {DIR_UP=0,
      DIR_UPRIGHT=1,
	  DIR_RIGHT=2,
	  DIR_RIGHTDOWN=3,
	  DIR_DOWN=4,
	  DIR_DOWNLEFT=5,
	  DIR_LEFT=6,
	  DIR_LEFTUP=7};
#define H_ONE   0
#define H_TWO   1
#define	H_THREE 2 
#define	H_FOUR  3
#define	H_DEAD  4
/*Состояние юнита 
          тип юнита:
          # Солдат    # Техника      # Строение
          0 Здоров      Исправен       Целый
		  1 Ранен       Есть поврежд.  Есть повреждения
		  2 Серь.ранен  Серь.поломка   Серь. повреждения
		  3 Ели жив     Подбит         Почти не функционирует
		  4 Мертв       Разбит         Руины
*/

QUEUE
{
  INDEX info;
  QUEUE *next;
};

// тип для массива отслеживающего поиск пути
typedef struct
{
	int mark;	// флаг определяющий есть ли у ячейки родитель,
				// т.е. находится ли уже ячейка в очереди ?

	int block;	// проходимость ячейки (0 или 1)

	int pI;		// родительская строка
	int pJ;		// родительский столбец
}PATHARRAY;

// к ширине и высоте добавляется 4 единицы, 
// т.к. необходимо ограничить участок, где
// будут происходить вычисления, 
// непроходимыми препятствиями (1)
PATHARRAY* WA[2004][1004];
INDEX *pINDEX;
QUEUE *Q;

typedef INDEX *pLPINDEX;
typedef std::list<pLPINDEX  > tINDEXList; 
typedef std::list<pLPINDEX  >::iterator tINDEXListIterator; 

inline int randint( int low, int high );
inline void randomize(void) { srand(GetTickCount()); }
void SetR(RECT &rect,int x,int y,int xl,int yl);
void insertItem(QUEUE **ppQueue, INDEX nItem);
INDEX removeItem(QUEUE **ppQueue, int *nError);
bool FindPath(INDEX Start,INDEX End,tINDEXList &InPathList);//поиск пути
//две функции, отвечающие за 2 уровень И.И.
void MessageAllUnitsAboutMe(INDEX pos);
void MessageMeAboutAllUnits(INDEX pos);
ENGINE_DLL void NewUnit(int ip,int jp,int who);

class tRocket;

class ENGINE_DLL tUnit//:public tEngine
{
public:
	tUnit(int ip,int jp,BYTE whose);
	virtual ~tUnit();
	//RECT rcRect; // Окружающий объект прямоугольник
	INDEX Pos; // координаты объекта
	INDEX Action; //Координаты текущего действия(путишествия)
	BOOL bAnim; // Есть ли анимация
	BOOL bDie; // Флаг “смерти” – объект нужно уничтожить?
	BOOL bBuilding; // Флаг строения – объект не двигается?
	RECT rFoto;//Прямоугольник в банке изобоажений юнитов
	BYTE Frame; // Текущий кадр
	BYTE Counter; // Счетчик для анимации
    int OSx;//Смещение на экране по х
	int OSy;//                   по у 
	int pr;//для снаряда...
	float xpr_temple,ypr_temple;
	POINT Start,Target;
	BYTE Angle;//угол поворота (см. engine.h)
	BYTE health;//состояние юнита
	int ThreadInd;//текущяя задача юнита(произв. юнита,апгрейт себя и т.д.)
	BYTE Complite;//прогресс вышеуказанного
	int MinDimage;
	int MaxDimage;
	int MinDefend;
	int MaxDefend;
	tUnit* pAttUnit;//pointer of Attacked Unit(Указатель на атакованный юнит)
	tINDEXList PathList; //список координат пути
	BYTE Whose; //принадлежность 
	BOOL Alloted; //Выделен ли
	void Kill() { bDie = TRUE; }
	BOOL Collision(tUnit* pUnit);
	//virtual void Blit() = 0;
	virtual BYTE GetType() = 0;
	virtual void Process(tUnit* pUnit) = 0;
	virtual BOOL Move() = 0;
};

class ENGINE_DLL tRectUnit
{
public:
	tRectUnit(int xp,int yp,int xl,int yl,tUnit* pU);
	virtual ~tRectUnit();
	RECT Rect;
	tUnit* pUnit;
};

class ENGINE_DLL tRect
{
public:
	tRect(int xp,int yp,int xl,int yl,tUnit* pU);
	virtual ~tRect();
	RECT Rect;
	int ThreadInd;
	tUnit* pUnit;
};

class ENGINE_DLL tField //: public tEngine 
{
public:
	tField();
    virtual ~tField();
	//INDEX Pos;
	tUnit* pUnit;
	int nSprt;
	BOOL Passability;
};

typedef tUnit *pLPUNIT;
typedef tRectUnit *pLPRECTUNIT;
typedef tRect *pLPRECT;
typedef std::list<pLPUNIT > tUnitList; 
typedef std::list<pLPUNIT >::iterator tUnitListIterator; 
typedef std::list<pLPRECTUNIT > tRectUnitList; 
typedef std::list<pLPRECTUNIT >::iterator tRectUnitListIterator; 
typedef std::list<pLPRECT > tRectList; 
typedef std::list<pLPRECT >::iterator tRectListIterator; 


ENGINE_DLL tUnitList UnitList; // список юнитов
ENGINE_DLL tUnitList AUnitList; // список выделенных юнитов
ENGINE_DLL tRectUnitList RectUnitList; // список зон для мыши
ENGINE_DLL tRectList RectList; // список зон для мыши
           tINDEXListIterator INDEXLI;
           tField* Field[2000][1000];//Карта (максимальная - 2000х1000)
           tUnit* pUnit;
           tUnit* pUnit2;
		   tRectUnit* pRectUnit;
		   tRect* pRect;
		   int MapSizeI;
		   int MapSizeJ; 
		   int vx,vy;//virtual x.y
		   int TileI,TileJ;
		   double len;
		   BYTE OffSet,OffSet2;
		   BYTE angle;
		   BYTE TotalAU;//Total Alloted Unit(s) (Всего выделенных юнитов)
		   POINT OffSet3;
		   POINT FirstC;
ENGINE_DLL int i,j;
ENGINE_DLL BYTE CurRival;
           RECT rect;
           BYTE nIWSurf;
           BYTE nABGSurf;
           BYTE nASSurf;
		   BYTE nAESurf;
           BYTE nPic0Surf;
		   BYTE nFontCGbSurf;
		   BYTE nFontCGwSurf;
		   BYTE nUnitFotosSurf;
		   LONG Flips;
		   short int FPS;	
		   static DWORD timenow;
		   static DWORD timethen;
		   DWORD time;
		   int time1,time2,time3,time4,time5,time6,time7,time8,time9,time10;
		   double seconds;
		   char tstr1[256];
		   char tstr2[256];
		   char tstr3[256];
		   char tstr4[256];
		   tFile LookUp;
		   int Mulx26[ViewedMapSizeJ*26+1];
		   int Mulx26p2[ViewedMapSizeJ*26+1];
		   int Mulx7[ViewedMapSizeI*7+1];
		   int Mulx7p17[ViewedMapSizeI*7+1];
		   
class ENGINE_DLL tInfantry : public tUnit
{
public:
	// ip, jp –  координаты солдата на карте
	tInfantry(int ip, int jp,BYTE whose);
	virtual ~tInfantry();
	BYTE GetType(){return UNITTYPE_INFANTRY;}// Возвращает тип объекта - пехота 
	UINT GetRad(){return FRadius;}//радиус стрельбы
	void Process(tUnit* pUnit);	// Функции обработки
	BOOL Move();
	void Fire();
	//void Blit();
	UINT FRadius;
	BYTE PassCounter;
};

class ENGINE_DLL tGunTurret : public tUnit
{
public:
	// ip, jp – координаты туриэли на карте
	tGunTurret(int ip, int jp,BYTE whose);
	virtual ~tGunTurret();
	BYTE GetType(){return UNITTYPE_TURRET;}// Возвращает тип объекта - туриэль 
	UINT GetRad(){return FRadius;}//радиус стрельбы
	void Process(tUnit* pUnit);	// Функции обработки
	BOOL Move();
	void Fire();
	//void Blit();
	UINT FRadius;
};

class ENGINE_DLL tBarraks : public tUnit
{
public:
	// ip, jp – координаты туриэли на карте
	tBarraks(int ip, int jp,BYTE whose);
	virtual ~tBarraks();
	BYTE GetType(){return UNITTYPE_BARRAKS;}// Возвращает тип объекта - бараки 
	UINT GetRad(){return FRadius;}//радиус стрельбы
	void Process(tUnit* pUnit);	// Функции обработки
	BOOL Move();
	//void Blit();
	UINT FRadius;
};

class tExplosion : public tUnit
{
public:
	tExplosion(int ip, int jp,int MnDi,int MxDi); 
	virtual ~tExplosion();
	BYTE GetType() { return UNITTYPE_MEXPLOSION; }
	UINT GetRad(){return FRadius;}//радиус поражения
	void Process(tUnit* pUnit);	// Функции обработки
	BOOL Move();
	UINT FRadius;
};

class tRocket : public tUnit
{
public:
	tRocket(INDEX start,INDEX target,int MnDi,int MxDi); 
	virtual ~tRocket();
	BYTE GetType() { return UNITTYPE_ROCKET; }
	void Process(tUnit* pUnit);	// Функции обработки
	BOOL Move();
	int Xl,Yl;
	int max_pr;
};


class ENGINE_DLL tEngine : public tDirectInput,
                           public tMusic
{
public:
	tEngine(void);
	virtual ~tEngine(void);
	void InitEngine(HINSTANCE hCurrentInst,int nCmdShow);
	void RunEngine(int MSI,int MSJ);
	void Update(void);
    void SetEngineThread(void (*thread)(void));
    void ReleaseEngine();
	BYTE BlitChar(int x,int y,char chr,BYTE nFontSurf);
	int BlitString(int x,int y,char chr[],BYTE nFontSurf);
protected:
	void InitDX();
	void InitGame();
	void InitPath();
	void ProcessMsg();
    void (*m_thread)(void);
	int ScrlI;
	int ScrlJ;
	tUnitListIterator UnitLI;
	tUnitListIterator UnitLI2;
	tRectUnitListIterator RectUnitLI;
	tRectListIterator RectLI;
};

#endif _ENGINE_H_
