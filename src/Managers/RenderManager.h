#pragma once

class RenderManager {
public:
	static RenderManager* GetInstance() {
		static RenderManager instance;
		return &instance;
	}

	std::string WINDOW_TITLE;
	unsigned int WINDOW_WIDTH;
	unsigned int WINDOW_HEIGHT;

	void Init(int _width, int _height, std::string _title);
	void Terminate();
	void ClearScreen();
	void RenderScreen();

	SDL_Renderer* GetRenderer() const { return renderer; }
	void LoadTexture(const std::string& _texturePath);
	SDL_Texture* GetTexture(const std::string& textureName);

	void LoadFont(std::string _path);
	TTF_Font* GetFont(std::string _path);

private:
	RenderManager() = default;
	RenderManager(RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	~RenderManager();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::map<std::string, SDL_Texture*> textures;

	void InitSDL();
	void CreateWindowAndRender();

	std::map <std::string, TTF_Font*> fonts;
};
