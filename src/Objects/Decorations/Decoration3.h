#pragma once
#include "Decoration.h"
class Decoration3 :
	public Decoration {
public:
	Decoration3() : Decoration(DECORATION_FLOWER_SPRITE_PATH, { 0,0 }, { 32, 32 }) {
		transform->scale = { 2.f, 2.f };
	}
};
