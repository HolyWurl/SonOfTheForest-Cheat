#pragma once
#include "includes.h"
#include "detour_hook.h"
#include <emmintrin.h>

struct hooks
{
	static bool hk_get_leaf_call(__int64 a1, uint32_t a2, uint32_t amount, bool a4);
	static __int64 hk_local_player_data(CPlayerStateData* a1);
	static __int64 hk_item_amount(__int64 a1, uint32_t a2);
	static void hk_patch_fov(__int64 a1, float a2);
	static bool hk_player_func(UPlayerData* a1, float* a2, bool a3);
	static __int64 hk_world_time(WorldTime* time, uint64_t* a2, bool a3);
};
struct minhook_keepalive
{
	minhook_keepalive();
	~minhook_keepalive();
};

class hooking
{
	friend hooks;
public:
	explicit hooking();
	~hooking();

	void enable();
	void disable();

private:
	bool m_enabled{};
	minhook_keepalive m_minhook_keepalive;
	detour_hook m_get_leaf_call_hook;
	detour_hook m_local_player_data_hook;
	detour_hook m_item_amount_hook;
	detour_hook m_patch_fov_hook;
	detour_hook m_player_func_hook;
	detour_hook m_world_time_hook;
};

inline hooking* g_hooking{};
