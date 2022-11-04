#pragma once
#include "AIBrain/AITask.h"

class AITaskStun : public AITask
{
public:
	AITaskStun(AIBrain* Brain, tgCString Name);

	bool OnTaskBeginExecute() override;

};
