#pragma once
#include "Decoration.h"
class Decoration1 :
    public Decoration
{
public:
    Decoration1() : Decoration("res/minecraft_tall_grass.png", {0,0}, {160, 160}) {
        transform->scale = { .5f, .7f };
    }
};

