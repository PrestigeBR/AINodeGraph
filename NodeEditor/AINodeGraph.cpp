#include <tgSystem.h>
#include "AINodeGraph.h"

#include <tgMemoryDisable.h>
#include "imgui.h"
#include "imnodes.h"
#include <tgMemoryEnable.h>

#include "AINode_Sequence.h"
#include "AINode_Start.h"
#include "AINode_Task.h"
#include "Imported/Enemy/CEnemy.h"

#include <tgLog.h>

AINodeGraph::AINodeGraph(AIBrain* Brain) : Brain(Brain)
{
}

AINodeGraph::~AINodeGraph()
{
	//UninitObjects();
	for (int i = 0; i < nodes.size(); ++i)
	{
		delete nodes[i];
		nodes[i] = nullptr;
	}
}

void AINodeGraph::Draw()
{
	/////////////////////////////////////////////////
	///
	///		GRAPH INIT
	///
	/////////////////////////////////////////////////
	
	if (MarkedForKill) return;
	if(!HasInitialized)
	{
		StartNode = new AINode_Start();
		InitObject(StartNode);
		HasInitialized = true;
	}

	/////////////////////////////////////////////////
	///
	///		GRAPH SKIP TO INTERPRET LOGIC
	///
	/////////////////////////////////////////////////

	if(!RenderUI)
		goto interp;

	/////////////////////////////////////////////////
	///
	///		GRAPH BEGIN RENDER
	///
	/////////////////////////////////////////////////

	if (ImGui::Begin("AI Node Graph"))
	{

		/////////////////////////////////////////////////
		///
		///		NODE SPAWN BUTTONS
		///
		/////////////////////////////////////////////////

		{
			if (ImGui::Button("+ AI Task Node###AddTask")) {
				AINode_Task* Object = new AINode_Task();
				InitObject(Object);
			}

			if (ImGui::Button("+ Sequence Node###AddSeq")) {
				AINode_Sequence* Object = new AINode_Sequence();
				InitObject(Object);
			}
		}

		/////////////////////////////////////////////////
		///
		///		GRAPH START
		///
		/////////////////////////////////////////////////

		ImNodes::BeginNodeEditor();

		for(AINodeObject* obj : nodes)
		{
			//AINodeType NodeType = obj->GetNodeType();

			/////////////////////////////////////////////////
			///
			///		NODE COLOR
			///
			/////////////////////////////////////////////////

			{
				tgCColor Color = obj->GetNodeColor();

				tgCColor ColorTinted = Color;

				//R
				if (ColorTinted.r >= 0.75f)
					ColorTinted.r -= 0.1f;
				else
					ColorTinted.r += 0.1f;

				//G
				if (ColorTinted.g >= 0.75f)
					ColorTinted.g -= 0.1f;
				else
					ColorTinted.g += 0.1f;

				//B
				if (ColorTinted.b >= 0.75f)
					ColorTinted.b -= 0.1f;
				else
					ColorTinted.b += 0.1f;

				ImNodes::PushColorStyle(
					ImNodesCol_TitleBar, Color);
				ImNodes::PushColorStyle(
					ImNodesCol_TitleBarSelected, ColorTinted);
				ImNodes::PushColorStyle(
					ImNodesCol_TitleBarHovered, ColorTinted);

				tgCColor PinCol = tgCColor::White;

				tgCColor PinColTinted = PinCol;

				//R
				if (PinColTinted.r >= 0.75f)
					PinColTinted.r -= 0.1f;
				else
					PinColTinted.r += 0.1f;

				//G
				if (PinColTinted.g >= 0.75f)
					PinColTinted.g -= 0.1f;
				else
					PinColTinted.g += 0.1f;

				//B
				if (PinColTinted.b >= 0.75f)
					PinColTinted.b -= 0.1f;
				else
					PinColTinted.b += 0.1f;

				ImNodes::PushColorStyle(ImNodesCol_Pin, PinCol);
				ImNodes::PushColorStyle(ImNodesCol_PinHovered, PinColTinted);
				ImNodes::PushColorStyle(ImNodesCol_Link, PinCol);
				ImNodes::PushColorStyle(ImNodesCol_LinkHovered, PinColTinted);
				ImNodes::PushColorStyle(ImNodesCol_LinkSelected, PinColTinted);
			}

			/////////////////////////////////////////////////
			///
			///		NODE START
			///
			/////////////////////////////////////////////////
			
			if(obj->NodeID != -1)
			{
				ImNodes::BeginNode(obj->NodeID);

				/////////////////////////////////////////////////
				///
				///		NODE TITLE
				///
				/////////////////////////////////////////////////

				{
					ImNodes::BeginNodeTitleBar();
					ImGui::TextColored(CLevelManager::GetInstance().GetCurrentLevel()->tgCColorToImVec4(obj->GetNodeTextColor()), tgCString("%s", obj->GetNodeName().c_str()).String());
					ImNodes::EndNodeTitleBar();
				}

				/////////////////////////////////////////////////
				///
				///		NODE INPUT & OUTPUT PINS
				///
				/////////////////////////////////////////////////

				for (int i = 0; i < obj->InputPins; ++i)
				{
					ImNodes::BeginInputAttribute(obj->InputLinkPinIDs[i]);
					ImGui::Text(" ");
					ImNodes::EndInputAttribute();
				}

				for (int i = 0; i < obj->OutputPins; ++i)
				{
					ImNodes::BeginOutputAttribute(obj->OutputLinkPinIDs[i]);
					ImGui::Text(" ");
					ImNodes::EndOutputAttribute();
				}

				/////////////////////////////////////////////////
				///
				///		NODE DELETE BUTTON
				///
				/////////////////////////////////////////////////

				if(obj->GetCanBeDeleted())
				{
					tgCString ex("Delete###%i", obj->NodeID);
					if (ImGui::Button(ex.String()))
					{
						for (int i = 0; i < nodes.size(); ++i)
						{
							if (nodes[i] == obj)
							{
							reLoop:
								for (int i3 = 0; i3 < links.size(); ++i3)
								{
									for (int i2 = 0; i2 < obj->InputPins; ++i2)
									{
										if (obj->InputLinks[i2])
										{
											int t1 = 0;
											for (AINodeObject* t : obj->InputLinks[i2]->OutputLinks)
											{
												if (t == obj)
													obj->InputLinks[i2]->OutputLinks[t1] = nullptr;
												t1++;
											}
										}
										obj->InputLinks[i2] = nullptr;
										if (links[i3].first == obj->InputLinkPinIDs[i2] || links[i3].second == obj->InputLinkPinIDs[i2])
										{
											links.erase(links.begin() + i3);
											goto reLoop;
										}
									}
									for (int i2 = 0; i2 < obj->OutputPins; ++i2)
									{
										if (obj->OutputLinks[i2])
										{
											int t1 = 0;
											for (AINodeObject* t : obj->OutputLinks[i2]->InputLinks)
											{
												if (t == obj)
													obj->OutputLinks[i2]->InputLinks[t1] = nullptr;
												t1++;
											}
										}
										obj->OutputLinks[i2] = nullptr;
										if (links[i3].first == obj->OutputLinkPinIDs[i2] || links[i3].second == obj->OutputLinkPinIDs[i2])
										{
											links.erase(links.begin() + i3);
											goto reLoop;
										}
									}
								}
								AINodeObject*& Temp = obj;
								obj = nullptr;
								delete Temp;
								nodes.erase(nodes.begin() + i);
								ImNodes::EndNode();
								ImNodes::EndNodeEditor();
								goto end;
							}
						}
					}
				}

				/////////////////////////////////////////////////
				///
				///		NODE SPECIAL UI
				///
				/////////////////////////////////////////////////

				{
					obj->RenderSpecialUI(inputID);
				}

				/////////////////////////////////////////////////
				///
				///		NODE PROPERTY INPUTS
				///
				/////////////////////////////////////////////////

				obj->DrawPropertyInputs();

				ImNodes::EndNode();
			}
		}

		/////////////////////////////////////////////////
		///
		///		NODE CREATE LINKS
		///
		/////////////////////////////////////////////////

		for (int i = 0; i < links.size(); ++i)
		{
			const std::pair<int, int> p = links[i];
			ImNodes::Link(i, p.first, p.second);
		}

		/////////////////////////////////////////////////
		///
		///		NODE END EDITOR
		///
		/////////////////////////////////////////////////

		ImNodes::EndNodeEditor();

		/////////////////////////////////////////////////
		///
		///		NODE (UNUSED) REMOVE LINK CODE
		///
		/////////////////////////////////////////////////

		//Check for new links
		//int linkId;
		//if(ImNodes::IsLinkDestroyed(&linkId))
		//{
		//	for (int i = 0; i < nodes.size(); ++i)
		//	{
		//		for (int i2 = 0; i2 < nodes[i]->OutputPins; ++i2)
		//		{
		//			if(linkId == nodes[i]->OutputLinkPinIDs[i2])
		//			{
		//				nodes[i]->OutputLinks[i2] = nullptr;
		//			}
		//		}
		//		for (int i2 = 0; i2 < nodes[i]->InputPins; ++i2)
		//		{
		//			if (linkId == nodes[i]->InputLinkPinIDs[i2])
		//			{
		//				nodes[i]->InputLinks[i2] = nullptr;
		//			}
		//		}
		//	}
		//}

		/////////////////////////////////////////////////
		///
		///		NODE STORE LINKS
		///
		/////////////////////////////////////////////////

		{
			int start_attr, end_attr;
			if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
			{
				bool b = false;
				for (int i = 0; i < links.size(); ++i)
				{
					if (links[i].first == start_attr)
					{
						links[i].second = end_attr;
						b = true;
					}
					if (links[i].second == end_attr)
					{
						links[i].first = start_attr;
						b = true;
					}
				}
				if (!b)
					links.push_back(std::make_pair(start_attr, end_attr));
			}
		}

	}

	/////////////////////////////////////////////////
	///
	///		GRAPH END
	///
	/////////////////////////////////////////////////

	end:
	ImGui::End();

	/////////////////////////////////////////////////
	///
	///		GRAPH VIRTUALIZE GRAPH TO LINKED LIST
	///
	/////////////////////////////////////////////////

	interp:
	UpdateObjectLinks();
}

