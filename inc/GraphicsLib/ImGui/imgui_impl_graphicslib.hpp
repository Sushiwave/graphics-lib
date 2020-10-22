#pragma once
#include <Windows.h>
#include <ThirdParty/ExtendedImGui/ImGui/imgui.h>


IMGUI_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

IMGUI_IMPL_API bool ImGui_ImplGraphicsLib_Init();
IMGUI_IMPL_API void ImGui_ImplGraphicsLib_Shutdown();
IMGUI_IMPL_API void ImGui_ImplGraphicsLib_NewFrame();
IMGUI_IMPL_API void ImGui_ImplGraphicsLib_Render();
