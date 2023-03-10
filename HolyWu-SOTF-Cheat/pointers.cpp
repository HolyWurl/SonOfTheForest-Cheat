#include "includes.h"
#include "pointers.h"
#include "memory/all.hpp"


pointers::pointers()
{
	memory::pattern_batch main_batch;
	main_batch.add("get_leaf_call", "E8 ? ? ? ? EB 1D 48 85 C0", [this](memory::handle ptr)
	{
		m_get_leaf_call = ptr.add(1).rip().as<void*>();
	});
	main_batch.add("local_player_data", "E8 ? ? ? ? EB 52 4D 85 C0", [this](memory::handle ptr)
	{
		m_local_player_data = ptr.add(1).rip().as<void*>();
	});
	main_batch.add("patch_wood", "E8 ? ? ? ? 0F 29 74 24 ? 40 84 F6", [this](memory::handle ptr)
	{
		m_patch_wood = ptr.add(1).rip().add(0x13B).as<void*>();
	});
	main_batch.add("item_amount", "E8 ? ? ? ? 3B 43 70", [this](memory::handle ptr)
	{
		m_item_amount = ptr.add(1).rip().as<void*>();
	});
	main_batch.add("world_time", "E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? B0 01 0F 28 B4 24", [this](memory::handle ptr)
	{
		m_world_time = ptr.add(1).rip().as<void*>();
	});
	main_batch.run(memory::module("GameAssembly.dll"));

	memory::pattern_batch unityplayer_batch;
	unityplayer_batch.add("patch_fov", "E8 ? ? ? ? 44 89 BE ? ? ? ? 49 8B 0C DE", [this](memory::handle ptr)
	{
		m_patch_fov = ptr.add(1).rip().as<void*>();
	});
	unityplayer_batch.add("player_func", "48 8B C4 48 89 58 10 48 89 68 18 56 57 41 56 48 81 EC ? ? ? ? 0F 29 70 D8", [this](memory::handle ptr)
	{
		m_player_func = ptr.as<void*>();
	});
	unityplayer_batch.run(memory::module("UnityPlayer.dll"));

	g_pointers = this;
}

pointers::~pointers()
{
	g_pointers = nullptr;
}
