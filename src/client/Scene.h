#pragma once
#include <scene/manager.h> // kazilib: lib::scene::Base / Manager
#include "Object.h"

namespace Client
{
// The next-scene key's hint (Scenes::HandleEvent)
#ifdef __EMSCRIPTEN__
constexpr char kNextSceneKeys[] = "N: next scene";
#else
constexpr char kNextSceneKeys[] = "Ctrl+S: next scene";
#endif

// A scene: an Object (its children drawn, ticked and given the events) and one of
// kazilib's scenes (Scenes holds it in a lib::scene::Manager)
struct Scene : Object, lib::scene::Base
{
	virtual void RenderUI();

	explicit Scene(SceneID id = SceneID::None);
	~Scene() override = default;

	virtual void OnHotpatch() override;
	void Tick() override;
	using Object::Render;
	virtual void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	using Object::HandleEvent;
	virtual bool HandleEvent(const sf::Event & ev) override;

	// kazilib's scene calls: the frame on the window, an sf::Event behind the pointer
	void Render() override;
	void HandleEvent(const void * event) override;

	const SceneID _id{};
	// The scene's keys, a line at the bottom of the window
	string _keys = kNextSceneKeys;
};
}
