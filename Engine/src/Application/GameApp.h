#pragma once

#include <Core/CoreMinimal.h>

#include <Graphics/Device/GraphicsDevice.h>
#include <Window/Window.h>
#include <GameLogic/GameLogic.h>

class GameApp {
public:
	/**
	 * @brief Create Windows Application Object
	 * @param width Desired Application width.
	 * @param height Desired Application height.
	*/
	GameApp(int width, int height);
	//	Copy Consturctor destruction.
	GameApp(const GameApp&) = delete;
	//	Move Semantics desturction.
	GameApp& operator= (const GameApp&) = delete;

	void Start();
	void Run();
	void Exit();

private:
	Engine::GraphicsDevice* m_GraphicsDevice;
	Engine::Window* m_Window;
	Engine::GameLogic* m_GameManager;
	GameTimer* m_Timer;
};