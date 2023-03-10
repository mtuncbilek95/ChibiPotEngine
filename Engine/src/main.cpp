//#include <Application/GameApp.h>

#include <ECS/EntityBase.h>
#include <ECS/Entity.h>
#include <ECS/TransformComponent.h>

int main(int argumentC, char** argumentValue) {
	//GameApp* Application = new GameApp(800,800);

	//Application->Start();
	//Application->Run();
	//Application->Exit();

	Entity* entity = new Entity();
	XMFLOAT3 pos = { 100,100,0 };
	XMFLOAT3 scale = { 1,1,1 };
	float rot = 0.0f;
	entity->AddComponent<TransformComponent>(pos,scale,rot);
	std::cout << std::boolalpha << entity->HasAnyComponent() << std::endl;

	return 0;
}