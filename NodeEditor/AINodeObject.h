#pragma once
#include "AIBrain/AITask.h"

#include <tgMemoryDisable.h>
#include <vector>
#include <string>
#include <tgMemoryEnable.h>

enum AINodeType
{
	NONE,
	START
};

enum AINodePropertyType
{
	PROPERTY_FLOAT,
	PROPERTY_BOOL,
};

struct AINodeProperty
{
	AINodePropertyType Type = PROPERTY_FLOAT;
	std::string PropertyName = "Default Value";
	float FloatValue = 0.f;
	bool BoolValue = false;
};

class AINodeObject
{
public:
	int NodeID = -1;

	int InputPins = 0;
	int OutputPins = 0;

	std::vector<int> InputLinkPinIDs;
	std::vector<int> OutputLinkPinIDs;

	std::vector<AINodeObject*> InputLinks;
	std::vector<AINodeObject*> OutputLinks;

	std::vector<AINodeProperty*> Properties;

	//NODE

	virtual void AllocateDefaultPins(int& InputID);

	virtual AINodeObject* InitializeNode();

	virtual void CleanupNode();

	virtual AINodeType GetNodeType();

	virtual AINodeObject* ExecuteNodeLogicOnInterpretation(AIBrain* Brain);

	virtual void DrawPropertyInputs();

	virtual void MarkDirty();

	//GRAPH RENDERING

	virtual std::string GetNodeName();

	virtual tgCColor GetNodeColor();

	virtual tgCColor GetNodeTextColor();

	virtual bool GetCanBeDeleted();

	virtual void RenderSpecialUI(int& inputID);

	//

};
