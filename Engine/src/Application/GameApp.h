#pragma once

#include <Core/CoreMinimal.h>
#include <Graphics/Device/GraphicsDevice.h>
#include <Window/Window.h>

class GameApp {
public:
	GameApp();

private:
	GraphicsDevice* m_GraphicsDevice;
	Window* m_Window;
};