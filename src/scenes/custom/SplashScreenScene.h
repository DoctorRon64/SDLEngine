#pragma once
#include "../Scene.h"
#include "../../Objects/Image.h"
class SplashScreenScene :
    public Scene
{
public:
    SplashScreenScene() = default;
    void OnEnter() override 
    {
        Image* bg = new Image("res/splash_screen.png", { 0, 0 }, { 320, 200 });
        bg->GetTransform()->position = { 0,0 };
        bg->GetTransform()->scale = { (float)RenderManager::GetInstance()->WINDOW_WIDTH / 320.0f, (float)RenderManager::GetInstance()->WINDOW_HEIGHT / 200.0f };
        bg->SetLayer(20);
        ui.push_back(bg);
        TimeManager::GetInstance()->SubscribeEvent(3.0f, []() {SceneManager::GetInstance()->SetNextScene(SceneState::MENU);});
    }

    void OnUpdate() override { Scene::OnUpdate(); }

    void OnExit() override { Scene::OnExit(); }
};

