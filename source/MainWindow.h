#pragma once
#include "Resource.h"
#include "TopPriority.h"
#include "TVLogFile.h"
#include "DiskSpaceInfo.h"
#include "TeamViewerUI.h"

/**
* This class is the GUI part of the program. It contains a MSG
* map, a DDX map and handles for Buttons, ListViewControls, etc.
*
*/

class MainWindow : public CDialogImpl<MainWindow>
{
public:
	MainWindow();
	enum { IDD = IDD_MAIN_DIALOG };

	BEGIN_MSG_MAP(MainWindow)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInit);
		MESSAGE_HANDLER(WM_CLOSE, OnClose);
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy);
		COMMAND_HANDLER(IDC_CLOSE, BN_CLICKED, OnCloseButtonClick);
		NOTIFY_HANDLER(IDC_CTRLLIST, NM_CLICK, OnNMClickCtrllist);
		COMMAND_HANDLER(IDC_BUTTON_START, BN_CLICKED, OnBnClickedStart);
		COMMAND_HANDLER(IDC_BUTTON_STOP, BN_CLICKED, OnBnClickedStop);

	END_MSG_MAP()

	LRESULT OnInit(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCloseButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnNMClickCtrllist(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnBnClickedStart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedStop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	void SetMember(TVLogFile* pTVLogFile, DiskSpaceInfo* pdiskSpaceInfo,
		TeamViewerUI* pTeamViewerUI, TopPriority* pTopPriority);

private:
	CListViewCtrl m_ListView;
	CListBox m_ListBox1;
	CListBox m_ListBox2;

	IModel* m_TVLogFile;
	IModel* m_diskSpaceInfo;
	IModel* m_TeamViewerUI;
	TopPriority* m_topPriority;
};