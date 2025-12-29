#pragma once
#include "../Object.h"

class PowerUp : public Object {
protected:
	virtual void OnCollect() = 0;
};