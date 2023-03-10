#include "includes.h"
#include "hooking.h"
#include "memory/module.hpp"
#include "pointers.h"
#include "kiero/minhook/include/MinHook.h"
#include <thread>
#include <emmintrin.h>

hooking::hooking() :
	m_get_leaf_call_hook("get_leaf_call", g_pointers->m_get_leaf_call, &hooks::hk_get_leaf_call),
	m_local_player_data_hook("local_player_data", g_pointers->m_local_player_data, &hooks::hk_local_player_data),
	m_item_amount_hook("item_amount", g_pointers->m_item_amount, &hooks::hk_item_amount),
	m_patch_fov_hook("patch_fov", g_pointers->m_patch_fov, &hooks::hk_patch_fov),
	m_player_func_hook("player_func", g_pointers->m_player_func, &hooks::hk_player_func),
	m_world_time_hook("world_time", g_pointers->m_world_time, &hooks::hk_world_time)
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
	m_patch_fov_hook.enable();
	m_player_func_hook.enable();
	m_world_time_hook.enable();
	m_enabled = true;
}

void hooking::disable()
{
	m_enabled = false;

	m_get_leaf_call_hook.disable();
	m_local_player_data_hook.disable();
	m_item_amount_hook.disable();
	m_patch_fov_hook.disable();
	m_player_func_hook.disable();
	m_world_time_hook.disable();
}

minhook_keepalive::minhook_keepalive()
{
	MH_Initialize();
}

minhook_keepalive::~minhook_keepalive()
{
	//MH_Uninitialize();
}

__int64 hooks::hk_local_player_data(CPlayerStateData* a1)
{
	sets::p_player_state_data = a1;
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

__int64 hooks::hk_item_amount(__int64 a1, uint32_t a2)
{
	auto ret = g_hooking->m_item_amount_hook.get_original<decltype(&hk_item_amount)>()(a1, a2);
	if (sets::item_bool)
	{
		return sets::item_amount;
	}
	return ret;
}

void hooks::hk_patch_fov(__int64 a1, float a2)
{
	if (sets::is_modify_fov)
	{
		a2 = sets::fov_value;
	}
	g_hooking->m_patch_fov_hook.get_original<decltype(&hk_patch_fov)>()(a1, a2);
}

bool hooks::hk_player_func(UPlayerData* data, float* a2, bool a3)
{
	auto ret = g_hooking->m_player_func_hook.get_original<decltype(&hk_player_func)>()(data, a2, a3);
	if (sets::is_modify_pos)
	{
		data->m_position_x = sets::pos_x;
		data->m_position_y = sets::pos_y;
		data->m_position_z = sets::pos_z;
		sets::is_modify_pos = false;
	}
	return ret;
}
__int64 hooks::hk_world_time(WorldTime* time, uint64_t* a2, bool a3)
{
	auto ret = g_hooking->m_world_time_hook.get_original<decltype(&hk_world_time)>()(time, a2, a3);
	if (time)
	{
		if (sets::is_modify_time)
		{
			time->m_times = (uint64_t)sets::set_minute * 600000000;
			sets::is_modify_time = false;
		}
		sets::current_minute = time->m_times / 600000000;
	}
	return ret;
}
