#include <SDL3/SDL.h>
#include <iostream>
#include <exception>
#include "Engine.h"

#include "Managers/RenderManager.h"

int main(int argc, char* argv[]) {
	Engine* engine = new Engine();

	try {
		engine->Init();
	}
	catch(std::exception& result) {
		std::cout << "There is a error: " << result.what() << std::endl;
		RM->Terminate();
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