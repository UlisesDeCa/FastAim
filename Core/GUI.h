#pragma once
#include <d3d11.h>
#include "../ImGui/imgui.h"

class User;

class Menu 
{
public:
	Menu(bool& running, User& user);

	void Start();

private:
	bool* m_Running;
	User* m_User;

	void DrawLoading();
	void DrawMenu();

	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pd3dDeviceContext = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_mainRenderTargetView = nullptr;
	//UINT m_ResizeWidth, m_ResizeHeight = 0;

	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
	void StyleMenu();

	bool SliderPercentage(const char* label, float* v, float v_min, float v_max);
	bool SliderInteger(const char* label, int* v, int v_min, int v_max);
	void HotKey(const char* label, int& hotkey, const ImVec2& size = ImVec2(0, 0));
	void HelpMark(const char* desc);
	bool Spinner(const char* label, float radius, int thickness, const ImU32& color);
};