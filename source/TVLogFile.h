/*
TVLogFile.h
*/

#pragma once
#include "BaseModel.h"

class TVLogFile final: public BaseModel
{
public:
    virtual ~TVLogFile() override = default;

    void UpdateMainWindowTVLogFile(HWND hWnd);
    void StartButton() override;
    void StopButton() override;

private:
    bool m_RunningTVLogFile{ true };
};