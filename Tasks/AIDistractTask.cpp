#include <tgSystem.h>

#include "AIDistractTask.h"
#include "AITaskChasePlayer.h"
#include <tgLog.h>

#include "Imported/Enemy/CEnemy.h"
#include "Imported/Player/CPlayer.h"
#include "LevelManager/CLevelManager.h"

AIDistractTask::AIDistractTask(AIBrain* Brain, tgCString Name) : AITask(Brain)
{
	m_Name = Name;
}

bool AIDistractTask::OnTaskBeginExecute()
{
	CPlayer* Player = CLevelManager::GetInstance().GetCurrentLevel()->m_pPlayer;
	CEnemy* Pawn = m_Brain->m_ControlledPawn;

	if(Player->m_DistractionAmmo)
	{
		Pawn->m_Target = Player->m_BulletManager.m_DistractionLocation;

		tgCMatrix& PawnMatrix = Pawn->GetTransform().GetMatrixLocal();
		tgCV3D EnemyToGoal = Pawn->m_Target - PawnMatrix.Pos;

		tgFloat Distance = (Pawn->GetModel()->GetTransform().GetMatrixLocal().Pos - Pawn->m_Target).Length();

		tgFloat DistractionTime = Player->m_BulletManager.m_CurrentTimeMS - Player->m_BulletManager.m_LastDistractionTime;

		if(Distance < 1.f || DistractionTime > 6.f)
		{
			return false;
		}

		PawnMatrix.At = tgCV3D(EnemyToGoal.Normalized().x, 0, EnemyToGoal.Normalized().z);
		PawnMatrix.OrthoNormalize();
		Pawn->GetVelocity().x = 2.f;

		return true;
	}
	return false;
}