/////////////////////////////////////////////////
///
///		INITIALIZE NODE
///
/////////////////////////////////////////////////

void AINodeGraph::InitObject(AINodeObject* Object)
{
	AINodeObject* Obj = Object->InitializeNode();

	Obj->AllocateDefaultPins(inputID);

	nodes.push_back(Obj);
}

/////////////////////////////////////////////////
///
///		UNINITIALIZE NODES
///
/////////////////////////////////////////////////

void AINodeGraph::UninitObjects()
{
	MarkForKill();
	for (int i = 0; i < nodes.size(); ++i)
	{
		if(nodes[i])nodes[i]->CleanupNode();
		AINodeObject*& TempNode = nodes[i];
		nodes[i] = nullptr;
		delete TempNode;
	}
}

/////////////////////////////////////////////////
///
///		VIRTUALIZE TO LINKED LIST
///
/////////////////////////////////////////////////

void AINodeGraph::UpdateObjectLinks()
{
	for (int i = 0; i < links.size(); ++i)
	{
		int outLink = links[i].first;
		int inLink = links[i].second;

		for(AINodeObject* obj : nodes)
		{
			//Input
			for (int i2 = 0; i2 < obj->InputPins; ++i2)
			{
				if(obj->InputLinkPinIDs[i2] == inLink)
				{
					for (AINodeObject* c_obj : nodes)
					{
						for (int i3 = 0; i3 < c_obj->OutputPins; ++i3)
						{
							if (c_obj->OutputLinkPinIDs[i3] == outLink)
							{
								obj->InputLinks[i2] = c_obj;
								c_obj->OutputLinks[i3] = obj;
							}
						}
					}
				}
			}

			//Output
			for (int i2 = 0; i2 < obj->OutputPins; ++i2)
			{
				if (obj->OutputLinkPinIDs[i2] == inLink)
				{
					for (AINodeObject* c_obj : nodes)
					{
						for (int i3 = 0; i3 < c_obj->InputPins; ++i3)
						{
							if (c_obj->OutputLinkPinIDs[i3] == outLink)
							{
								obj->OutputLinks[i2] = c_obj;
								c_obj->InputLinks[i3] = obj;
							}
						}
					}
				}
			}
			obj->MarkDirty();
		}
	}
}

/////////////////////////////////////////////////
///
///		START LOGIC INTERPRETATION
///
/////////////////////////////////////////////////

void AINodeGraph::InterpretLogicFromNodeGraph(AIBrain* Brain)
{
	CurrentObject = StartNode->OutputLinks[0];
	while (CurrentObject != nullptr)
	{
		AINodeType Type = CurrentObject->GetNodeType();

		InterpLogic(Brain);
	}
}

/////////////////////////////////////////////////
///
///		GETTERS / SETTERS
///
/////////////////////////////////////////////////

void AINodeGraph::MarkForKill()
{
	MarkedForKill = true;
}

bool AINodeGraph::GetHasInitialized()
{
	return HasInitialized;
}

bool AINodeGraph::GetCanRenderUI()
{
	return RenderUI;
}

void AINodeGraph::SetCanRenderUI(bool val)
{
	RenderUI = val;
}

/////////////////////////////////////////////////
///
///		INTERNAL LOGIC INTERPRETATION
///
/////////////////////////////////////////////////

void AINodeGraph::InterpLogic(AIBrain* Brain)
{
	if (!CurrentObject) return;

	CurrentObject = CurrentObject->ExecuteNodeLogicOnInterpretation(Brain);
}
