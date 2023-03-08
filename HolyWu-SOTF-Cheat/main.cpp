#include "includes.h"
#include "kiero/minhook/include/MinHook.h"
#include "hooking.h"
#include "pointers.h"
#define IsKeyPressed(key) GetAsyncKeyState(key) & 0x8000
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
ImFont* chinese;
bool g_running = true;
bool opened = false;
void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
	chinese = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/simhei.ttf", 17.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
auto tick = GetTickCount64();

namespace ImGui
{
	void TipsHelper(const char* tip)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(tip);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetTickCount64() - tick > 500 && IsKeyPressed(VK_INSERT))
	{
		tick = GetTickCount64();
		opened ^= true;
	}
	if (opened)
	{
		ImGui::Begin("HolyWu的森林之子作弊");
		if (sets::p_player_state_data &&
			sets::p_player_state_data->m_player_health &&
			sets::p_player_state_data->m_player_energy &&
			sets::p_player_state_data->m_player_water &&
			sets::p_player_state_data->m_player_food &&
			sets::p_player_state_data->m_player_sleep
			)
		{
			ImGui::PushItemWidth(500);
			ImGui::SliderFloat("生命值", &sets::p_player_state_data->m_player_health->m_current, 0, 9999, "%.1f");
			ImGui::SliderFloat("体力", &sets::p_player_state_data->m_player_energy->m_current, 0, 100, "%.1f");
			ImGui::SliderFloat("水", &sets::p_player_state_data->m_player_water->m_current, 0, 100, "%.1f");
			ImGui::SliderFloat("食物", &sets::p_player_state_data->m_player_food->m_current, 0, 100, "%.1f");
			ImGui::SliderFloat("精神", &sets::p_player_state_data->m_player_sleep->m_current, 0, 100, "%.1f");
			ImGui::PopItemWidth();

			ImGui::Checkbox("无限丢弃(刷木头等)", &sets::patch_wood);
			ImGui::Checkbox("无限物品", &sets::item_bool);
			ImGui::SameLine();
			ImGui::PushItemWidth(250);
			ImGui::InputInt("欲设置数量", &sets::item_amount);
			ImGui::PopItemWidth();

			ImGui::Checkbox("树叶收集机", &sets::is_modify_leaf);
			ImGui::SameLine();
			ImGui::PushItemWidth(250);
			ImGui::InputInt("欲收集数量", &sets::leaf_amount);
			ImGui::PopItemWidth();

			ImGui::Checkbox("自定义视角(FOV)", &sets::is_modify_fov);
			ImGui::SameLine();
			ImGui::PushItemWidth(250);
			ImGui::InputInt("值", &sets::fov_value);
			ImGui::PopItemWidth();
			ImGui::SameLine();
			ImGui::TipsHelper("填写后进入游戏设置随意修改一下即可触发");
			
			ImGui::PushItemWidth(160);
			ImGui::InputFloat("X", &sets::pos_x, 0.1f, 1, 1);
			ImGui::SameLine();
			ImGui::InputFloat("Y", &sets::pos_y, 0.1f, 1, 1);
			ImGui::SameLine();
			ImGui::InputFloat("Z", &sets::pos_z, 0.1f, 1, 1);
			ImGui::PopItemWidth();
			ImGui::SameLine();
			if (ImGui::Button("传送到该坐标"))
			{
				sets::is_modify_pos = true;
			}

			ImGui::Text("时间(分):%d", sets::current_minute);
			ImGui::SameLine();
			ImGui::PushItemWidth(160);
			ImGui::InputInt("欲设置时间(分)", &sets::set_minute);
			ImGui::PopItemWidth();
			ImGui::SameLine();
			if (ImGui::Button("设置"))
			{
				sets::is_modify_time = true;
				sets::time_set_count = 0;
			}

		}
		else
		{
			ImGui::Text("等待进入游戏");
		}
		ImGui::End();
	}

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI run(LPVOID lpReserved)
{
	if (AllocConsole()) {
		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		SetConsoleTitleW(L"SOTF Cheat by HolyWu");
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
	}

	auto pointers_instance = std::make_unique<pointers>();
	std::cout << "sig scan success!" << std::endl;
	auto hooking_instance = std::make_unique<hooking>();
	std::cout << "create hooking success!" << std::endl;
	g_hooking->enable();
	std::cout << "enable all hooks success!" << std::endl;

	bool init_hook = false;
	do
	{
		if (!init_hook && kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			std::cout << "dx hook success!" << std::endl;
			init_hook = true;
		}
		if (IsKeyPressed(VK_END))
		{
			g_running = false;
		}
		if (sets::patch_wood)
		{
			byte newBytes[] = { 0x90, 0x90, 0x90 };
			PDWORD O;
			if (VirtualProtect(g_pointers->m_patch_wood, sizeof(newBytes) + 1, PAGE_EXECUTE_READWRITE, (PDWORD)&O) != 0)
			{
				if (memcmp(g_pointers->m_patch_wood, newBytes, sizeof(newBytes)) != 0)
				{
					memcpy(g_pointers->m_patch_wood, newBytes, sizeof(newBytes));
				}
			}
		}
		else
		{
			byte newBytes[] = { 0xFF, 0x4E, 0x5C };
			PDWORD O;
			if (VirtualProtect(g_pointers->m_patch_wood, sizeof(newBytes) + 1, PAGE_EXECUTE_READWRITE, (PDWORD)&O) != 0)
			{
				if (memcmp(g_pointers->m_patch_wood, newBytes, sizeof(newBytes)) != 0)
				{
					memcpy(g_pointers->m_patch_wood, newBytes, sizeof(newBytes));
				}
			}
		}
		Sleep(100);
	} while (g_running);

	SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	kiero::shutdown();

	fclose(stdout);
	FreeConsole();
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpReserved), 0);
	return true;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, run, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}