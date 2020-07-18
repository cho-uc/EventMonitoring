/*
DiskSpaceInfo.h
*/

#pragma once
#include "stdafx.h"
#include "BaseModel.h"

class DiskSpaceInfo : public BaseModel
{
public:
    void UpdateMainWindowDiskSpace(HWND hWnd);

    void StartButton() override;
    void StopButton() override;

protected:
    bool m_RunningDiskSpaceInfo = true;
};