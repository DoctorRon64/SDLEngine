#pragma once
#include "Decoration.h"
class Decoration3 :
    public Decoration
{
public:
    Decoration3() : Decoration("res/minecraft_poppy.png", { 0,0 }, { 120, 188 }) {
        transform->scale = { .2f, .2f };
    }
};

