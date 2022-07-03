/*---------------------- C++ source file -----------------------
 Project: tEngine

 Класс файла
--------------------------------------------------------------*/

#include "tFile.h"

/*--------------------------------------------------------------
 tFile::tFile()

 Конструктор по умолчанию
--------------------------------------------------------------*/
tFile::tFile()
{
    m_file = NULL;
}

/*--------------------------------------------------------------
 tFile::~tFile()

 Деструктор
--------------------------------------------------------------*/
tFile::~tFile()
{
  //   Закрыть файл
    if(m_file)
        if(fclose(m_file))
            throw tError(__FILE__,__LINE__,"tFile::~tFile",
                         "Не могу закрыть файл! / file - %s / flags - 0x%x",m_fileName,m_fileFlags);
		m_fileName.erase();
}

/*--------------------------------------------------------------
 tFile::OpenFile()

 Открытие файла
--------------------------------------------------------------*/
void tFile::OpenFile(const char* name,int flags)
{
    string openFlags;

    try
    {
        // Закрыть файл
        tFile::CloseFile();
    }
    catch(tError &error)
    {
        error.AddErrorHistory(" <-tFile::OpenFile");
        throw;
	}

    // Копируем имя файла
    m_fileName = name;
    // Копируем флаги
    m_fileFlags = flags;

    // Формирование флагов для открытия
    if(m_fileFlags&TFILEREAD)
        openFlags = "r";
    if(m_fileFlags&TFILEWRITE)
        openFlags = "r+";
    if((m_fileFlags&TFILEWRITE)&&(m_fileFlags&TFILENEW))
        openFlags = "w";
    if((m_fileFlags&TFILEREAD)&&(m_fileFlags&TFILENEW))
        openFlags = "w+";
    if(m_fileFlags&TFILEBINARY)
        openFlags += "b";
    else
        openFlags += "t";

	// Открытие файла
    m_file = fopen(m_fileName.c_str(),openFlags.c_str());
    if(!m_file)
        throw tError(__FILE__,__LINE__,"tFile::OpenFile",
                     "Не могу открыть файл! / file - %s / flags - 0x%x",m_fileName.c_str(),m_fileFlags);

}

/*--------------------------------------------------------------
 tFile::CloseFile()

 Закрытие файла
--------------------------------------------------------------*/
void tFile::CloseFile(void)
{
    if(m_file)
    {
        if(fclose(m_file))
            throw tError(__FILE__,__LINE__,"tFile::CloseFile",
                         "Не могу закрыть файл! / file - %s / flags - 0x%x",m_fileName,m_fileFlags);
        m_file = NULL;
        m_fileName.erase();
    }
}

/*--------------------------------------------------------------
 tLogFile::OpenLogFile()

 Открытие log-файла
--------------------------------------------------------------*/
void tFile::OpenLogFile(const char* name)
{
	try
	{
		// Открытие файла
		tFile::OpenFile(name,TFILENEW|TFILEWRITE|TFILETEXT);
	}
    catch(tError &error)
    {
		error.AddErrorHistory(" <-tLogFile::OpenLogFile");
        throw;
    }
    tFile::LogMessage("----------------------- begin log ------------------------------\n");
}

/*--------------------------------------------------------------
 tLogFile::LogMessage()

 Вывести сообщение в log-файл
--------------------------------------------------------------*/
void tFile::LogMessage(const char* message ...)
{
    va_list list;
    va_start(list,message);
    if(!m_file||vfprintf(m_file,message,list)<0)
		throw tError(__FILE__,__LINE__,"tLogFile::LogMessage",
                     "Fail to write to file! / file - %s / flags - 0x%x",m_fileName,m_fileFlags);
    va_end(list);
}

/*--------------------------------------------------------------
 tLogFile::CloseLogFile()

 Закрытие log-файла
--------------------------------------------------------------*/
void tFile::CloseLogFile(void)
{
	tFile::LogMessage("----------------------- end log --------------------------------");
    try
    {
		// Закрытие файла
        tFile::CloseFile();
    }
    catch(tError &error) {
        error.AddErrorHistory(" <-tLogFile::CloseLogFile");
        throw;
    }
}
