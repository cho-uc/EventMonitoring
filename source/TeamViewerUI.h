/*
TeamViewerUI.h
*/

#pragma once

#include "stdafx.h"
#include "BaseModel.h"

#define INFO_BUFFER_SIZE 256

class TeamViewerUI : public BaseModel
{
public:    
	void UpdateMainWindowTVUIStatus(HWND hWnd);
	void StartButton() override;
	void StopButton() override;

private:
	bool m_RunningTeamViewerUI = true;

};