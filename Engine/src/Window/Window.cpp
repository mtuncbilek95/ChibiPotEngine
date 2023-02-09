#include "Window.h"

#include <Logger/Logger.h>
#include <Resources/Resource.h>

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
		CONSOLE_LOG(CB_Success, "Window has been successfully created.");
		ShowWindow(m_windowHandle, SW_SHOW);
	}

	bIsRunning = RendererDX->Initialize(m_windowHandle);
}

void Engine::Window::Run()
{
	m_windowTimer.Reset();

	MSG msg{};

	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			RendererDX->UpdateFrame(m_windowTimer.DeltaTime());
			CalculateFrameRate(m_windowTimer.DeltaTime());

			m_windowTimer.Tick();
		}
	}
}

void Engine::Window::Exit()
{
	UnregisterClass(m_className.c_str(), m_hInstance);
	DestroyWindow(m_windowHandle);
	m_hInstance = 0;
	m_windowHandle = 0;
	delete RendererDX;
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

void Engine::Window::CalculateFrameRate(float DeltaTime)
{
	static float counter{0};
	counter += DeltaTime;

	int fps = (int)(1.f / DeltaTime);

	if (counter >= 1.0f) {
		
		string fpsStr = std::to_string(static_cast<int>(fps));

		string windowText = m_windowName + " FPS: " + fpsStr;
		CONSOLE_LOG(CB_Display, "%s", windowText.c_str());
		counter = 0.0f;
	}
}

void Engine::Window::ProcessMessage()
{
	MSG msg{};

	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
