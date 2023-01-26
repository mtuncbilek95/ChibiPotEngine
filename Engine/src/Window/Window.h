#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#pragma region "Std Libraries"
#include <string>
#include <memory>
#pragma enregion

#include <Renderer/Renderer.h>
#include <GameTimer/GameTimer.h>

using std::string;

namespace Engine {

	class Window {
	public:
		Window(UINT width, UINT height);
		Window(const Window&) = delete;
		Window& operator= (const Window&) = delete;
		~Window() = default;

		void Initialize();
		void Run();
		void Exit();

		bool bIsRunning;
	protected:
		static LRESULT APIENTRY WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
		void CalculateFrameRate();

		std::unique_ptr<Renderer> RendererDX;
	private:
		HINSTANCE m_hInstance;
		HWND m_windowHandle;

		UINT m_width, m_height;

		const char* m_className = "WindowClass";
		string m_windowName = "ChibiPot Engine";

		GameTimer m_windowTimer;
	};
}