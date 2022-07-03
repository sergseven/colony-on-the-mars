
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

enum{UNITTYPE_UNIT,
	            UNITTYPE_INFANTRY};

class tEngine : public tDirectInput,
                           public tMusic
{
public:
	tEngine(void);
	virtual ~tEngine(void);
	void InitEngine(HINSTANCE hCurrentInst,int nCmdShow);
	void RunEngine();
    void SetEngineThread(void (*thread)(void));
    void ReleaseEngine();
	void InitDD();
	void InitGame();
protected:
    void (*m_thread)(void);

};

class tUnit : public tEngine
{
public:
	tUnit();
	virtual ~tUnit();
	RECT rcRect; // ���������� ������ �������������
	POINT Pos; // �������� ���������� �������
	BOOL bAnim; // ���� �� ��������
	BOOL bDie; // ���� ������� � ������ ����� ����������?
	BYTE Frame; // ������� ����
	BYTE Counter; // ������� ��� ��������
	POINT Action; //���������� �������� ��������
	POINT *PathMass; //������ ��������� ����
	int Whose; //�������������� 
	void Kill() { bDie = TRUE; }
	BOOL Collision(tUnit* pUnit);
	virtual void Blit() = 0;
	virtual BYTE GetType() = 0;
	virtual void Process(tUnit* pUnit) = 0;
	virtual BOOL Move() = 0;
    void FindPath(POINT Start,POINT Finish,
		          POINT *InPathMass);//����� ����  
};

class tInfantry : public tUnit
{
public:
	// x, y � �������� ���������� �������
	tInfantry(int x, int y);
	virtual ~tInfantry();
	// ���������� ��� ������� - ������ 
	BYTE GetType() { return UNITTYPE_INFANTRY; }
	// ������� ���������
	void Process(tUnit* pUnit);
	BOOL Move();
	// ������� ����������
	void Blit();
};

class tField : public tEngine 
{
public:
	tField();
    virtual ~tField();
	//POINT Pos;
	tUnit* pUnit;
	BYTE nSprt;
};

typedef tUnit *LPOBJECT;
typedef std::list<LPOBJECT > MyList; 
typedef std::list<LPOBJECT >::iterator MyListIterator; 

MyList List; // ���������� ������
tField* Field[20][38];//�����
tUnit* pUnit;
int i,j;
RECT rect;
int nIWSurf;
int nABGSurf;

#endif _ENGINE_H_
