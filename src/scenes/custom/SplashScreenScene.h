#pragma once
#include "../Scene.h"
class SplashScreenScene :
    public Scene
{
public:
    SplashScreenScene() = default;
    void OnEnter() override 
    {
        TimeManager::GetInstance()->SubscribeEvent(std::make_pair(3.0f, []() {SceneManager::GetInstance()->SetNextScene(SceneState::MENU);}));
    }
    void OnExit() override {}
};

