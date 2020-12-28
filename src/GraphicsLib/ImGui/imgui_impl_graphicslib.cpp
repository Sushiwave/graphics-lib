#include <GraphicsLib/ImGui/imgui_impl_graphicslib.hpp>
#include <GraphicsLib/Context.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Window/Components/WINAPI/WindowHandle/WINAPIWindowHandle.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/MainRenderTarget/MainRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <ThirdParty/ExtendedImGui/ImGui/imgui_impl_dx11.h>
#include <ThirdParty/ExtendedImGui/ImGui/imgui_impl_win32.h>





bool ImGui_ImplGraphicsLib_Init()
{
#ifdef CONTEXT_D3D11
	auto isSucceeded = false;
	ImGui::CreateContext();
	ImGui::GetIO().IniFilename = nullptr;
	isSucceeded = ImGui_ImplWin32_Init(cg::winapi::WindowHandle::get());
	isSucceeded = ImGui_ImplDX11_Init(cg::d3d11::Device::getDevice().Get(), cg::d3d11::Device::getDeviceContext().Get());
	
	return isSucceeded;
#endif
}

void ImGui_ImplGraphicsLib_Shutdown()
{
#ifdef CONTEXT_D3D11
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif
}

void ImGui_ImplGraphicsLib_NewFrame()
{
#ifdef CONTEXT_D3D11
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
#endif
	ImGui::NewFrame();
	
	const auto baseColor = ImVec4(224.0f/255.0f, 25.0f/255.0f, 66.0f/255.0f, 1.0f);
	const auto baseColorDark = ImVec4(baseColor.x*0.5f, baseColor.y*0.5f, baseColor.z*0.5f, 1.0f);
	const auto darkColor = ImVec4(0.125f, 0.125f, 0.125f, 1.0f);
		
	ImGui::PushStyleColor(ImGuiCol_TitleBg, baseColorDark);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, baseColor);
	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, darkColor);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, darkColor);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, darkColor);
	ImGui::PushStyleColor(ImGuiCol_Button, baseColorDark);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, baseColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, baseColor);
	ImGui::PushStyleColor(ImGuiCol_DragDropTarget, baseColorDark);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, darkColor);
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, baseColor);
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, baseColorDark);
	ImGui::PushStyleColor(ImGuiCol_Header, baseColorDark);
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, baseColor);
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, baseColor);
	ImGui::PushStyleColor(ImGuiCol_CheckMark, baseColor);
}

void ImGui_ImplGraphicsLib_Render()
{
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::Render();

	const auto mainRenderTarget = cg::MainRenderTarget::shared.get();
	if (cg::GPUStateViewer::view().renderTarget.id != mainRenderTarget->getID())
	{
		mainRenderTarget->set(nullptr);
	}

#ifdef CONTEXT_D3D11
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
}
