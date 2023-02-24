#pragma once

#include <Core/CoreMinimal.h>

#include <Renderer/Renderer.h>
#include <Graphics/Device/GraphicsDevice.h>

#include <GameTimer/GameTimer.h>

namespace Engine {

	class Window {
	public:
		Window(int width, int height);
		Window(const Window&) = delete;
		Window& operator= (const Window&) = delete;
		~Window() = default;

		void InitializeWindow();

		void Start();
		void Update();
		void Exit();

		bool bIsRunning;
	protected:
		static LRESULT APIENTRY WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
		void CalculateFrameRate(float DeltaTime);

		GraphicsDevice* GraphicsDeviceDX;
	private:
		HINSTANCE m_hInstance;
		HWND m_windowHandle;

		int m_width, m_height;

		const string m_className;
		const string m_windowName;

		GameTimer m_windowTimer;
	};
}