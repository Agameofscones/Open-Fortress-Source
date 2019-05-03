//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======
//
//
//=============================================================================
#ifndef TF_WEAPON_SMG_H
#define TF_WEAPON_SMG_H
#ifdef _WIN32
#pragma once
#endif

#include "tf_weaponbase_gun.h"

// Client specific.
#ifdef CLIENT_DLL
#define CTFSMG C_TFSMG
#define CTFSMG_Mercenary C_TFSMG_Mercenary
#define CTFTommyGun C_TFTommyGun
#define CTFAssaultRifle C_TFAssaultRifle
#endif

//=============================================================================
//
// TF Weapon Sub-machine gun.
//
class CTFSMG : public CTFWeaponBaseGun
{
public:

	DECLARE_CLASS( CTFSMG, CTFWeaponBaseGun );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

// Server specific.
#ifdef GAME_DLL
	DECLARE_DATADESC();
#endif

	CTFSMG() {}
	~CTFSMG() {}

	
	virtual int		GetWeaponID( void ) const			{ return TF_WEAPON_SMG; }

private:

	CTFSMG( const CTFSMG & ) {}
};

// Mercenary specific version
class CTFSMG_Mercenary : public CTFSMG
{
public:
	DECLARE_CLASS( CTFSMG_Mercenary, CTFSMG );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	virtual int		GetWeaponID( void ) const			{ return TF_WEAPON_SMG_MERCENARY; }
};

// TommyGun version
class CTFTommyGun : public CTFSMG
{
public:
	DECLARE_CLASS( CTFTommyGun, CTFSMG );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	virtual int		GetWeaponID( void ) const			{ return TF_WEAPON_TOMMYGUN; }
};

// AR
class CTFAssaultRifle : public CTFSMG
{
public:
	DECLARE_CLASS(CTFAssaultRifle, CTFSMG);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	
	CTFAssaultRifle() 
	{
		m_bInBurst = false;
	}
	
	virtual int		GetWeaponID(void) const { return TF_WEAPON_ASSAULTRIFLE; }

	virtual int		GetBurstSize( void ) { return 3; };
	void			BurstThink( void );
	void			PrimaryAttack( void );
	void			BasePrimaryAttack( void );
	
	virtual float	GetBurstCycleRate( void ) { return 0.5; }
	
protected:
	int		m_iBurstSize;
	bool	m_bInBurst;
};


#endif // TF_WEAPON_SMG_H
