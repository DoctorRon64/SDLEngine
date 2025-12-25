#pragma once
#include "../Object.h"

class PowerUp : public Object {
private:
	virtual void OnCollect() = 0;
};