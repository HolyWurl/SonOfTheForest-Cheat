#pragma once
#include <cstdint>

class CPlayerStateData
{
public:
	char pad_0000[176]; //0x0000
	class CPlayerPower* m_player_power; //0x00B0
	class CPlayerMaxEnergy* m_player_maxenergy; //0x00B8
	class CPlayerHealth* m_player_health; //0x00C0
	class CPlayerEnergy* m_player_energy; //0x00C8
	class CPlayerWater* m_player_water; //0x00D0
	class CPlayerFood* m_player_food; //0x00D8
	class CPlayerSleep* m_player_sleep; //0x00E0
	class CPlayerUnk* m_player_unk; //0x00E8
	char pad_00F0[3984]; //0x00F0
}; //Size: 0x1080
static_assert(sizeof(CPlayerStateData) == 0x1080);

class CPlayerWater
{
public:
	char pad_0000[16]; //0x0000
	float m_current; //0x0010
	char pad_0014[116]; //0x0014
}; //Size: 0x0088
static_assert(sizeof(CPlayerWater) == 0x88);

class CPlayerEnergy
{
public:
	char pad_0000[16]; //0x0000
	float m_current; //0x0010
	char pad_0014[116]; //0x0014
}; //Size: 0x0088
static_assert(sizeof(CPlayerEnergy) == 0x88);

class CPlayerHealth
{
public:
	char pad_0000[16]; //0x0000
	float m_current; //0x0010
	char pad_0014[116]; //0x0014
}; //Size: 0x0088
static_assert(sizeof(CPlayerHealth) == 0x88);

class CPlayerPower
{
public:
	char pad_0000[16]; //0x0000
	float m_current; //0x0010
	char pad_0014[116]; //0x0014
}; //Size: 0x0088
static_assert(sizeof(CPlayerPower) == 0x88);

class CPlayerMaxEnergy
{
public:
	char pad_0000[16]; //0x0000
	float m_current; //0x0010
	char pad_0014[116]; //0x0014
}; //Size: 0x0088
static_assert(sizeof(CPlayerMaxEnergy) == 0x88);

class CPlayerUnk
{
public:
	char pad_0000[16]; //0x0000
	float m_unk; //0x0010
	char pad_0014[116]; //0x0014
}; //Size: 0x0088
static_assert(sizeof(CPlayerUnk) == 0x88);

class CPlayerFood
{
public:
	char pad_0000[16]; //0x0000
	float m_current; //0x0010
	char pad_0014[116]; //0x0014
}; //Size: 0x0088
static_assert(sizeof(CPlayerFood) == 0x88);

class CPlayerSleep
{
public:
	char pad_0000[16]; //0x0000
	float m_current; //0x0010
	char pad_0014[116]; //0x0014
}; //Size: 0x0088
static_assert(sizeof(CPlayerSleep) == 0x88);