#include "pch.h"
#include "AmoebaSplitState.h"
#include "../AmoebaEnemy.h"

void AmoebaSplitState::Update(float dt) {
	(void)dt;

	if(!owner) {
		finished = true;
		return;
	}

	if(!spawned) {
		owner->SpawnSplitClones();
		spawned = true;
	}

	if(owner->AreSplitClonesDone()) {
		finished = true;
	}
}
