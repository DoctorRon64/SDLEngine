#pragma once
#include "Text.h"
class InputText :
    public Text
{
private:
    std::string _text = "";

public:
    InputText(std::string _text) : Text(_text) {}

    void Update() override {
        Text::Update();

        //Letters
        for (int key = SDLK_A; key <= SDLK_Z; ++key) {
            if (InputManager::GetInstance()->GetEvent(key, DOWN)
                && _text.length() < MAX_USER_LENGTH)
                _text += (char)(key - SDLK_A) + 'A';
        }

        //Numbers
        for (int key = SDLK_0; key <= SDLK_9; ++key) {
            if (InputManager::GetInstance()->GetEvent(key, DOWN)
                && _text.length() < MAX_USER_LENGTH)
                _text += (char)(key - SDLK_0) + '0';
        }

        if(InputManager::GetInstance()->GetEvent(SDLK_BACKSPACE, DOWN)
            && _text.length() > 0) {
            _text.erase(_text.length() - 1, 1);
        }

        if (_text.length() > 0) SetText(_text);
        else SetText(" ");
    }
};

