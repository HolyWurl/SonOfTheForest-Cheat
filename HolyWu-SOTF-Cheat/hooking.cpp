#include "includes.h"
#include "hooking.h"
#include "memory/module.hpp"
#include "pointers.h"
#include "kiero/minhook//include/MinHook.h"
#include <thread>

hooking::hooking() :
	m_get_leaf_call_hook("get_leaf_call", g_pointers->m_get_leaf_call, &hooks::hk_get_leaf_call),
	m_local_player_data_hook("local_player_data", g_pointers->m_local_player_data, &hooks::hk_local_player_data),
	m_item_amount_hook("item_amount", g_pointers->m_item_amount, &hooks::hk_item_amount)
{
	g_hooking = this;
}

hooking::~hooking()
{
	//if (m_enabled)
	//	disable();
	
	g_hooking = nullptr;
}

void hooking::enable()
{
	m_get_leaf_call_hook.enable();
	m_local_player_data_hook.enable();
	m_item_amount_hook.enable();
	m_enabled = true;
}

void hooking::disable()
{
	m_enabled = false;

	m_get_leaf_call_hook.disable();
	m_local_player_data_hook.disable();
	m_item_amount_hook.disable();
}

minhook_keepalive::minhook_keepalive()
{
	MH_Initialize();
}

minhook_keepalive::~minhook_keepalive()
{
	//MH_Uninitialize();
}

__int64 hooks::hk_local_player_data(void* a1)
{
	sets::p_player_state_data = (CPlayerStateData*)a1;
	return g_hooking->m_local_player_data_hook.get_original<decltype(&hk_local_player_data)>()(a1);
}

bool hooks::hk_get_leaf_call(__int64 a1, uint32_t a2, uint32_t amount, bool a4)
{
	if (sets::is_modify_leaf)
	{
		amount = sets::leaf_amount;
	}
	
	return g_hooking->m_get_leaf_call_hook.get_original<decltype(&hk_get_leaf_call)>()(a1, a2, amount, a4);
}

__int64 hooks::hk_item_amount(__int64 a1, unsigned int a2)
{
	auto ret = g_hooking->m_item_amount_hook.get_original<decltype(&hk_item_amount)>()(a1, a2);
	if (sets::item_bool)
	{
		return sets::item_amount;
	}
	return ret;
}