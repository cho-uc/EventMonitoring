/*
DiskSpaceInfo.h
*/
#pragma once
#include "BaseModel.h"

class TopPriority: public BaseModel
{
public:    
    void UpdateMostImportantEvent(HWND handle);
	void StartButton() override;
	void StopButton() override;
	
};