#include "tError.h"

/*--------------------------------------------------------------
 tError::tError()

 �����������, ��������������� ������
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

 ����������
--------------------------------------------------------------*/
tError::~tError()
{
    m_errorFile.erase();
    m_errorHistory.erase();
    m_errorMessage.erase();
}

/*--------------------------------------------------------------
 tError::GetErrorMessage()

 ������������ � �������� ��������� �� ������
--------------------------------------------------------------*/
const char* tError::GetErrorMessage(void)
{
    char buffer[4096];

    // ������������ ��������� �� ������
    sprintf(buffer,"%s\n[File:%s][Line:%d]\n\nHistory: %s",
            m_errorMessage.c_str(),
            m_errorFile.c_str(),
            m_errorLine,
            m_errorHistory.c_str());
    m_errorMessage = buffer;

    // �������� ��������� �� ������
    return m_errorMessage.c_str();
}

/*--------------------------------------------------------------
 tError::AddErrorHistory()

 �������� � ������� ������
--------------------------------------------------------------*/
void tError::AddErrorHistory(const char* history ...)
{
    char buffer[4096];

    va_list list;
    va_start(list,history);
    vsprintf(buffer,history,list);
    va_end(list);

    // �������� � ������� ������
    m_errorHistory += buffer;
}
