#ifndef _TFILE_H_
#define _TFILE_H_

#include "..\tError\tError.h"

enum {
    TFILENEW = 0x00000001, // ������� ����� ����
    TFILEREAD = 0x00000002, // ������� ��� ������
    TFILEWRITE = 0x00000004, // ������� ��� ������
    TFILETEXT = 0x00000008, // ������� ��� �����
    TFILEBINARY = 0x00000010 // ������� ��� �������� ����
};
/*--------------------------------------------------------------
 tFile

 ����� �����
--------------------------------------------------------------*/
class ENGINE_DLL tFile 
{
public:
    tFile();
    virtual ~tFile();
    void OpenLogFile(const char* name);
	virtual void LogMessage(const char* message ...);
    void CloseLogFile(void);
protected:
    FILE* m_file; // ��������� �� ����
    string m_fileName; // ��� �����
    int m_fileFlags; // ����� �������� �����
    void OpenFile(const char* name,int flags = TFILEREAD|TFILETEXT);
    void CloseFile(void);
};

#endif _TFILE_H_