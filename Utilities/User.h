#pragma once
#include <windows.h>

class User {
public:
	User();

	~User();

	struct
	{
		int aim = 0x00;
		int toggleMenu = VK_F10;
	}Binds;

	struct 
	{
		float strength = 1.0f;
		int fov = 320;
		int offsetX = 0;
		int offsetY = 0;
	}Aimbot;

	struct
	{
		int color = 0x000000;
		int colorVariation = 0;
		int prefX = GetSystemMetrics(SM_CXSCREEN) / 2;
		int prefY = GetSystemMetrics(SM_CYSCREEN) / 2;
		int sizeSearch = 1;
		int minMatch = 1;
		// For ImGui widget
		float colorRGB[3] = { 0 , 0, 0 };
		int refX = 0;
		int refY = 0;
	}SearchSettings;

	struct 
	{
		bool debug = false;
		bool loadedApp = false;
	}Data;
};