#include "pch.h"
#include "Engine.h"

int main(int argc, char* argv[]) {
	constexpr unsigned int WIDTH = 1360;
	constexpr unsigned int HEIGHT = 768;
	const std::string TITLE = "SDL_Engine";

	Engine* engine = new Engine();

	try {
		renderManager->Init(WIDTH, HEIGHT, TITLE);
		audioManager->Init();
		engine->Init();
	}
	catch(std::exception& result) {
		std::cout << "There is a error: " << result.what() << std::endl;
		renderManager->Terminate();
		audioManager->HaltAudio();
		return -1;
	}

	while(engine->IsRunning()) {
		timeManager->Update();
		if(timeManager->ShouldUpdateGame()) {
			engine->HandleEvents();
			engine->Update();
			engine->Render();
			timeManager->ResetDeltaTime();
		}
	}

	delete(engine);
	engine = nullptr;

	return 0;
}