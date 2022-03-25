#pragma once
#include "Scene.h"

namespace Client
{
class TiledMap;
class Sprite;

class TiledScene final : public Scene
{
public:
	TiledScene();
	~TiledScene() override;

	void OnHotpatch() override;
	void Tick() override;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void RenderUI() override;
	bool HandleEvent(const sf::Event & ev) override;

	unique_ptr<TiledMap> _map{};
};
}
