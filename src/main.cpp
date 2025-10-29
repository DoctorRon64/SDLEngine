#include <SDL3/SDL.h>
#include <iostream>
#include <exception>
#include "Engine.h"

int main(int argc, char* argv[]) {
	Engine* engine = new Engine();

	try {
		engine->Init();
	}
	catch (std::exception& result) {
		std::cout << "Hay un error: " << result.what() << std::endl;
		engine->Terminate();
		return -1;
	}

	while (engine->IsRunning()) {
		engine->HandleEvents();
		engine->Update();
		engine->Render();
	}
	return 0;
}