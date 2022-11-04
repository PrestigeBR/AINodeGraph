#include <tgSystem.h>
#include "AITaskLookForPlayer.h"

#include "AIBrain/AIBrain.h"
#include "Imported/CLevel.h"
#include "Imported/Enemy/CEnemy.h"
#include "Imported/Player/CPlayer.h"

#include <tgLog.h>

AITaskLookForPlayer::AITaskLookForPlayer(AIBrain* Brain, tgCString Name) : AITask(Brain)
{
	m_Name = Name;
	AINodeProperty* Prop = new AINodeProperty();
	Prop->PropertyName = tgCString("Eye Sight Check");
	Prop->Type = AINodePropertyType::PROPERTY_BOOL;
	Properties.push_back(Prop);
}

bool AITaskLookForPlayer::OnTaskBeginExecute()
{
	CPlayer* Player = CLevel::GetInstance().m_pPlayer;
	CEnemy* Pawn = m_Brain->m_ControlledPawn;

	//Change Enemy to PhysicsObject
	tgFloat Distance = (Pawn->GetModel()->GetTransform().GetMatrixLocal().Pos - Player->GetTransform().GetMatrixLocal().Pos).Length();

	tgFloat Angle = -Pawn->GetModel()->GetTransform().GetMatrixLocal().At.DotProduct(Pawn->GetModel()->GetTransform().GetMatrixLocal().Pos - Player->GetTransform().GetMatrixLocal().Pos);

	if(Angle > 0.f)
	{
		if(Distance < Pawn->m_EyeSightLength && Properties[0]->BoolValue)
		{
			Pawn->m_Target = Player->GetTransform().GetMatrixLocal().Pos;
			return true;
		}
	}
	else if(Player->m_DistractionAmmo)
	{
		return false;
	}

	Pawn->GetVelocity().x = 0.f;
	return false;
}
