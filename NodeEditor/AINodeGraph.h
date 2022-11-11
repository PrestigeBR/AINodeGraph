#pragma once
#include <tgMemoryDisable.h>
#include <vector>
#include <tgMemoryEnable.h>

#include "AINodeObject.h"

class AINodeGraph
{
	AIBrain* Brain;

	bool HasInitialized = false;

	AINodeObject* StartNode = nullptr;

	std::vector<AINodeObject*> nodes;
	std::vector<std::pair<int, int>> links;

	int inputID = 0;

	bool RenderUI = false;

	bool MarkedForKill = false;

	//Logic interpretation
	AINodeObject* CurrentObject = nullptr;

public:

	AINodeGraph(AIBrain* Brain);
	~AINodeGraph();

	void Draw();

	void InitObject(AINodeObject* Object);

	void UninitObjects();

	void UpdateObjectLinks();

	void InterpretLogicFromNodeGraph(AIBrain* Brain);

	void MarkForKill();

	bool GetHasInitialized();

	bool GetCanRenderUI();
	void SetCanRenderUI(bool val);

private:
	void InterpLogic(AIBrain* Brain);

};
