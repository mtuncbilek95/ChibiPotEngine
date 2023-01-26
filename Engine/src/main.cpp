#include <Window/Window.h>

int main(int argumentC, char** argumentValue) {

	Engine::Window* AppWindow = new Engine::Window(800, 800);

	AppWindow->Initialize();
	AppWindow->Run();
	AppWindow->Exit();

	delete AppWindow;

	return 0;
}