#pragma once

namespace KwurkEngine::Core
{
	class Window
	{
	public:
		void Initialize(HINSTANCE instance, const std::wstring& appName, uint32_t width, uint32_t height);
		void Terminte();

		void ProcessMessage();

		HWND GetWINdowHandle() const;
		bool IsActive() const;


	private:
		HINSTANCE = nullptr;
		HWND mWIndow = nullptr;
		RECT mScreenRect{};
		std::wstring mAppName;
		bool mActive;
	};


}
