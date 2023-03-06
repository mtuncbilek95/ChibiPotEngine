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
		//	Move Semantics desturction.
		Window& operator= (const Window&) = delete;
		~Window();

		void InitializeWindow();
		bool ProcessMessage();

		void SetIsRunning(bool bValue) { bIsRunning = bValue; }
		bool GetIsRunning() { return bIsRunning; }

		XMINT2 GetWindowSize() { return { m_width,m_height }; }
		HWND GetWindowHandler();
	protected:
		static LRESULT APIENTRY WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HINSTANCE m_hInstance;
		HWND m_windowHandle;

		int m_width, m_height;

		const string m_className;
		const string m_windowName;

		bool bIsRunning;

	};
}