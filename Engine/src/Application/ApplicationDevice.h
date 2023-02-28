#pragma once

#include <Core/CoreMinimal.h>

#include <ECS/Entity/GameConductor.h>

#include <Window/Window.h>
#include <Graphics/Device/GraphicsDevice.h>

namespace Engine {
	class ApplicationDevice {
	public:
		/**
		 * @brief Application Device Object Consturctor
		*/
		ApplicationDevice();
		ApplicationDevice(const ApplicationDevice&) = delete;

		void BeginPlay();
		void Update();
		void LateUpdate();
		void EndPlay();

	private:
		Window* m_AppWindow;
		GraphicsDevice* m_GraphicsDevice;
	};
}