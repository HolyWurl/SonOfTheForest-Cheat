#pragma once
#include <cstdint>

class UPlayerData
{
public:
	char pad_0000[104]; //0x0000
	uint32_t m_unk68; //0x0068
	char pad_006C[64]; //0x006C
	uint32_t m_unkAC; //0x00AC
	char pad_00B0[144]; //0x00B0
	float m_heading1; //0x0140
	float m_heading2; //0x0144
	float m_heading3; //0x0148
	float m_heading4; //0x014C
	float m_position_x; //0x0150
	float m_position_y; //0x0154
	float m_position_z; //0x0158
	char pad_015C[116]; //0x015C
}; //Size: 0x01D0
static_assert(sizeof(UPlayerData) == 0x1D0);