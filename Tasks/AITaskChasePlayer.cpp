#include <tgSystem.h>
#include "AITaskChasePlayer.h"

#include "Imported/CLevel.h"
#include "Imported/Enemy/CEnemy.h"
#include "Imported/Player/CPlayer.h"

AITaskChasePlayer::AITaskChasePlayer(AIBrain* Brain, tgCString Name) : AITask(Brain)
{
	m_Name = Name;
}

bool AITaskChasePlayer::OnTaskBeginExecute()
{
	CPlayer* Player = CLevel::GetInstance().m_pPlayer;
	CEnemy* Pawn = m_Brain->m_ControlledPawn;

	Pawn->m_Target = Player->GetTransform().GetMatrixLocal().Pos;

	tgCMatrix& PawnMatrix = Pawn->GetTransform().GetMatrixLocal();
	tgCV3D EnemyToGoal = Pawn->m_Target - PawnMatrix.Pos;

	PawnMatrix.At = tgCV3D(EnemyToGoal.Normalized().x, 0, EnemyToGoal.Normalized().z);
	PawnMatrix.OrthoNormalize();
	Pawn->GetVelocity().x = 2.f;

    return true;
}
