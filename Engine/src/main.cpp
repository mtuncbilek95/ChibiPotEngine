#include <Application/GameApp.h>

#include <ECS/EntityBase.h>
#include <ECS/Entity.h>
#include <ECS/TransformComponent.h>

int main(int argumentC, char** argumentValue) {
	//GameApp* Application = new GameApp(800,800);

	//Application->Start();
	//Application->Run();
	//Application->Exit();

	Entity* entity = new Entity();

	entity->AddComponent<TransformComponent>(100,100);


	return 0;
}