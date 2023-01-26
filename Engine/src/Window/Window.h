#pragma once

#include <Core/CoreMinimal.h>

#include <Renderer/Renderer.h>
#include <GameTimer/GameTimer.h>

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

	protected:
		static LRESULT APIENTRY WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
		void CalculateFrameRate(float DeltaTime);
		void ProcessMessage();

		Renderer* RendererDX;
	private:
		HINSTANCE m_hInstance;
		HWND m_windowHandle;

		UINT m_width, m_height;

		const string m_className;
		const string m_windowName;

		GameTimer m_windowTimer;

		bool bIsRunning;
	};
}