#pragma once
#include <tgCColor.h>

#include "AINodeObject.h"

#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

class AINode_Sequence : public AINodeObject
{
public:

	int SeqPins = 0;

	void AddPinLink(int& InputID);

	AINodeType GetNodeType() override;

	AINodeObject* InitializeNode() override;

	AINodeObject* ExecuteNodeLogicOnInterpretation(AIBrain* Brain) override;

	void RenderSpecialUI(int& inputID) override;

	std::string GetNodeName() override;

	tgCColor GetNodeColor() override;

};

inline void AINode_Sequence::AddPinLink(int& InputID)
{
	OutputLinks.push_back(nullptr);
	OutputLinkPinIDs.push_back(InputID);
	OutputPins++;
	SeqPins++;
	InputID++;
}

inline AINodeType AINode_Sequence::GetNodeType()
{
	return AINodeType::NONE;
}

inline AINodeObject* AINode_Sequence::InitializeNode()
{
	InputPins = 1;
	OutputPins = 0;

	return this;
}

inline AINodeObject* AINode_Sequence::ExecuteNodeLogicOnInterpretation(AIBrain* Brain)
{
	for (int i = 0; i < OutputPins; ++i)
	{
		if(OutputLinks[i]) return OutputLinks[i]->ExecuteNodeLogicOnInterpretation(Brain);
	}
	return nullptr;
}

inline void AINode_Sequence::RenderSpecialUI(int& inputID)
{
	if(ImGui::Button(tgCString("+ Add pin##%i", NodeID).String())) {
		AddPinLink(inputID);
	}
}

inline std::string AINode_Sequence::GetNodeName()
{
	return "Sequence";
}

inline tgCColor AINode_Sequence::GetNodeColor()
{
	return tgCColor::Gray;
}
