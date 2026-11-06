#include "pch.h"

// nft
#include "App.h"
#include "Scenes.h"
#include "Sprite.h"

namespace Client
{
App::App()
{
	g_app = this;

	Global::Initialize();

	InitializeWindow(g_res_x, g_res_y);

#if NFT_IMGUI
	lib::imgui::Init(_window);
#endif

	// (the web test waits for this line)
	Info("{} ready: {} pictures, scene {}", kAppName, Sprite::List.size(), enum_name(g_scenes->_scene->_id));
}
App::~App()
{
#if NFT_IMGUI
	lib::imgui::Shutdown();
#endif

	Global::Deinitialize();
}

void App::InitializeWindow([[maybe_unused]] const u16 res_x, [[maybe_unused]] u16 res_y)
{
	ContextSettings settings;
	{
		settings.depthBits         = 0;
		settings.stencilBits       = 0;
		settings.antiAliasingLevel = 0;
#ifndef __EMSCRIPTEN__ // a browser gets its WebGL2 context
		settings.majorVersion      = 3;
		settings.minorVersion      = 2;
#endif
	}

	_window.create(VideoMode({ g_res_x, g_res_y }), kAppName, sf::Style::None, sf::State::Windowed, settings);

	_window.setVisible(true);
	if(!_window.setActive(true))
		Warn("the window's OpenGL context could not be made current");
#ifndef __EMSCRIPTEN__ // a browser paces display() by its animation frames
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(120);
#endif
}

bool App::Frame()
{
	time::Tick();

	if(!HandleEvents())
		return false;

	{
		g_scenes->Tick();

#if NFT_IMGUI
		ImGui::SFML::Update(_window, _delta_clock.restart());
#endif
	}

	{
		_window.clear(sf::Color::Black);

		{
			g_scenes->Render(_window, {});

#if NFT_IMGUI
			lib::imgui::End(_window);
#endif
		}

		_window.display();
	}

	return true;
}

int App::Tick()
{
	while(_window.isOpen())
	{
		if(!Frame())
			break;

#ifndef __EMSCRIPTEN__ // in a browser display() already yielded to the page
		this_thread::sleep_for(std::chrono::milliseconds(1));
#endif
	}

	return 0;
}

bool App::HandleEvents()
{
	while(const optional<sf::Event> ev = _window.pollEvent())
	{
#if NFT_IMGUI
		ImGui::SFML::ProcessEvent(*ev);
#endif

		if(ev->is<sf::Event::Closed>())
		{
			_window.close();
			return false;
		}

		// (Resized: SFML 3 sets the viewport from the view on every draw; the old
		// glViewport call is gone)
		if(!ev->is<sf::Event::Resized>())
		{
			if(g_scenes->HandleEvent(*ev))
				return true;
		}
	}

	return true;
}
}
