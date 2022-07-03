/*--------------------------------------------------------------
 tError

 Класс обработчика ошибок
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
    string m_errorFile; // Имя файла, где произошла ошибка
    int m_errorLine; // Строка, где произошла ошибка
    string m_errorHistory; // История ошибки
    string m_errorMessage; // Сообщение об ошибке
};

#endif _TERROR_H_