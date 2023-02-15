#pragma once

class GameConductor {

public:
	virtual void Start() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void End() = 0;
};

class GameObject : public GameConductor {

	virtual void Start() override {

	}
};