#include "includes.h"
#include "detour_hook.h"
#include "memory/handle.hpp"
#include "kiero/minhook//include/MinHook.h"


detour_hook::detour_hook(std::string name, void* target, void* detour) :
	m_name(std::move(name)),
	m_target(target),
	m_detour(detour)
{
	fix_hook_address();

	if (auto status = MH_CreateHook(m_target, m_detour, &m_original); status == MH_OK)
	{
		std::cout << "Created hook '" << m_name << "'."<<std::endl;
	}
	else
	{
		//throw std::runtime_error(fmt::format("Failed to create hook '{}' at 0x{:X} (error: {})", m_name, reinterpret_cast<std::uintptr_t>(m_target), MH_StatusToString(status)));
	}
}

detour_hook::~detour_hook() noexcept
{
	if (m_target)
	{
		MH_RemoveHook(m_target);
	}
	
	std::cout << "Removed hook '" << m_name << "'." << std::endl;
}

void detour_hook::enable()
{
	if (auto status = MH_EnableHook(m_target); status == MH_OK)
	{
		std::cout << "Enabled hook '" << m_name << "'." << std::endl;
	}
	else
	{
		//throw std::runtime_error(fmt::format("Failed to enable hook 0x{:X} ({})", reinterpret_cast<std::uintptr_t>(m_target), MH_StatusToString(status)));
	}
}

void detour_hook::disable()
{
	if (auto status = MH_DisableHook(m_target); status == MH_OK)
	{
		std::cout << "Disabled hook '" << m_name << "'." << std::endl;
	}
	else
	{
		std::cout << "Failed to disable hook '" << m_name << "'." << std::endl;
	}
}

DWORD exp_handler(PEXCEPTION_POINTERS exp, std::string const& name)
{
	return exp->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION
		? EXCEPTION_EXECUTE_HANDLER
		: EXCEPTION_CONTINUE_SEARCH;
}

void detour_hook::fix_hook_address()
{
	__try
	{
		auto ptr = memory::handle(m_target);
		while (ptr.as<std::uint8_t&>() == 0xE9)
		{
			ptr = ptr.add(1).rip();
		}

		m_target = ptr.as<void*>();
	}
	__except (exp_handler(GetExceptionInformation(), m_name))
	{
		[this]()
		{
			//throw std::runtime_error(fmt::format("Failed to fix hook address for '{}'", m_name));
		}();
	}
}

