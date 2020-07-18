#include "stdafx.h"
#include "resource.h" //for IDC_CTRLLIST
#include "TopPriority.h"

#pragma once

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define INFO_BUFFER_SIZE 512

static TCHAR const* PRIORITY_DESC0 = "The highest priority is ";
static TCHAR const* PRIORITY_DESC1 = "The most important event is ";
TCHAR const* EVENT00 = "TeamViewer Log File";
TCHAR const* EVENT01 = "Available Disk space";
TCHAR const* EVENT02 = "TeamViewer UI Process";

void TopPriority::UpdateMostImportantEvent(HWND hWnd)
{
	LVITEM LVItem0;
	LVITEM LVItem1;
	LVITEM LVItem2;
	LVItem0.mask = LVIF_TEXT;
	LVItem1.mask = LVIF_TEXT;
	LVItem2.mask = LVIF_TEXT;
	LVItem0.iSubItem = 2; //column
	LVItem1.iSubItem = 2; //column
	LVItem2.iSubItem = 2; //column
	LVItem0.cchTextMax = INFO_BUFFER_SIZE;
	LVItem1.cchTextMax = INFO_BUFFER_SIZE;
	LVItem2.cchTextMax = INFO_BUFFER_SIZE;
	char priority0[INFO_BUFFER_SIZE];
	char priority1[INFO_BUFFER_SIZE];
	char priority2[INFO_BUFFER_SIZE];
	LVItem0.pszText = priority0;
	LVItem1.pszText = priority1;
	LVItem2.pszText = priority2;
	int iterWhileLoop = 0;

	int mostImportantEventMonitor = 0; //control if there's a change in the priorityID (value = 0 or 1)
	int priorityID = 0;
	int priorityIDPast = 0;
	int priorityMax = 0;
	int priorityMaxPast = 0;

	while (m_RunningMainWindow)
	{
		//Get text from List View table
		SendDlgItemMessageA(hWnd, IDC_CTRLLIST, LVM_GETITEMTEXT, 0, (LPARAM)&LVItem0); //row 0
		SendDlgItemMessageA(hWnd, IDC_CTRLLIST, LVM_GETITEMTEXT, 1, (LPARAM)&LVItem1); //row 1
		SendDlgItemMessageA(hWnd, IDC_CTRLLIST, LVM_GETITEMTEXT, 2, (LPARAM)&LVItem2); //row 2

		//Convert string to int
		int priority0Int = std::atoi(LVItem0.pszText);
		int priority1Int = std::atoi(LVItem1.pszText);
		int priority2Int = std::atoi(LVItem2.pszText);

		int priorityMax = max(max(priority0Int, priority1Int), priority2Int);
		char const* eventDescription;

		if (priorityMax == priority0Int)
		{
			priorityID = 0; //index of the row with max value
			eventDescription = EVENT00;
		}
		if (priorityMax == priority1Int)
		{
			priorityID = 1; //index of the row with max value
			eventDescription = EVENT01;
		}
		if (priorityMax == priority2Int)
		{
			priorityID = 2; //index of the row with max value
			eventDescription = EVENT02;
		}
		
		//Update ListBox -------------------------------------------------------------
		int priorityMaxGap = priorityMax - priorityMaxPast;
		int priorityIDGap = priorityID - priorityIDPast;

		if (priorityMaxGap != 0 || priorityIDGap != 0 || iterWhileLoop < 5) // there's a change in the data and first update
		{
			//Convert int to string
			std::string s = std::to_string(priorityMax); //value
			char const* pChar = s.c_str();

			//Concatenate string
			char result0[INFO_BUFFER_SIZE];
			strcpy(result0, PRIORITY_DESC0);
			strcat(result0, pChar);
			char result1[INFO_BUFFER_SIZE];
			strcpy(result1, PRIORITY_DESC1);
			strcat(result1, eventDescription);

			SendDlgItemMessageA(hWnd, IDC_LISTBOX1, LB_DELETESTRING, 0, 0);
			SendDlgItemMessageA(hWnd, IDC_LISTBOX1, LB_DELETESTRING, 0, 0);
			SendDlgItemMessageA(hWnd, IDC_LISTBOX1, LB_INSERTSTRING, -1, (LPARAM)result0);
			SendDlgItemMessageA(hWnd, IDC_LISTBOX1, LB_INSERTSTRING, -1, (LPARAM)result1);
		}

		priorityMaxPast = priorityMax; //save for next iteration
		priorityIDPast = priorityID; //save for next iteration
		iterWhileLoop ++;
		
		Sleep(SLEEP_TIME); //ms
	}//end of loop
}

void TopPriority::StartButton()
{
	
}

void TopPriority::StopButton()
{
	
}