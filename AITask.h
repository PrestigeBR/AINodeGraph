#pragma once

#include <tgMemoryDisable.h>
#include <vector>
#include <string>
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

	std::string m_Name = "MISSINGNO";

	AIBrain* m_Brain = nullptr;

	float m_LastExecuteTime = 0.f;

	std::vector<AINodeProperty*> Properties;

protected:
	virtual bool OnTaskBeginExecute();

};

