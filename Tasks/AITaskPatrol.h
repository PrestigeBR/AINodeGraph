#pragma once
#include "AIBrain/AITask.h"

class AITaskPatrol : public AITask
{
public:
	AITaskPatrol(AIBrain* Brain, tgCString Name);

	bool OnTaskBeginExecute() override;

};
