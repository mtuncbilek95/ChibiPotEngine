#include <Application/GameApp.h>

int main(int argumentC, char** argumentValue) {
	GameApp* Application = new GameApp(800,800);

	Application->Start();
	Application->Run();
	Application->Exit();


	return 0;
}