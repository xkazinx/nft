#include "pch.h"
#include "Scenes.h"
#include "DummyScene.h"
#include "TiledScene.h"
#include "GenScene.h"

namespace Client
{
Scenes::Scenes() :
	Object(ObjectType::Scenes, "Scenes")
{
	ID first = ID::Gen;
	if(lib::init::Has("scene"))
	{
		// by name, any case: scene=pacman (the tiled map), scene=gen, scene=dummy
		string name = lib::init::Value("scene");
		ranges::transform(name, name.begin(), [](const unsigned char c) { return (char)std::tolower(c); });
		for(const auto id : enum_values<ID>())
		{
			string id_name(enum_name(id));
			ranges::transform(id_name, id_name.begin(), [](const unsigned char c) { return (char)std::tolower(c); });
			if(id_name == name || (name == "tiled" && id == ID::PacMan))
				first = id;
		}
		_last_id = first;
	}

	Set(first);
}

Scenes::~Scenes()
{
	_manager._current = nullptr;
}

void Scenes::Set(const ID id)
{
	auto scene = Create(id);
	_manager.Set(*scene);
	_scene = std::move(scene);

	Info("scene {}", enum_name(id)); // (the web test waits for it)
}

void Scenes::OnHotpatch()
{
	Object::OnHotpatch();

	if(_scene)
		_scene->OnHotpatch();
}

void Scenes::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);

	_manager.Render();

	if(_scene)
		_scene->RenderUI();
}

void Scenes::Tick()
{
	Object::Tick();

	_manager.Tick();
}

bool Scenes::HandleEvent(const sf::Event & ev)
{
	bool next = KeyPressed(ev) == sf::Keyboard::Key::S && CtrlHeld(ev);
#ifdef __EMSCRIPTEN__
	// A browser keeps Ctrl+S (save the page) for itself: N there too
	next = next || KeyPressed(ev) == sf::Keyboard::Key::N;
#endif
	if(next)
	{
		if(++_last_id >= enum_count<ID>())
		{
			_last_id = enum_values<ID>()[0];
		}

		Set(ID(_last_id));
	}

	return _scene && _scene->HandleEvent(ev);
}

unique_ptr<Scene> Scenes::Create(ID id)
{
	switch(id)
	{
		using enum ID;

	case Dummy:
		return make_unique<DummyScene>();

	case PacMan:
		return make_unique<TiledScene>();

	case Gen:
		return make_unique<GenScene>();

	case None:
	default: ;
		break;
	}

	return make_unique<Scene>();
}
}
