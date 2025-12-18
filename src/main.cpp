#include "pch.h"
#include "Engine.h"

int main(int argc, char* argv[]) {
	constexpr unsigned int Width = 1200;
	constexpr unsigned int Height = 1080;
	const std::string Title = "SDL_Engine";

	Engine* engine = new Engine();

	try {
		renderManager->Init(Width, Height, Title);
		engine->Init();
		audioManager->Init();
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