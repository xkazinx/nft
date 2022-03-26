#pragma once
#include "Scene.h"

namespace Client
{
class GenScene final : public Scene
{
public:
	GenScene();
	~GenScene() override;
	void SetPosition(Vector2f pos, bool update) override;
	void UpdatePosition() override;
	void Move(Vector2f pos) override;
	void RenderUI() override;
	void OnHotpatch() override;
	void Tick() override;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	bool HandleEvent(const sf::Event & ev) override;
};
}
