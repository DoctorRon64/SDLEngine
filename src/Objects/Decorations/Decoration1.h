#pragma once
#include "Decoration.h"
class Decoration1 :
	public Decoration {
public:
	Decoration1() : Decoration("res/decoration_grass.png", { 0,0 }, { 32, 32 }) {
		transform->scale = { 2.f, 2.f };
	}
};
