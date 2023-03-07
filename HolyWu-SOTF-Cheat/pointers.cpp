#include "includes.h"
#include "pointers.h"
#include "memory/all.hpp"


pointers::pointers()
{
	memory::pattern_batch main_batch;
	main_batch.add("get_leaf_call", "E8 ? ? ? ? EB 1B 48 8B 48 20", [this](memory::handle ptr)
	{
		m_get_leaf_call = ptr.add(1).rip().as<void*>();
	});
	main_batch.add("local_player_data", "40 53 48 83 EC 70 0F 29 74 24 ? 33 D2", [this](memory::handle ptr)
	{
		m_local_player_data = ptr.as<void*>();
	});
	main_batch.add("patch_wood", "E8 ? ? ? ? 0F 29 74 24 ? 84 DB", [this](memory::handle ptr)
	{
		m_patch_wood = ptr.add(1).rip().add(0x15B).as<void*>();
	});
	main_batch.add("item_amount", "E8 ? ? ? ? 3B 43 70", [this](memory::handle ptr)
	{
		m_item_amount = ptr.add(1).rip().as<void*>();
	});
	
	main_batch.run(memory::module("GameAssembly.dll"));

	g_pointers = this;
}

pointers::~pointers()
{
	g_pointers = nullptr;
}
