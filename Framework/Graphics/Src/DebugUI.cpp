#include "Precompiled.h"
#include "DebugUI.h"

#include "GraphicsSystem.h"

#include <ImGui/Inc/imgui_impl_dx11.h>
#include <ImGui/Inc/imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace KwurkEngine;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;

namespace
{
	WindowMessageHandler sWindowMessageHandler;

	bool IsMouseInput(UINT message)
	{
		switch (message)
		{
		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:

		case WM_RBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONDBLCLK:

		case WM_MBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONDBLCLK:

		case WM_MOUSEWHEEL:
		case WM_MOUSEHWHEEL:
			return true;
		}
		return false;
	}

	bool IsKeyBoardInput(UINT message)
	{
		switch (message)
		{
		case WM_KEYUP:
		case WM_KEYDOWN:
		case WM_SYSKEYUP:
		case WM_SYSKEYDOWN:
		case WM_CHAR:

			return true;
		}
		return false;					
	}

	LRESULT CALLBACK DebugUIMessageHandle(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse && IsMouseInput(message))
		{
			return ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam);
		}
		if (io.WantCaptureKeyboard && IsKeyBoardInput(message))
		{
			return ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam);
		}
		
		LRESULT result = ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam);
		if (result != 0)
		{
			return result;
		}
		return sWindowMessageHandler.ForwardMessage(window, message, wParam, lParam);
	}
}


void DebugUI::StaticInitialize(HWND window, bool docking, bool multiViewPort)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	if (docking)
	{
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	}
	if(multiViewPort)
	{
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	}

	auto device = GraphicsSystem::Get()->GetDevice();
	auto context = GraphicsSystem::Get()->GetContext();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, context);

	sWindowMessageHandler.Hook(window, DebugUIMessageHandle);
}

void DebugUI::StaticTerminate()
{
	sWindowMessageHandler.Unhook();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


}

void DebugUI::SetTheme(Theme theme)
{
	switch (theme)
	{
	case Theme::Classic:	ImGui::StyleColorsClassic();
		break; 
	case Theme::Dark:		ImGui::StyleColorsDark();
		break;
	case Theme::Light:		ImGui::StyleColorsLight();
		break;
	default:
		break;
	}
}

void DebugUI::BeginRender()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void DebugUI::EndRender()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}
