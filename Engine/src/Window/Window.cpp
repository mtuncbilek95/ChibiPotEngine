#include "Window.h"

#include <Resources/Resource.h>
#include <Logger/Logger.h>

Engine::Window::Window(UINT width, UINT height) : m_hInstance(GetModuleHandle(nullptr)), m_windowHandle(nullptr), 
bIsRunning(false), m_className("WindowClass"), m_windowName("ChibiPot Engine")
{
	this->m_width = width;
	this->m_height = height;

	RendererDX = new Renderer(width, height);
}

void Engine::Window::Initialize()
{
	WNDCLASSEX windowClass{};
	windowClass.cbSize = sizeof(windowClass);
	windowClass.lpszClassName = m_className.c_str();
	windowClass.lpszMenuName = nullptr;
	windowClass.hInstance = m_hInstance;
	windowClass.hIcon = (HICON)(LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 32, 32, 0));
	windowClass.hIconSm = (HICON)(LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0));
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpfnWndProc = WindowProc;

	RegisterClassEx(&windowClass);

	DWORD windowStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	RECT windowSize;
	windowSize.left = 250;
	windowSize.top = 250;
	windowSize.right = windowSize.left + m_width;
	windowSize.bottom = windowSize.top + m_height;

	AdjustWindowRect(&windowSize, windowStyle, false);

	m_windowHandle = CreateWindowEx(0, m_className.c_str(), m_windowName.c_str(), windowStyle, windowSize.left, windowSize.top, windowSize.right - windowSize.left,
		windowSize.bottom - windowSize.top, nullptr, nullptr, m_hInstance, this);

	if (m_windowHandle != nullptr) {
		CONSOLE_LOG(Success, "Window has been successfully created.");
		ShowWindow(m_windowHandle, SW_SHOW);
	}

	bIsRunning = RendererDX->Initialize(m_windowHandle);
}

void Engine::Window::Run()
{
	MSG msg{};

	m_windowTimer.Reset();

	while (bIsRunning)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			RendererDX->UpdateFrame();

			m_windowTimer.Tick();
			CalculateFrameRate();
		}
	}
}

void Engine::Window::Exit()
{
	UnregisterClass(m_className.c_str(), m_hInstance);
	DestroyWindow(m_windowHandle);
}

LRESULT Engine::Window::WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		Window* WindowPtr = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)WindowPtr);
		break;
	}
	case WM_CLOSE:
		((Window*)(GetWindowLongPtr(windowHandle, GWLP_USERDATA)))->bIsRunning = false;
		break;
	}

	return DefWindowProc(windowHandle, message, wParam, lParam);
}

void Engine::Window::CalculateFrameRate()
{
	static int frameCount = 0;
	static float timeElapsed = 0.0f;

	frameCount++;

	if ((m_windowTimer.TotalTime() - timeElapsed) >= 1.0f) {
		float fps = (float)frameCount;
		float mspf = 1000.f / fps;
		string fpsStr = std::to_string(static_cast<int>(fps));

		string windowText = m_windowName + " FPS: " + fpsStr;
		SetWindowText(m_windowHandle, windowText.c_str());

		frameCount = 0;
		timeElapsed += 1.0f;
	}
}
