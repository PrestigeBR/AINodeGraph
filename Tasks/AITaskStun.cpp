#include <tgSystem.h>
#include "AITaskStun.h"

#include <tgTypes.h>

#include <tgLog.h>

#include "Imported/Enemy/CEnemy.h"

AITaskStun::AITaskStun(AIBrain* Brain, tgCString Name) : AITask(Brain)
{
	m_Name = Name;
	AINodeProperty* Prop = new AINodeProperty();
	Prop->PropertyName = tgCString("Stun Time");
	Prop->Type = AINodePropertyType::PROPERTY_FLOAT;
	Properties.push_back(Prop);
}

bool AITaskStun::OnTaskBeginExecute()
{
	CEnemy* Pawn = m_Brain->m_ControlledPawn;

	if (Pawn->m_IsStunned)
	{
		if (Pawn->m_StunTimer <= 0.f) {
			Pawn->m_IsStunned = false;
			Pawn->m_StunTimer = Properties[0]->FloatValue;
			return false;
		}
		Pawn->m_StunTimer -= 1.f * Pawn->m_DeltaTime;
		Pawn->GetVelocity().x = 0.f;
		return true;
	}
	return false;
}
