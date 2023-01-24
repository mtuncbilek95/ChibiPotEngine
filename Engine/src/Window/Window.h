#ifndef WINDOW_H
#define WINDOW_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Renderer/Renderer.h>

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

		Renderer RendererDX;
	private:
		HINSTANCE m_hInstance;
		HWND m_windowHandle;

		UINT m_width, m_height;

		const char* className = "WindowClass";
	};

}

#endif // __WINDOW_H__