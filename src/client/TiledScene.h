#pragma once
#include "Scene.h"

namespace Client
{
struct TiledMap;
struct Sprite;

struct TiledScene final : Scene
{
	TiledScene();
	~TiledScene() override;

	void OnHotpatch() override;
	void Tick() override;
	using Scene::Render;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void RenderUI() override;
	using Scene::HandleEvent;
	bool HandleEvent(const sf::Event & ev) override;

	unique_ptr<TiledMap> _map{};
};
}
