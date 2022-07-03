/*--------------------------------------------------------------
 tError

 ����� ����������� ������
--------------------------------------------------------------*/
#ifndef _TERROR_H_
#define _TERROR_H_

#include "..\common.h"

class ENGINE_DLL tError
{
public:
    tError(const char* file,int line,const char* history,const char* message ...);
    virtual ~tError();
    const char* GetErrorMessage(void);
    void AddErrorHistory(const char* history ...);
protected:
    string m_errorFile; // ��� �����, ��� ��������� ������
    int m_errorLine; // ������, ��� ��������� ������
    string m_errorHistory; // ������� ������
    string m_errorMessage; // ��������� �� ������
};

#endif _TERROR_H_