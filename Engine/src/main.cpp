#include <Window/Window.h>

int main(int argumentC, char** argumentValue) {

	Engine::Window* AppWindow = new Engine::Window(600, 600);

	AppWindow->Initialize();
	while (AppWindow->bIsRunning)
		AppWindow->Run();
	AppWindow->Exit();

	delete AppWindow;

	return 0;
}