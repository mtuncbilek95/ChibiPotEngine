#include <Application/ApplicationDevice.h>

int main(int argumentC, char** argumentValue) {

	Engine::ApplicationDevice* App = new Engine::ApplicationDevice();

	App->BeginPlay();
	App->Update();
	App->LateUpdate();
	App->EndPlay();
	
	return 0;
}