//========= Copyright � Valve LLC, All rights reserved. =======================
//
// Purpose:		
//
// $NoKeywords: $
//=============================================================================

#include "cbase.h"
#include "tf_shareddefs.h"
#include "eyeball_boss_approach.h"
#include "eyeball_boss_rockets.h"

extern ConVar tf_eyeball_boss_attack_range;
extern ConVar tf_eyeball_boss_speed;


CEyeBallBossApproachTarget::CEyeBallBossApproachTarget()
{
}


const char *CEyeBallBossApproachTarget::GetName( void ) const
{
	return "ApproachTarget";
}


ActionResult<CEyeBallBoss> CEyeBallBossApproachTarget::OnStart( CEyeBallBoss *me, Action<CEyeBallBoss> *priorAction )
{
	m_targetDuration.Start( 5.0f );
	m_keepTargetDuration.Start( 0.5f );

	return Action<CEyeBallBoss>::Continue();
}

ActionResult<CEyeBallBoss> CEyeBallBossApproachTarget::Update( CEyeBallBoss *me, float dt )
{
	CBaseCombatCharacter *pVictim = me->GetVictim();
	if( pVictim != me->FindNearestVisibleVictim() && m_keepTargetDuration.IsElapsed() )
		return Action<CEyeBallBoss>::Done( "Noticed better victim" );

	if ( !pVictim || !pVictim->IsAlive() )
		return Action<CEyeBallBoss>::Done( "Victim gone..." );

	if ( m_targetDuration.IsElapsed() )
		return Action<CEyeBallBoss>::Done( "Giving up..." );
	
	if ( !me->IsLineOfSightClear( pVictim, CBaseCombatCharacter::IGNORE_ACTORS ) && m_targetVerifyTimer.IsElapsed() )
		return Action<CEyeBallBoss>::Done( "Lost victim..." );

	m_targetVerifyTimer.Start( 1.0f );

	float flRange = tf_eyeball_boss_attack_range.GetFloat();
	if ( me->GetTeamNumber() != TF_TEAM_NPC ||
			me->GetHealth() < ( me->GetMaxHealth() / 3 ) ||
			( me->m_attitudeTimer.HasStarted() && !me->m_attitudeTimer.IsElapsed() ) )
	{
		flRange *= 2;
	}

	if ( me->IsRangeLessThan( pVictim, flRange ) )
		return Action<CEyeBallBoss>::ChangeTo( new CEyeBallBossLaunchRockets, "Rocket attack!" );

	CEyeBallBossLocomotion *pLoco = (CEyeBallBossLocomotion *)me->GetLocomotionInterface();
	pLoco->SetDesiredSpeed( tf_eyeball_boss_speed.GetFloat() );
	pLoco->Approach( pVictim->WorldSpaceCenter() );

	return Action<CEyeBallBoss>::Continue();
}
