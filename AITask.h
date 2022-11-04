#pragma once
#include <tgCString.h>
#include <tgTypes.h>

#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

struct AINodeProperty;
class AIBrain;

class AITask
{

public:
	AITask(AIBrain* Brain);
	~AITask();

	bool Execute();

	bool HasFinishedExecute = false;

	tgCString m_Name = "MISSINGNO";

	AIBrain* m_Brain = nullptr;

	tgFloat m_LastExecuteTime = 0.f;

	std::vector<AINodeProperty*> Properties;

protected:
	virtual bool OnTaskBeginExecute();

};

