#pragma once
#include "AIBrain/AITask.h"

class AITaskLookForPlayer : public AITask
{
public:
	AITaskLookForPlayer(AIBrain* Brain, tgCString Name);

	bool OnTaskBeginExecute() override;

};
