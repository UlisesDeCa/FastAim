// ColorAimbot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <stdexcept>
#include "Core/IOManagement.h"
#include "Core/FastFind.h"
#include "Core/GUI.h"
#include "Utilities/User.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    User User;

    bool appRunning = true;
    Menu Menu(appRunning, User);
    Sleep(1000);
    User.Data.loadedApp = true; // For an animation and a little bit of time for the Menu thread
    
    FastFind FastFind(&User);
    Interception Mouse;

    const int MONITOR_CENTER_X = GetSystemMetrics(SM_CXSCREEN) / 2;
    const int MONITOR_CENTER_Y = GetSystemMetrics(SM_CYSCREEN) / 2;
    int x = MONITOR_CENTER_X - User.Aimbot.fov / 2 + User.SearchSettings.refX;
    int y = MONITOR_CENTER_Y - User.Aimbot.fov / 2 + User.SearchSettings.refY;

    while (appRunning)
    {
        Sleep(50);
        while (GetAsyncKeyState(User.Binds.aim) & 0x8000)
        {
            if (!FastFind.ScreenShoot()) { std::cerr << "\Screenshot failed"; continue; }
            if (!FastFind.ColorSearch(x, y)) { std::cerr << "\nPixelsearch failed"; continue; }

            // Convert to relative coordinates and apply the most basic smooth ever
            int relX = (x - MONITOR_CENTER_X + User.Aimbot.offsetX) * User.Aimbot.strength;
            int relY = (y - MONITOR_CENTER_Y + User.Aimbot.offsetY) * User.Aimbot.strength;
            Mouse.Aim(relX, relY);
            continue;
        }
    }

    return 0;
}