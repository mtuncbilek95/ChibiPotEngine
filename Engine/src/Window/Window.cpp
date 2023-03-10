#include "Window.h"

#include <Logger/Logger.h>
#include <Application/GameApp.h>

#include <Resources/Resource.h>


Engine::Window::Window(int width, int height) : m_hInstance(GetModuleHandle(nullptr)), m_windowHandle(nullptr),
bIsRunning(false), m_className("WindowClass"), m_windowName("ChibiPot Engine")
{
	this->m_width = width;
	this->m_height = height;
	Logger::PrintLog(Logger::PrintType::Display, "********** Window Device **********");
}

Engine::Window::~Window()
{
	UnregisterClass(m_className.c_str(), m_hInstance);
	DestroyWindow(m_windowHandle);
	m_hInstance = 0;
	m_windowHandle = 0;
}

void Engine::Window::InitializeWindow()
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

	RECT windowSize{};
	windowSize.left = 250;
	windowSize.top = 250;
	windowSize.right = windowSize.left + m_width;
	windowSize.bottom = windowSize.top + m_height;

	AdjustWindowRect(&windowSize, windowStyle, false);

	m_windowHandle = CreateWindowEx(0, m_className.c_str(), m_windowName.c_str(), windowStyle, windowSize.left, windowSize.top, windowSize.right - windowSize.left,
		windowSize.bottom - windowSize.top, nullptr, nullptr, m_hInstance, this);

	if (m_windowHandle != nullptr)
	{
		Logger::PrintLog(Logger::PrintType::Success, "Window has been successfully created.");
		ShowWindow(m_windowHandle, SW_SHOW);
	}
}

bool Engine::Window::ProcessMessage()
{
	MSG msg{};

	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		return true;
	}
	else
		return false;
}

HWND Engine::Window::GetWindowHandler()
{
	return m_windowHandle;
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
	case WM_QUIT:
		((Window*)(GetWindowLongPtr(windowHandle, GWLP_USERDATA)))->bIsRunning = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(windowHandle, message, wParam, lParam);
}
