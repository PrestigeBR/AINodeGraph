#include <tgSystem.h>
#include "AITask.h"

#include <tgTypes.h>

#include "AIBrain.h"

AITask::AITask(AIBrain* Brain)
{
	m_Brain = Brain;
}

AITask::~AITask()
{
	for (AINodeProperty* p : Properties)
		delete p;
}

bool AITask::Execute()
{
	m_LastExecuteTime = m_Brain->FrameCount;
	HasFinishedExecute = OnTaskBeginExecute();
	return HasFinishedExecute;
}

bool AITask::OnTaskBeginExecute()
{
	return false;
}
