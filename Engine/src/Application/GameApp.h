#pragma once

#include <Core/CoreMinimal.h>

#include <Graphics/Device/GraphicsDevice.h>
#include <Window/Window.h>

class GameApp {
public:
	GameApp(int width, int height);

	void Start();
	void Run();
private:
	Engine::GraphicsDevice* m_GraphicsDevice;
	Engine::Window* m_Window;
	GameTimer* m_Timer;
};