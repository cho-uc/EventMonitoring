#include "stdafx.h"
#include "MainWindow.h"

static TCHAR const* COL_HEADER_EVENT_NAME = "Event Name";
static TCHAR const* COL_HEADER_CURRENT_VALUE = "Current Value";
static TCHAR const* COL_HEADER_PRIORITY = "Priority";
static TCHAR const* COL_HEADER_STATUS = "Status";

static TCHAR const* STATUS_DESC0 = "Running";
static TCHAR const* STATUS_DESC1 = "Stopped";

static TCHAR const* EVENT0 = "TeamViewer Log File";
static TCHAR const* EVENT1 = "Available Disk space";
static TCHAR const* EVENT2 = "TeamViewer UI Process";
static TCHAR const* EVENT0_DESC0 = "Monitor the size of the TeamViewer log file";
static TCHAR const* EVENT0_DESC1 = "    - 10 KB, Priority = 2";
static TCHAR const* EVENT0_DESC2 = "    - 100 KB,  Priority = 6";
static TCHAR const* EVENT0_DESC3 = "    - > 500 KB,  Priority = 10";
static TCHAR const* EVENT1_DESC0 = "Monitor the availability of disk space";
static TCHAR const* EVENT1_DESC1 = "    - 10 MB, Priority = 1";
static TCHAR const* EVENT1_DESC2 = "    - 100 MB,  Priority = 3";
static TCHAR const* EVENT1_DESC3 = "    - > 1 GB,  Priority = 9";
static TCHAR const* EVENT2_DESC0 = "Monitor TeamViewer UI process";
static TCHAR const* EVENT2_DESC1 = "    - UI process is started, Priority = 1";
static TCHAR const* EVENT2_DESC2 = "    - UI process is terminated, Priority = 10";
static TCHAR const* EVENT2_DESC3 = "";

DWORD COL_WIDTH = 130;

MainWindow::MainWindow()
{
	
}

void MainWindow::SetMember(TVLogFile* pTVLogFile, DiskSpaceInfo* pdiskSpaceInfo, 
	TeamViewerUI* pTeamViewerUI, TopPriority* pTopPriority)
{
	m_TVLogFile = pTVLogFile;
	m_diskSpaceInfo = pdiskSpaceInfo;
	m_TeamViewerUI = pTeamViewerUI;
	m_topPriority = pTopPriority;
	
};

LRESULT MainWindow::OnInit(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_ListView.Attach(GetDlgItem(IDC_CTRLLIST));
	m_ListBox1.Attach(GetDlgItem(IDC_LISTBOX1));
	m_ListBox2.Attach(GetDlgItem(IDC_LISTBOX2));

	m_ListView.InsertColumn(0, COL_HEADER_EVENT_NAME, LVCFMT_CENTER, COL_WIDTH);
	m_ListView.InsertColumn(1, COL_HEADER_CURRENT_VALUE, LVCFMT_CENTER, COL_WIDTH);
	m_ListView.InsertColumn(2, COL_HEADER_PRIORITY, LVCFMT_CENTER, COL_WIDTH);
	m_ListView.InsertColumn(3, COL_HEADER_STATUS, LVCFMT_CENTER, COL_WIDTH);

	m_ListView.InsertItem(0, EVENT0);
	m_ListView.InsertItem(1, EVENT1);
	m_ListView.InsertItem(2, EVENT2);	

	m_ListView.AddItem(0, 3, STATUS_DESC0);
	m_ListView.AddItem(1, 3, STATUS_DESC0);
	m_ListView.AddItem(2, 3, STATUS_DESC0);	

	return 0;
}

LRESULT MainWindow::OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_topPriority->Terminate();
	m_TVLogFile->StopButton();
	m_diskSpaceInfo->StopButton();
	m_TeamViewerUI->StopButton();
	m_TVLogFile->Terminate();
	m_diskSpaceInfo->Terminate();
	m_TeamViewerUI->Terminate();

	DestroyWindow();
	return 0;
}

LRESULT MainWindow::OnCloseButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_topPriority->Terminate();
	m_TVLogFile->StopButton();
	m_diskSpaceInfo->StopButton();
	m_TeamViewerUI->StopButton();
	m_TVLogFile->Terminate();
	m_diskSpaceInfo->Terminate();
	m_TeamViewerUI->Terminate();

	DestroyWindow();
	return 0;
}

LRESULT MainWindow::OnDestroy(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0);
	return 0;
}

LRESULT MainWindow::OnNMClickCtrllist(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	LV_ITEM lv;
	::memset(&lv, 0, sizeof(LV_ITEM));
	lv.iItem = m_ListView.GetNextItem(-1, LVNI_SELECTED);
	
	if (lv.iItem == 0)
	{
		m_ListBox2.DeleteString(0); m_ListBox2.DeleteString(0);
		m_ListBox2.DeleteString(0); m_ListBox2.DeleteString(0);
		m_ListBox2.AddString(EVENT0_DESC0);
		m_ListBox2.AddString(EVENT0_DESC1);
		m_ListBox2.AddString(EVENT0_DESC2);
		m_ListBox2.AddString(EVENT0_DESC3);

	}
	if (lv.iItem == 1)
	{
		m_ListBox2.DeleteString(0); m_ListBox2.DeleteString(0);
		m_ListBox2.DeleteString(0); m_ListBox2.DeleteString(0);
		m_ListBox2.AddString(EVENT1_DESC0);
		m_ListBox2.AddString(EVENT1_DESC1);
		m_ListBox2.AddString(EVENT1_DESC2);
		m_ListBox2.AddString(EVENT1_DESC3);

	}
	if (lv.iItem == 2)
	{
		m_ListBox2.DeleteString(0); m_ListBox2.DeleteString(0);
		m_ListBox2.DeleteString(0); m_ListBox2.DeleteString(0);
		m_ListBox2.AddString(EVENT2_DESC0);
		m_ListBox2.AddString(EVENT2_DESC1);
		m_ListBox2.AddString(EVENT2_DESC2);
		m_ListBox2.AddString(EVENT2_DESC3);

	}

	return 0;
}

LRESULT MainWindow::OnBnClickedStart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	LV_ITEM lv;
	::memset(&lv, 0, sizeof(LV_ITEM));
	lv.iItem = m_ListView.GetNextItem(-1, LVNI_SELECTED);
	if (lv.iItem == 0)
	{	
		m_TVLogFile->StartButton();
		m_ListView.AddItem(0, 3, STATUS_DESC0);
	}

	if (lv.iItem == 1)
	{
		m_diskSpaceInfo->StartButton();
		m_ListView.AddItem(1, 3, STATUS_DESC0);
	}
	if (lv.iItem == 2)
	{
		m_TeamViewerUI->StartButton();
		m_ListView.AddItem(2, 3, STATUS_DESC0);
	}

	return 0;
}

LRESULT MainWindow::OnBnClickedStop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	LV_ITEM lv;
	::memset(&lv, 0, sizeof(LV_ITEM));
	lv.iItem = m_ListView.GetNextItem(-1, LVNI_SELECTED);
	if (lv.iItem == 0)
	{		
		m_TVLogFile->StopButton();
		m_ListView.AddItem(0, 3, STATUS_DESC1); 
	}

	if (lv.iItem == 1)
	{
		m_diskSpaceInfo->StopButton();
		m_ListView.AddItem(1, 3, STATUS_DESC1);
	}
	if (lv.iItem == 2)
	{
		m_TeamViewerUI->StopButton();
		m_ListView.AddItem(2, 3, STATUS_DESC1);
	}

	return 0;
}