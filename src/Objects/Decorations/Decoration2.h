#pragma once
#include "Decoration.h"
class Decoration2 :
    public Decoration
{
public:
    Decoration2() : Decoration("res/minecraft_rose_bush.png", { 0,0 }, { 160, 160 }) {
        transform->scale = { .5f, .5f };
    }
};

