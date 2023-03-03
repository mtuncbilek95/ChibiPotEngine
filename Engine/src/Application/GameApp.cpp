#include "GameApp.h"

GameApp::GameApp(int width, int height) : m_GraphicsDevice(nullptr), m_Window(nullptr)
{
	m_Window = new Engine::Window(width, height);

	if (m_Window->GetWindowHandler())
		m_GraphicsDevice = new Engine::GraphicsDevice();
	
	if (m_GraphicsDevice)
		m_Timer = new GameTimer();

}

void GameApp::Start()
{
	m_Window->InitializeWindow();
	m_GraphicsDevice->Initialize(m_Window->GetWindowHandler(), m_Window->GetWindowSize().x, m_Window->GetWindowSize().y);
}

void GameApp::Run()
{
}
