#pragma once
#include "AINodeObject.h"

#include "Imported/Enemy/CEnemy.h"
#include "LevelManager/CLevelManager.h"

class AINode_Task : public AINodeObject
{
public:
	AITask* Task = nullptr;

	AINodeObject* Prev = nullptr;
	AINodeObject* True = nullptr;
	AINodeObject* False = nullptr;

	void MarkDirty() override;

	AINodeType GetNodeType() override;

	void AllocateDefaultPins(int& InputID) override;

	void RenderSpecialUI(int& inputID) override;

	AINodeObject* InitializeNode() override;

	AINodeObject* ExecuteNodeLogicOnInterpretation(AIBrain* Brain) override;

	std::string GetNodeName() override;

	tgCColor GetNodeColor() override;

	void DrawPropertyInputs() override;

};

inline void AINode_Task::MarkDirty()
{
	AINodeObject::MarkDirty();

	if (InputLinks[0])
		Prev = InputLinks[0];

	if (OutputLinks[0])
		True = OutputLinks[0];

	if (OutputLinks[1])
		False = OutputLinks[1];

}

inline AINodeType AINode_Task::GetNodeType()
{
	return AINodeType::NONE;
}

inline void AINode_Task::AllocateDefaultPins(int& InputID)
{
	AINodeObject::AllocateDefaultPins(InputID);
}

inline void AINode_Task::RenderSpecialUI(int& inputID)
{
	tgCString in("###%s%i", Task->m_Name, NodeID);
	if (ImGui::BeginCombo("", Task->m_Name.c_str(), ImGuiComboFlags_NoPreview))
	{
		for (AITask* TItem : CLevelManager::GetInstance().GetCurrentLevel()->m_pEnemy->TaskList)
		{
			tgBool isSelected = TItem->m_Name.c_str() == Task->m_Name.c_str();

			if (ImGui::Selectable(TItem->m_Name.c_str(), isSelected))
			{
				Task = TItem;
			}
		}
		ImGui::EndCombo();
	}
	tgCString s2("Class: %s", Task->m_Name);
	ImGui::TextColored(CLevelManager::GetInstance().GetCurrentLevel()->tgCColorToImVec4(tgCColor::White), s2.String());
}

inline AINodeObject* AINode_Task::InitializeNode()
{
	Task = CLevelManager::GetInstance().GetCurrentLevel()->m_pEnemy->TaskList[0];

	InputPins = 1;
	OutputPins = 2;

	return this;
}

inline AINodeObject* AINode_Task::ExecuteNodeLogicOnInterpretation(AIBrain* Brain)
{
	if (Brain->ExecuteTask(Task))
	{
		return True;
	}
	return False;
}

inline std::string AINode_Task::GetNodeName()
{
	return Task->m_Name;
}

inline tgCColor AINode_Task::GetNodeColor()
{
	return tgCColor::Lime;
}

inline void AINode_Task::DrawPropertyInputs()
{
	if (Task)
	{
		Properties = Task->Properties;
	}
	AINodeObject::DrawPropertyInputs();
}
