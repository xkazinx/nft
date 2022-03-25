#include "pch.h"

// nft
#include "App.h"
#include "SceneMgr.h"

#ifdef LIVEPP
#include <LPP_API.h>

void lppPrePatch()
{
}

void lppPostPatch()
{
	Print("LivePP: Patch");
	g_cmd->Setup();
}

LPP_PREPATCH_HOOK(lppPrePatch);
LPP_POSTPATCH_HOOK(lppPostPatch);
#endif

namespace Client
{
App::App() // NOLINT(cppcoreguidelines-pro-type-member-init)
{
#ifdef LIVEPP
	_livePP = lpp::lppLoadAndRegister(L"D:\\LIBPATH\\LivePP", "nft");
	lpp::lppEnableAllCallingModulesAsync(_livePP);
#endif

	g_app = this;

	Global::Initialize();

	InitializeWindow(g_res_x, g_res_y);

	ImGui::SFML::Init(_window);
}

App::~App() // NOLINT(modernize-use-equals-default)
{
	ImGui::SFML::Shutdown();

	Global::Deinitialize();

#ifdef LIVEPP
	lpp::lppShutdown(_livePP);
	::FreeLibrary(_livePP);
#endif
}

void App::ToggleConsole()
{
	const HWND hwnd  = GetConsoleWindow();
	int        state = SW_SHOW;

	if(::IsWindowVisible(hwnd))
		state = SW_HIDE;

	ShowWindow(hwnd, state);
}

void App::InitializeWindow([[maybe_unused]] const u16 res_x, [[maybe_unused]] u16 res_y)
{
	ContextSettings settings;
	{
		settings.depthBits         = 0;
		settings.stencilBits       = 0;
		settings.antialiasingLevel = 0;
		settings.majorVersion      = 3;
		settings.minorVersion      = 2;
	}

	_window.create(VideoMode(g_res_x, g_res_y), kAppName, sf::Style::None, settings);

	_window.setVisible(true);
	_window.setActive(true);
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(120);

	AdjustViewport(_window.getSize().x, _window.getSize().y);
}

void App::AdjustViewport(const GLsizei & x, const GLsizei & y)
{
	glViewport(0, 0, x, y);
}

int App::Tick()
{
	sf::Clock delta_clock;

	while(_window.isOpen())
	{
		time::Tick();

		if(!HandleEvents())
			break;

		{
			g_scene->Tick();

			ImGui::SFML::Update(_window, delta_clock.restart());
		}

		{
			_window.clear(sf::Color::Black);

			{
				g_scene->Render(_window, {});

				ImGui::SFML::Render(_window);
			}

			_window.display();
		}

		this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return 0;
}

bool App::HandleEvents()
{
	sf::Event ev;

	while(_window.pollEvent(ev))
	{
		ImGui::SFML::ProcessEvent(ev);

		if(ev.type == sf::Event::Closed)
		{
			_window.close();
			return false;
		}

		if(ev.type == sf::Event::Resized)
		{
			AdjustViewport(ev.size.width, ev.size.height);
		}
		else
		{
			if(g_scene->HandleEvent(ev))
				return true;
		}
	}

	return true;
}
}
