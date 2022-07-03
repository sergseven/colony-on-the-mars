#ifndef _TFILE_H_
#define _TFILE_H_

#include "..\tError\tError.h"

enum {
    TFILENEW = 0x00000001, // Создать новый файл
    TFILEREAD = 0x00000002, // Открыть для чтения
    TFILEWRITE = 0x00000004, // Открыть для записи
    TFILETEXT = 0x00000008, // Открыть как текст
    TFILEBINARY = 0x00000010 // Открыть как двоичный файл
};
/*--------------------------------------------------------------
 tFile

 Класс файла
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
    FILE* m_file; // Указатель на файл
    string m_fileName; // Имя файла
    int m_fileFlags; // Флаги открытия файла
    void OpenFile(const char* name,int flags = TFILEREAD|TFILETEXT);
    void CloseFile(void);
};

#endif _TFILE_H_