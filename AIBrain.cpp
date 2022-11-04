#include <tgSystem.h>
#include "AIBrain.h"

#include "NodeEditor/AINode_Task.h"

AITask* AIBrain::InitTask(AITask* Task)
{
	TaskList.push_back(Task);

	return Task;
}

void AIBrain::DebugCheckTasks()
{
	for(AITask* Task : TaskList)
	{
		if(Task->m_LastExecuteTime != FrameCount)
		{
			Task->HasFinishedExecute = false;
		}
	}
	FrameCount += 1.f;
}

AIBrain::AIBrain(CEnemy* Pawn)
{
	m_ControlledPawn = Pawn;
}

bool AIBrain::ExecuteTask(AITask* Task)
{
	m_CurrentTask = Task;
	return Task->Execute();
}

void AIBrain::DestroyTasks() const
{
	for (AITask* t : TaskList)
		delete t;
}
