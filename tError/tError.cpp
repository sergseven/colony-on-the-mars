#include "tError.h"

/*--------------------------------------------------------------
 tError::tError()

 Конструктор, инициализирущий ошибку
--------------------------------------------------------------*/
tError::tError(const char* file,int line,const char* history,const char* message ...)
{
    char buffer[4096];

    va_list list;
    va_start(list,message);
    vsprintf(buffer,message,list);
    va_end(list);

    m_errorFile = file;
    m_errorLine = line;
    m_errorHistory = history;
    m_errorMessage = buffer;
}

/*--------------------------------------------------------------
 tError::~tError()

 Деструктор
--------------------------------------------------------------*/
tError::~tError()
{
    m_errorFile.erase();
    m_errorHistory.erase();
    m_errorMessage.erase();
}

/*--------------------------------------------------------------
 tError::GetErrorMessage()

 Сформировать и передать сообщение об ошибке
--------------------------------------------------------------*/
const char* tError::GetErrorMessage(void)
{
    char buffer[4096];

    // Формирование сообщения об ошибке
    sprintf(buffer,"%s\n[File:%s][Line:%d]\n\nHistory: %s",
            m_errorMessage.c_str(),
            m_errorFile.c_str(),
            m_errorLine,
            m_errorHistory.c_str());
    m_errorMessage = buffer;

    // Передать сообщение об ошибке
    return m_errorMessage.c_str();
}

/*--------------------------------------------------------------
 tError::AddErrorHistory()

 Добавить в историю ошибки
--------------------------------------------------------------*/
void tError::AddErrorHistory(const char* history ...)
{
    char buffer[4096];

    va_list list;
    va_start(list,history);
    vsprintf(buffer,history,list);
    va_end(list);

    // Добавить в историю ошибки
    m_errorHistory += buffer;
}
