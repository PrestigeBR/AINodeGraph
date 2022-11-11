#pragma once
#include "AITask.h"

#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

#include "NodeEditor/AINodeGraph.h"

class CEnemy;

class AIBrain
{

public:
	AIBrain(CEnemy* Pawn);

	bool ExecuteTask(AITask* Task);

	AITask* InitTask(AITask* Task);

	void DebugCheckTasks();

	float FrameCount = 0.f;

	float m_DeltaTime = 0.f;

	void DestroyTasks() const;

	std::vector<AITask*> TaskList;

	AITask* m_CurrentTask = nullptr;

	CEnemy* m_ControlledPawn = nullptr;

};
