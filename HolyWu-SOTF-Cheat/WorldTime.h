#pragma once
#include <cstdint>

class WorldTime
{
public:
	char pad_0000[32]; //0x0000
	uint32_t m_days; //0x0020
	uint32_t m_hours; //0x0024
	uint32_t m_minutes; //0x0028
	uint32_t m_seconds; //0x002C
	uint64_t m_ms; //0x0030
	uint32_t m_mms_lol; //0x0038
	uint32_t m_unk_0x3C; //0x003C
	char pad_0040[24]; //0x0040
	uint64_t m_times; //0x0058
	char pad_0060[32]; //0x0060
	float m_unk_0x80; //0x0080
	float m_unk_0x84; //0x0084
	uint32_t pad_0x88; //0x0088
	float m_unk_0x8C; //0x008C
	double m_unk_0x90; //0x0090
	bool m_unk_0x98; //0x0098
	bool m_unk_0x99; //0x0099
	char pad_009A[38]; //0x009A
}; //Size: 0x00C0
static_assert(sizeof(WorldTime) == 0xC0);