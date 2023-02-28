#include "ApplicationDevice.h"

Engine::ApplicationDevice::ApplicationDevice()
{
	m_AppWindow = new Window(700, 700);
	m_GraphicsDevice = new GraphicsDevice();

	m_AppWindow->InitializeWindow();
}

void Engine::ApplicationDevice::BeginPlay()
{
	m_AppWindow->BeginPlay(m_GraphicsDevice);
}

void Engine::ApplicationDevice::Update()
{
	while (m_AppWindow->GetIsRunning())
		m_AppWindow->Update();
}

void Engine::ApplicationDevice::LateUpdate()
{
}

void Engine::ApplicationDevice::EndPlay()
{
	m_AppWindow->EndPlay();
}
