#pragma once

namespace Engine {

	class GameLogic {
	public:
		GameLogic();
		GameLogic(const GameLogic&) = delete;
		GameLogic& operator=(const GameLogic&) = delete;
		~GameLogic();

		void Start();
		void Update(float DeltaTime);
		void Stop();
	};
}
