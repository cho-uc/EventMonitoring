/* TVLogFile.cpp
*/

#include "stdafx.h"

#include "TVLogFile.h"
#include "resource.h" //for IDC_CTRLLIST

#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif // _UNICODE

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif // _UNICODE

#define INFO_BUFFER_SIZE 512

const char* SOURCE_LOGFILE = "C:\\Program Files (x86)\\TeamViewer\\TeamViewer15_Logfile.log";
DWORD TV_LOG_FILE_LIMIT1 = 10; //KB
DWORD TV_LOG_FILE_LIMIT2 = 100; //KB
DWORD TV_LOG_FILE_LIMIT3 = 500; //KB

namespace
{
size_t GetLogFileSize(const char* str)
{
	size_t file_size = 0;
	struct stat fs = { 0 };
	if (stat((const char*)str, &fs) == 0)
	{
		file_size = fs.st_size;
	}

	return (file_size / 1024); //in KB
}

std::vector<int> UpdateLogFileStatus(const int fileSizeBefore)
{
	int TVLogFileArray[2] = { 0,0 }; //store past and present value of log file
	int TVLogFileGap = 0;
	int logFilePriority = 0;
	std::vector<int> logFileStatusArray{ 0, 0 }; //value, priority

	int fileSize = GetLogFileSize(SOURCE_LOGFILE); //KB
	TVLogFileGap = fileSize - fileSizeBefore;

	//Update Priority--------------------------------------------------------------
	if (TVLogFileGap <= TV_LOG_FILE_LIMIT1)
	{
		logFilePriority = 2;
	}
	if ((TVLogFileGap > TV_LOG_FILE_LIMIT2) && (TVLogFileGap <= TV_LOG_FILE_LIMIT3))
	{
		logFilePriority = 6;
	}
	if (TVLogFileGap > TV_LOG_FILE_LIMIT3)
	{
		logFilePriority = 10;
	}
	//update return value
	logFileStatusArray[0] = fileSize;
	logFileStatusArray[1] = logFilePriority;

	return logFileStatusArray;
}
} // end of namespace

void TVLogFile::UpdateMainWindowTVLogFile(HWND hWnd)
{
	int fileSizePast = 0;
	std::vector<int> logFileStatusArray = UpdateLogFileStatus(fileSizePast); // value, priority
	fileSizePast = logFileStatusArray[0];  //initial value, before going into infinite loop
	int TVLogFileGap = 0;
	int iterWhileLoop = 0;

	
	while (m_RunningMainWindow)
	{
		while (m_RunningTVLogFile)
		{
			logFileStatusArray = UpdateLogFileStatus(fileSizePast);
			TVLogFileGap = logFileStatusArray[0] - fileSizePast;

			if (TVLogFileGap != 0 || iterWhileLoop < 1) // there's a change in the data and first update
			{
				LVITEM lvitem;
				char stringKB[INFO_BUFFER_SIZE] = " KB";

				lvitem.mask = LVIF_TEXT;
				lvitem.iItem = 0; //row
				lvitem.iSubItem = 1; //column

				//Convert int to string
				std::string s = std::to_string(logFileStatusArray[0]);//value
				char const* pChar = s.c_str();

				//Concatenate string
				char result[INFO_BUFFER_SIZE];
				strcpy(result, pChar);
				strcat(result, stringKB);

				lvitem.pszText = (LPSTR)result;
				SendDlgItemMessageA(hWnd, IDC_CTRLLIST, LVM_SETITEM, 0, (LPARAM)&lvitem);

				//-----------------------------
				LVITEM lvitem2;
				lvitem2.mask = LVIF_TEXT;
				lvitem2.iItem = 0; //row
				lvitem2.iSubItem = 2; //column

				//Convert int to string
				std::string s2 = std::to_string(logFileStatusArray[1]); //priority
				char const* pChar2 = s2.c_str();

				lvitem2.pszText = (LPSTR)pChar2;
				SendDlgItemMessageA(hWnd, IDC_CTRLLIST, LVM_SETITEM, 0, (LPARAM)&lvitem2);
			}

			fileSizePast = logFileStatusArray[0]; //save for next iteration
			iterWhileLoop = 1;
			Sleep(SLEEP_TIME);
		}// end of inner loop
	}//end of outer loop
}

void TVLogFile::StartButton()
{
	m_RunningTVLogFile = true;
}

void TVLogFile::StopButton()
{
	m_RunningTVLogFile = false;
}