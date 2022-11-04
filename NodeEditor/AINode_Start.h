#pragma once
#include "AINodeObject.h"

#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

class AINode_Start : public AINodeObject
{
public:

	AINodeType GetNodeType() override;

	AINodeObject* InitializeNode() override;

	bool GetCanBeDeleted() override;

	tgCString GetNodeName() override;

	tgCColor GetNodeColor() override;

};

inline AINodeType AINode_Start::GetNodeType()
{
	return AINodeType::START;
}

inline AINodeObject* AINode_Start::InitializeNode()
{
	InputPins = 0;
	OutputPins = 1;

	return this;
}

inline bool AINode_Start::GetCanBeDeleted()
{
	return false;
}

inline tgCString AINode_Start::GetNodeName()
{
	return tgCString("Event Tick");
}

inline tgCColor AINode_Start::GetNodeColor()
{
	return tgCColor::Red;
}
