/*---------------------- C++ source file -----------------------
 Project: tEngine

 ����� �����
--------------------------------------------------------------*/

#include "tFile.h"

/*--------------------------------------------------------------
 tFile::tFile()

 ����������� �� ���������
--------------------------------------------------------------*/
tFile::tFile()
{
    m_file = NULL;
}

/*--------------------------------------------------------------
 tFile::~tFile()

 ����������
--------------------------------------------------------------*/
tFile::~tFile()
{
  //   ������� ����
    if(m_file)
        if(fclose(m_file))
            throw tError(__FILE__,__LINE__,"tFile::~tFile",
                         "�� ���� ������� ����! / file - %s / flags - 0x%x",m_fileName,m_fileFlags);
		m_fileName.erase();
}

/*--------------------------------------------------------------
 tFile::OpenFile()

 �������� �����
--------------------------------------------------------------*/
void tFile::OpenFile(const char* name,int flags)
{
    string openFlags;

    try
    {
        // ������� ����
        tFile::CloseFile();
    }
    catch(tError &error)
    {
        error.AddErrorHistory(" <-tFile::OpenFile");
        throw;
	}

    // �������� ��� �����
    m_fileName = name;
    // �������� �����
    m_fileFlags = flags;

    // ������������ ������ ��� ��������
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

	// �������� �����
    m_file = fopen(m_fileName.c_str(),openFlags.c_str());
    if(!m_file)
        throw tError(__FILE__,__LINE__,"tFile::OpenFile",
                     "�� ���� ������� ����! / file - %s / flags - 0x%x",m_fileName.c_str(),m_fileFlags);

}

/*--------------------------------------------------------------
 tFile::CloseFile()

 �������� �����
--------------------------------------------------------------*/
void tFile::CloseFile(void)
{
    if(m_file)
    {
        if(fclose(m_file))
            throw tError(__FILE__,__LINE__,"tFile::CloseFile",
                         "�� ���� ������� ����! / file - %s / flags - 0x%x",m_fileName,m_fileFlags);
        m_file = NULL;
        m_fileName.erase();
    }
}

/*--------------------------------------------------------------
 tLogFile::OpenLogFile()

 �������� log-�����
--------------------------------------------------------------*/
void tFile::OpenLogFile(const char* name)
{
	try
	{
		// �������� �����
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

 ������� ��������� � log-����
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

 �������� log-�����
--------------------------------------------------------------*/
void tFile::CloseLogFile(void)
{
	tFile::LogMessage("----------------------- end log --------------------------------");
    try
    {
		// �������� �����
        tFile::CloseFile();
    }
    catch(tError &error) {
        error.AddErrorHistory(" <-tLogFile::CloseLogFile");
        throw;
    }
}
