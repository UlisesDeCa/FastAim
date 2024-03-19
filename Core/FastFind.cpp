#include "FastFind.h"
#include "../Utilities/User.h"
#include <iostream>

FastFind::FastFind(User* user)
{
    std::cout << "[FastFind] Starting\n";

    m_User = user;

    // Dinamically load FastFind functions
    HINSTANCE hGetProcIDDLL = LoadLibrary(L".\\FastFind64.dll");

    if (!hGetProcIDDLL) { std::cout << "Could not load the dll" << std::endl; return; }

    m_SnapShot = (f_SnapShot)GetProcAddress(hGetProcIDDLL, "SnapShot");
    m_GenericColorSearch = (f_GenericColorSearch)GetProcAddress(hGetProcIDDLL, "GenericColorSearch");
    //m_SetHWnd = (f_SetHWnd)GetProcAddress(hGetProcIDDLL, "SetHWnd");
    //m_AddColor = (f_AddColor)GetProcAddress(hGetProcIDDLL, "AddColor");
    //m_GetPixel = (f_GetPixel)GetProcAddress(hGetProcIDDLL, "FFGetPixel");
    //m_AddExcludedArea = (f_AddExcludedArea)GetProcAddress(hGetProcIDDLL, "AddExcludedArea");

    if (!m_SnapShot) { std::cout << "Could not locate SnapShot" << std::endl; return; }
    if (!m_GenericColorSearch) { std::cout << "Could not locate GenericColorSearch" << std::endl; return; }
    //if (!m_SetHWnd) { std::cout << "Could not locate SetHWnd" << std::endl; return; }
    //if (!m_AddColor) { std::cout << "Could not locate AddColor" << std::endl; return; }
    //if (!m_GetPixel) { std::cout << "Could not locate GetPixel" << std::endl; return; }
    //if (!m_AddExcludedArea) { std::cout << "Could not locate AddExcludedArea" << std::endl; return; }

    std::cout << "[FastFind] Started\n";

}

const int MONITOR_CENTER_X = GetSystemMetrics(SM_CXSCREEN) / 2;
const int MONITOR_CENTER_Y = GetSystemMetrics(SM_CYSCREEN) / 2;

const int FastFind::ScreenShoot()
{
    // Only screenshot inside the FOV
    return m_SnapShot(
        MONITOR_CENTER_X - m_User->Aimbot.fov / 2, 
        MONITOR_CENTER_Y - m_User->Aimbot.fov / 2,
        MONITOR_CENTER_X + m_User->Aimbot.fov / 2,
        MONITOR_CENTER_Y + m_User->Aimbot.fov / 2,
        1);
}

const int FastFind::ColorSearch(int& x, int& y)
{
    int minMatch = m_User->SearchSettings.minMatch;

    // Found
    if (m_GenericColorSearch(m_User->SearchSettings.sizeSearch, minMatch, x, y, m_User->SearchSettings.color, m_User->SearchSettings.colorVariation, 1))
        return 1; 

    // Not found, we reset start search position
    else  
    { 
        x = m_User->SearchSettings.prefX;
        y = m_User->SearchSettings.prefY;
        return 0; 
    }
}

FastFind::~FastFind()
{
	FreeLibrary(m_hGetProcIDDLL);
}