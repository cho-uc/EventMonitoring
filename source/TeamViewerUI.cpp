#pragma once
#include "stdafx.h"
#include "resource.h" //for IDC_CTRLLIST
#include "TeamViewerUI.h"

const wchar_t* UI_BINFILE = L"TeamViewer.exe"; //no need to add the full path

namespace{
bool IsProcessRunning(const wchar_t* processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry)) {
        while (Process32Next(snapshot, &entry))
        {
            //Convert char to wchar_t
            wchar_t  entry2[INFO_BUFFER_SIZE];
            MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, entry.szExeFile, -1, entry2, INFO_BUFFER_SIZE);
            //Check process
            if (!_wcsicmp(entry2, processName))
            {
                exists = true;
            }
        }
    }
    CloseHandle(snapshot);
    return exists;
}

std::vector<int> UpdateTVUIStatus(const int TVUIStatusBefore)
{
	std::vector<int> TVUIProcessArray = { 0, 0 }; //value, priority
	bool UIProcessIsRunning = 0;
	int TVUIPriority = 0;
	UIProcessIsRunning = IsProcessRunning(UI_BINFILE);

	//Update Priority--------------------------------------------------------------
	int TVUIProcessGap = (int)UIProcessIsRunning - TVUIStatusBefore;

	if (TVUIProcessGap == 1) //TV UI is starting 
	{
		TVUIPriority = 1;
	}

	if (TVUIProcessGap == -1) //TV UI is terminated
	{
		TVUIPriority = 10;
	}

	else
	{
		TVUIPriority = 0;
	}

	TVUIProcessArray[0] = UIProcessIsRunning;
	TVUIProcessArray[1] = TVUIPriority;

	return TVUIProcessArray;
}
} //end of namespace

void TeamViewerUI::UpdateMainWindowTVUIStatus(HWND hWnd)
{
	int UIProcessIsRunningPast = 0;
	std::vector<int> TVUIProcessArray = UpdateTVUIStatus(UIProcessIsRunningPast); //value, priority
	UIProcessIsRunningPast = TVUIProcessArray[0]; //initial value, before going into infinite loop
	int TVUIProcessGap = 0;
	int iterWhileLoop = 0;

	while (m_RunningMainWindow)
	{
		while (m_RunningTeamViewerUI)
		{
			TVUIProcessArray = UpdateTVUIStatus(UIProcessIsRunningPast); //value, priority
			TVUIProcessGap = TVUIProcessArray[0] - UIProcessIsRunningPast;

			if (TVUIProcessGap != 0 || iterWhileLoop < 1) // there's a change in the data and first update
			{
				LVITEM lvitem;
				lvitem.mask = LVIF_TEXT;
				lvitem.iItem = 2; //row
				lvitem.iSubItem = 1; //column

				//Convert int to string
				std::string s = std::to_string(TVUIProcessArray[0]); //value
				char const* pChar = s.c_str();

				lvitem.pszText = (LPSTR)pChar;
				SendDlgItemMessageA(hWnd, IDC_CTRLLIST, LVM_SETITEM, 0, (LPARAM)&lvitem);

				//-----------------------------
				LVITEM lvitem2;
				lvitem2.mask = LVIF_TEXT;
				lvitem2.iItem = 2; //row
				lvitem2.iSubItem = 2; //column

				//Convert int to string
				std::string s2 = std::to_string(TVUIProcessArray[1]); //priority
				char const* pChar2 = s2.c_str();

				lvitem2.pszText = (LPSTR)pChar2;
				SendDlgItemMessageA(hWnd, IDC_CTRLLIST, LVM_SETITEM, 0, (LPARAM)&lvitem2);
			}
			UIProcessIsRunningPast = TVUIProcessArray[0]; //save for next iteration
			iterWhileLoop = 1;
			Sleep(SLEEP_TIME); //ms
		}// end of inner loop

	}//end of outer loop

}

void TeamViewerUI::StartButton()
{
	m_RunningTeamViewerUI = true;
}

void TeamViewerUI::StopButton()
{
	m_RunningTeamViewerUI = false;
}