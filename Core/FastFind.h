#pragma once
#include <Windows.h>
#include <stdexcept>

//https://github.com/FastFrench/FastFind

typedef LPCTSTR(__stdcall* f_FFVersion)(void);
typedef void(__stdcall* f_SetHWnd)(HWND NewWindowHandle, bool bClientArea);
typedef int(__stdcall* f_SnapShot)(int aLeft, int aTop, int aRight, int aBottom, int NoSnapShot);
typedef int(__stdcall* f_AddColor)(COLORREF NewColor);
typedef int(__stdcall* f_GetPixel)(int X, int Y, int NoSnapShot);
typedef void(__stdcall* f_AddExcludedArea)(int x1, int y1, int x2, int y2);
/* Return value: 0 if error, 1 if found
   SizeSearch: size of the sub-search area
   NbMatchMin: minimum ammount of pixels found in the search area (replaced by ammount of matchs found)
   XYRef: search will return closest find to this position (replaced by position of the match)
   ColorToFind: color to find 0xAARRGGBB
   ShadeVariation: variation of the color to match from 0 to 255
   NoSnapShot: number of the snapshot where the search is going to take place
*/
typedef int(__stdcall* f_GenericColorSearch)(int SizeSearch, int& NbMatchMin, int& XRef, int& YRef, int ColorToFind, int ShadeVariation, int NoSnapShot);

class User;

class FastFind
{
public:
	FastFind(User* user);

    const int ScreenShoot();

    const int ColorSearch(int& XRef, int& YRef);

    ~FastFind();

private:
    User* m_User;
    HINSTANCE m_hGetProcIDDLL;
    f_SnapShot m_SnapShot;
    f_GenericColorSearch m_GenericColorSearch;
    //f_SetHWnd m_SetHWnd;
    //f_AddColor m_AddColor;
    //f_GetPixel m_GetPixel;
    //f_AddExcludedArea m_AddExcludedArea;
};