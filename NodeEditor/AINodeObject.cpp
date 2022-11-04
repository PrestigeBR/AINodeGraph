#include <tgSystem.h>
#include "AINodeObject.h"

#include <tgCColor.h>
#include <tgMemoryDisable.h>
#include "imgui.h"
#include <tgMemoryEnable.h>

void AINodeObject::AllocateDefaultPins(int& InputID)
{
	NodeID = InputID;
	InputID++;

	for (int i = 0; i < InputPins; ++i)
	{
		InputLinkPinIDs.push_back(InputID);
		InputLinks.push_back(nullptr);
		InputID++;
	}
	for (int i = 0; i < OutputPins; ++i)
	{
		OutputLinkPinIDs.push_back(InputID);
		OutputLinks.push_back(nullptr);
		InputID++;
	}

}

void AINodeObject::MarkDirty()
{
	//
}

void AINodeObject::DrawPropertyInputs()
{
	if(Properties.size() > 0)
	{
		int i = 10000;
		ImGui::PushItemWidth(48.f);
		ImGui::NewLine();
		ImGui::TextColored(ImVec4(255, 255, 255, 255), "Property Inputs:");
		for (AINodeProperty* p : Properties)
		{
			tgCString inputName("##%i%i", NodeID, i);
			if (p->Type == PROPERTY_FLOAT)
			{
				ImGui::TextColored(ImVec4(0, 255, 0, 255), " o");
				ImGui::SameLine();
				float f = p->FloatValue;
				if (ImGui::InputFloat(inputName.String(), &f))
				{
					p->FloatValue = f;
				}
			}
			if (p->Type == PROPERTY_BOOL)
			{
				ImGui::TextColored(ImVec4(255, 0, 0, 255), " o");
				ImGui::SameLine();
				bool b = p->BoolValue;
				if (ImGui::Checkbox(inputName.String(), &b))
				{
					p->BoolValue = !p->BoolValue;
				}
			}
			//char* c = p->StringValue;
			//if (p->Type == PROPERTY_STRING)
			//{
			//	if(ImGui::InputText(inputName.String(), c, sizeof(p->StringValue)))
			//	{
			//		p->StringValue = c;
			//	}
			//}
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 255, 255), p->PropertyName.String());
			i++;
		}
		ImGui::PopItemWidth();
	}
}

AINodeType AINodeObject::GetNodeType()
{
	return AINodeType::NONE;
}

void AINodeObject::CleanupNode()
{
	for (int i = 0; i < Properties.size(); ++i)
	{
		delete Properties[i];
		Properties[i] = nullptr;
	}
	for (int i = 0; i < InputLinks.size(); ++i)
	{
		delete InputLinks[i];
		InputLinks[i] = nullptr;
	}
	for (int i = 0; i < OutputLinks.size(); ++i)
	{
		delete OutputLinks[i];
		OutputLinks[i] = nullptr;
	}
}

AINodeObject* AINodeObject::InitializeNode()
{
	return this;
}

AINodeObject* AINodeObject::ExecuteNodeLogicOnInterpretation(AIBrain* Brain)
{
	if(OutputPins > 0)
	{
		return OutputLinks[0];
	}
	return nullptr;
}

tgCString AINodeObject::GetNodeName()
{
	return tgCString("Default Node");
}

tgCColor AINodeObject::GetNodeColor()
{
	return tgCColor::Gray;
}

tgCColor AINodeObject::GetNodeTextColor()
{
	return tgCColor::White;
}

bool AINodeObject::GetCanBeDeleted()
{
	return true;
}

void AINodeObject::RenderSpecialUI(int& inputID)
{
	//
}
