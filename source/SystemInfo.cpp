// SystemInfo.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "MainWindow.h"
#include "TopPriority.h"
#include "TVLogFile.h"
#include "DiskSpaceInfo.h"
#include "TeamViewerUI.h"

// Global Variables:
#define MAX_LOADSTRING 100

HWND hWnd;

HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
//-------------Main Program-------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// init common controls to allow usage!
	InitCommonControls();

	TVLogFile tvlogFileInstance;
	DiskSpaceInfo diskSpaceInfoInstance;
	TeamViewerUI TeamViewerUIInstance;
	TopPriority topPriorityInstance;

	MainWindow mainwindow;
	mainwindow.SetMember(&tvlogFileInstance, &diskSpaceInfoInstance, &TeamViewerUIInstance, &topPriorityInstance);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SYSTEMINFO, szWindowClass, MAX_LOADSTRING);

	// Perform application initialization:
	hInst = hInstance;
	hWnd = mainwindow.Create(NULL, NULL);

	auto TVLogFileThread = std::thread(&TVLogFile::UpdateMainWindowTVLogFile, &tvlogFileInstance, hWnd);
	auto diskSpaceInfoThread = std::thread(&DiskSpaceInfo::UpdateMainWindowDiskSpace, &diskSpaceInfoInstance, hWnd);
	auto TeamViewerUIThread = std::thread(&TeamViewerUI::UpdateMainWindowTVUIStatus, &TeamViewerUIInstance, hWnd);
	auto topPriorityThread = std::thread(&TopPriority::UpdateMostImportantEvent, &topPriorityInstance, hWnd);
	
	int i = GetLastError();
	ShowWindow(hWnd, nCmdShow);
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SYSTEMINFO));

	//---------------------------------------
	// Main message loop;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//End inner while loop
	tvlogFileInstance.StopButton();
	diskSpaceInfoInstance.StopButton();
	TeamViewerUIInstance.StopButton();
	//End outer while loop
	tvlogFileInstance.Terminate(); 
	diskSpaceInfoInstance.Terminate();
	TeamViewerUIInstance.Terminate();
	topPriorityInstance.Terminate();
	
	TVLogFileThread.join();
	diskSpaceInfoThread.join();
	TeamViewerUIThread.join();
	topPriorityThread.join();

	return (int)msg.wParam;
}