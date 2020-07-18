#pragma once
#include "stdafx.h"
#include "resource.h" //for IDC_CTRLLIST
#include "DiskSpaceInfo.h"

#define INFO_BUFFER_SIZE 512

int DISK_SPACE_LIMIT1 = 10; //MB, avoid conversion to unsigned DWORD since gap can be negative value
int DISK_SPACE_LIMIT2 = 100; //MB
int DISK_SPACE_LIMIT3 = 1000; //MB

namespace{
std::vector< std::tuple<wchar_t*, std::wstring, long long> > GetDiskInfo()
{
    DWORD cchBuffer;
    wchar_t* driveStrings(L"C:\\"); //only check C drive
    UINT driveType;
    std::wstring driveTypeString;
    ULARGE_INTEGER freeSpace; //in Bytes
    long long freeSpaceMB; //in Mega Bytes
    std::vector< std::tuple<wchar_t*, std::wstring, long long> > diskInfo;
    
    // Dump drive information
    driveType = GetDriveTypeW(driveStrings);
    GetDiskFreeSpaceExW(driveStrings, &freeSpace, NULL, NULL);

    switch (driveType)
    {
        case DRIVE_FIXED:
            driveTypeString = L"Hard disk";
            break;

        case DRIVE_CDROM:
            driveTypeString = L"CD/DVD";
            break;

        case DRIVE_REMOVABLE:
            driveTypeString = L"Removable";
            break;

        case DRIVE_REMOTE:
            driveTypeString = L"Network";
            break;

        default:
            driveTypeString = L"Unknown";
            break;
    }

    freeSpaceMB = freeSpace.QuadPart / 1024 / 1024;
    diskInfo.push_back({ driveStrings,driveTypeString,freeSpaceMB });

    return diskInfo;
}

std::vector<int> UpdateDiskSpaceStatus(const int diskSpaceCPast)
{
    std::vector<int> diskSpaceStatusArray = { 0, 0 }; //value, priority
    int diskSpacePriority = 0;
    std::vector< std::tuple<wchar_t*, std::wstring, long long> >diskInfo = GetDiskInfo();
    long long diskSpaceC = std::get<2>(diskInfo[0]); //get only from C drive

    //Update Priority--------------------------------------------------------------

    int diskSpaceGap = diskSpaceC - diskSpaceCPast;

    if (diskSpaceGap <= DISK_SPACE_LIMIT1)
    {
        diskSpacePriority = 1;
    }

    if ((diskSpaceGap > DISK_SPACE_LIMIT2) && (diskSpaceGap <= DISK_SPACE_LIMIT3))
    {
        diskSpacePriority = 3;
    }

    if (diskSpaceGap > DISK_SPACE_LIMIT3)
    {
        diskSpacePriority = 9;
    }

    diskSpaceStatusArray[0] = diskSpaceC;
    diskSpaceStatusArray[1] = diskSpacePriority;
    return diskSpaceStatusArray;
}
}//end of namespace

void DiskSpaceInfo::UpdateMainWindowDiskSpace(HWND hWnd)
{
    int diskSpaceCPast = 0;
    std::vector<int> diskSpaceStatusArray = UpdateDiskSpaceStatus(diskSpaceCPast); //value, priority
    diskSpaceCPast = diskSpaceStatusArray[0]; //initial value, before going into infinite loop
    int diskSpaceGap = 0;
    int iterWhileLoop = 0;
    while (m_RunningMainWindow)
    {
        while (m_RunningDiskSpaceInfo)
        {
            diskSpaceStatusArray = UpdateDiskSpaceStatus(diskSpaceCPast);
            diskSpaceGap = diskSpaceStatusArray[0] - diskSpaceCPast;

            if (diskSpaceGap != 0 || iterWhileLoop < 1) // there's a change in the data and first update
            {
                LVITEM lvitem;
                char stringMB[INFO_BUFFER_SIZE] = " MB";

                lvitem.mask = LVIF_TEXT;
                lvitem.iItem = 1; //row
                lvitem.iSubItem = 1; //column

                //Convert int to string
                std::string s = std::to_string(diskSpaceStatusArray[0]); //value
                char const* pChar = s.c_str();

                //Concatenate string
                char result[INFO_BUFFER_SIZE];
                strcpy(result, pChar);
                strcat(result, stringMB);

                lvitem.pszText = (LPSTR)result;
                SendDlgItemMessageA(hWnd, IDC_CTRLLIST, LVM_SETITEM, 0, (LPARAM)&lvitem);

                //-----------------------------
                LVITEM lvitem2;
                lvitem2.mask = LVIF_TEXT;
                lvitem2.iItem = 1; //row
                lvitem2.iSubItem = 2; //column

                //Convert int to string
                std::string s2 = std::to_string(diskSpaceStatusArray[1]); //priority
                char const* pChar2 = s2.c_str();

                lvitem2.pszText = (LPSTR)pChar2;
                SendDlgItemMessageA(hWnd, IDC_CTRLLIST, LVM_SETITEM, 0, (LPARAM)&lvitem2);
            }
            diskSpaceCPast = diskSpaceStatusArray[0]; //save for next iteration
            iterWhileLoop = 1;

            Sleep(SLEEP_TIME); //ms
        }// end of inner loop
    }// end of outer loop
}

void DiskSpaceInfo::StartButton()
{
    m_RunningDiskSpaceInfo = true;
}

void DiskSpaceInfo::StopButton()
{
    m_RunningDiskSpaceInfo = false;
}