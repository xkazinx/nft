#pragma once
#include "Scene.h"

namespace Client
{
// The scenes: one at a time in kazilib's scene manager (scene/manager.h); Ctrl+S
// makes the next one. Startup flag scene=gen|pacman|dummy (gen by default).
struct Scenes final : Object
{
	using ID = SceneID;

	Scenes();
	~Scenes() override;

	void OnHotpatch() override;
	void Tick() override;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	bool HandleEvent(const sf::Event & ev) override;

	unique_ptr<Scene> Create(ID id);
	// Replaces the current scene with a new one of `id`
	void Set(ID id);

	lib::scene::Manager       _manager;
	unique_ptr<Scene>         _scene;
	underlying_type_t<ID>     _last_id = enum_values<ID>()[0]; // the one Ctrl+S counts from
};
}
