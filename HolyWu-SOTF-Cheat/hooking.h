#pragma once
#include "includes.h"
#include "detour_hook.h"

struct hooks
{
	static bool hk_get_leaf_call(__int64 a1, uint32_t a2, uint32_t amount, bool a4);
	static __int64 hk_local_player_data(void* a1);
	static __int64 hk_item_amount(__int64 a1, unsigned int a2);
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
};

inline hooking* g_hooking{};