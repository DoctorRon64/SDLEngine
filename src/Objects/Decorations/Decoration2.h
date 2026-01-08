#pragma once
#include "Decoration.h"
class Decoration2 :
	public Decoration {
public:
	Decoration2() : Decoration("res/decoration_bush.png", { 0,0 }, { 32, 32 }) {
		transform->scale = { 2.f, 3.f };
	}
};
