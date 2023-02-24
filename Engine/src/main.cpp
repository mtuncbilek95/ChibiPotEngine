#include <Window/Window.h>

int main(int argumentC, char** argumentValue) {

	std::unique_ptr<Engine::Window> AppWindow = std::make_unique<Engine::Window>(600,600);

	AppWindow->InitializeWindow();
	
	AppWindow->Start();
	while (AppWindow->bIsRunning)
		AppWindow->Update();
	AppWindow->Exit();

	return 0;
}