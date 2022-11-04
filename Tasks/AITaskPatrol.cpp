#include <tgSystem.h>
#include "AITaskPatrol.h"
#include <tgCModel.h>

#include "Imported/Enemy/CEnemy.h"

AITaskPatrol::AITaskPatrol(AIBrain* Brain, tgCString Name) : AITask(Brain)
{
	m_Name = Name;
}

bool AITaskPatrol::OnTaskBeginExecute()
{
	CEnemy* Pawn = m_Brain->m_ControlledPawn;

	tgCMatrix& PawnMatrix = Pawn->GetTransform().GetMatrixLocal();

	Pawn->m_Target = Pawn->m_PatrolPoints[Pawn->m_PatrolIndex];

	tgCV3D EnemyToGoal = Pawn->m_Target - PawnMatrix.Pos;

	//PawnMatrix.Pos = PawnMatrix.Pos + Pawn->m_Target.Normalized() * m_Brain->m_DeltaTime;
	PawnMatrix.At = tgCV3D(EnemyToGoal.Normalized().x, 0, EnemyToGoal.Normalized().z);
	PawnMatrix.OrthoNormalize();
	Pawn->GetVelocity().x = 1.f;

	tgFloat Distance = (Pawn->m_PatrolPoints[Pawn->m_PatrolIndex] - PawnMatrix.Pos).Length();

	if(Distance < 1.f)
	{
		Pawn->m_PatrolIndex++;
		if (Pawn->m_PatrolIndex >= Pawn->m_PatrolPoints.size()) Pawn->m_PatrolIndex = 0;
	}

	return true;
}
