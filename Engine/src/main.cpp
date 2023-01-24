#include "Window/Window.h"

int main(int argumentC, char** argumentValue) {

	Engine::Window* AppWindow = new Engine::Window(800, 800);

	AppWindow->Initialize();

	while (AppWindow->bIsRunning)
		AppWindow->Run();

	AppWindow->Exit();

	delete AppWindow;

	return 0;
}