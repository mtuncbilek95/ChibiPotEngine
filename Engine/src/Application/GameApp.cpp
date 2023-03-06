#include "GameApp.h"

GameApp::GameApp(int width, int height) : m_GraphicsDevice(nullptr), m_Window(nullptr), m_Timer(nullptr)
{
	m_Window = new Engine::Window(width, height);

	m_Window->InitializeWindow();

	if (m_Window->GetWindowHandler())
		m_GraphicsDevice = new Engine::GraphicsDevice();

	if (m_GraphicsDevice)
		m_Timer = new GameTimer();
}

void GameApp::Start()
{
	m_Window->SetIsRunning(m_GraphicsDevice->Initialize(m_Window->GetWindowHandler(), m_Window->GetWindowSize().x, m_Window->GetWindowSize().y));
}

void GameApp::Run()
{
	while (m_Window->GetIsRunning()) {
		if (!m_Window->ProcessMessage())
		{
			m_Timer->Tick();
			m_GraphicsDevice->Update();
		}
	}
}

void GameApp::Exit()
{
	delete m_Timer, m_GraphicsDevice, m_Window;
}
