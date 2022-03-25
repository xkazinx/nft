#pragma once
#include "Scene.h"

namespace Client
{
class DummyScene final : public Scene
{
public:
	DummyScene();
	~DummyScene() override;

	void OnHotpatch() override;
	void Tick() override;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void RenderUI() override;
	bool HandleEvent(const sf::Event & ev) override;
};
}
