#include "../includes.h"
#include "pattern_batch.hpp"
#include "range.hpp"
#define HEX_TO_UPPER(value) "0x" << std::hex << std::uppercase << (DWORD64)value << std::dec << std::nouppercase
namespace memory
{
	void pattern_batch::add(std::string name, pattern pattern, std::function<void(handle)> callback)
	{
		m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));
	}

	void pattern_batch::run(range region)
	{
		bool all_found = true;
		for (auto& entry : m_entries)
		{
			if (auto result = region.scan(entry.m_pattern))
			{
				if (entry.m_callback)
				{
					std::invoke(std::move(entry.m_callback), result);
					//std::cout << "Found '" << entry.m_name << "'Deadly.dll+" << HEX_TO_UPPER(result.as<DWORD64>() - region.begin().as<DWORD64>()) << std::endl;
				}
				else
				{
					all_found = false;
					std::cout  << "Failed to find '" << entry.m_name << "'." << std::endl;
				}
			}
			else
			{
				all_found = false;
				std::cout << "Failed to find '" << entry.m_name << "'." << std::endl;
			}
		}

		m_entries.clear();
		if (!all_found)
		{
			throw std::runtime_error("Failed to find some patterns.");
		}
	}
}
