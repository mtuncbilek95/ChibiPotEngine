#include <Window/Window.h>

int main(int argumentC, char** argumentValue) {

	Engine::Window* App = new Engine::Window(800,800);

	App->InitializeWindow();

	App->Start();
	while(App->GetIsRunning())
		App->Update();
	App->Stop();
	
	return 0;
}