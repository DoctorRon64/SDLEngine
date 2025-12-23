#include "pch.h"
#include "Engine.h"
#include "Utils/config.h"

int main(int argc, char* argv[]) {
	Engine* engine = new Engine();

	try {
		RenderManager::GetInstance()->Init(WIDTH, HEIGHT, TITLE);
		AudioManager::GetInstance()->Init();
		engine->Init();
	}
	catch(std::exception& result) {
		std::cout << "There is a error: " << result.what() << std::endl;
		RenderManager::GetInstance()->Terminate();
		AudioManager::GetInstance()->HaltAudio();
		return -1;
	}

	while(engine->IsRunning()) {
		TimeManager::GetInstance()->Update();
		if(TimeManager::GetInstance()->ShouldUpdateGame()) {
			engine->HandleEvents();
			engine->Update();
			engine->Render();
			TimeManager::GetInstance()->ResetDeltaTime();
		}
	}

	delete(engine);
	engine = nullptr;

	return 0;
}