#include "Engine.h"
#include "Managers/RenderManager.h"
#include <exception>
#include <iostream>
#include <SDL3/SDL.h>

int main(int argc, char* argv[]) {
	Engine* engine = new Engine();

	try {
		engine->Init();
	}
	catch(std::exception& result) {
		std::cout << "There is a error: " << result.what() << std::endl;
		renderManager->Terminate();
		return -1;
	}

	while(engine->IsRunning()) {
		engine->HandleEvents();
		engine->Update();
		engine->Render();
	}

	delete(engine);
	engine = nullptr;

	return 0;
}