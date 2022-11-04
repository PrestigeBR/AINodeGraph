#pragma once
#include "AIBrain/AITask.h"

class AITaskChasePlayer : public AITask
{
public:
	AITaskChasePlayer(AIBrain* Brain, tgCString Name);

	bool OnTaskBeginExecute() override;

};
