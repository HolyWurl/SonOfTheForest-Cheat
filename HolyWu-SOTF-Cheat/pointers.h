#pragma once
#include "includes.h"

class pointers
{
public:
	explicit pointers();
	~pointers();
public:
	void* m_get_leaf_call{};
	void* m_local_player_data{};
	void* m_patch_wood{};
	void* m_item_amount{};
	void* m_patch_fov{};
	void* m_player_func{};
	void* m_world_time{};
};

inline pointers* g_pointers{};
