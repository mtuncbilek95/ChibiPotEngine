#pragma once

#include <Core/CoreMinimal.h>

#include <Graphics/Device/GraphicsDevice.h>

#include <GameTimer/GameTimer.h>

namespace Engine {

	class Window {
	public:
		/**
		 * @brief Create Windows Window Object
		 * @param width Desired Window width.
		 * @param height Desired Window height.
		*/
		Window(int width, int height);
		//	Copy Consturctor destruction.
		Window(const Window&) = delete;
		//	Copy Constructor desturction.
		Window& operator= (const Window&) = delete;
		~Window() = default;

		void InitializeWindow();

		void Start();
		void Update();
		void Stop();

		XMINT2 GetWindowSize() { return {m_width,m_height}; }
		HWND GetWindowHandler() { return m_windowHandle; }
		bool GetIsRunning() { return bIsRunning; }
	protected:
		static LRESULT APIENTRY WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
		void CalculateFrameRate(float DeltaTime);

	private:
		HINSTANCE m_hInstance;
		HWND m_windowHandle;

		int m_width, m_height;

		const string m_className;
		const string m_windowName;

		GameTimer m_windowTimer;
		bool bIsRunning;

		GraphicsDevice* m_GraphicsDevice;
	};
}