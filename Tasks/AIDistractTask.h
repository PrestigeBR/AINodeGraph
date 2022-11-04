#pragma once
#include "AIBrain/AITask.h"
#include "Imported/Player/CPlayer.h"

class AIDistractTask : public AITask
{
public:
	AIDistractTask(AIBrain* Brain, tgCString Name);

	bool OnTaskBeginExecute() override;

};
