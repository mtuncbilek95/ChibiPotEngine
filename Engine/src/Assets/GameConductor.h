#pragma once

class GameConductor {
	GameConductor() = delete;
	GameConductor(const GameConductor&) = delete;
	GameConductor& operator=(const GameConductor&) = delete;
public:
	virtual void Start() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void End() = 0;
};

class GameObject : public GameConductor {

	virtual void Start() override {

	}
};