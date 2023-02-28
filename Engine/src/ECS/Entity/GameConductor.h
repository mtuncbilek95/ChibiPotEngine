#pragma once

class GameConductor {

public:
	/**
	 * @brief Runs after first initialization, before tick.
	*/
	virtual void BeginPlay() = 0;
	/**
	 * @brief Runs per frame.
	 * @param DeltaTime Time difference between each frame
	*/
	virtual void Update(float DeltaTime) = 0;
	/**
	 * @brief Runs per frame after tick.
	*/
	virtual void LateUpdate() = 0;
	/**
	 * @brief Runs when termination event. 
	 * TODO : This will take EndReason parameter later.
	*/
	virtual void EndPlay() = 0;
};