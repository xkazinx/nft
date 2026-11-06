#pragma once
#include "Scene.h"

namespace Client
{
struct GenScene final : Scene
{
	GenScene();
	~GenScene() override;
	void SetPosition(Vector2f pos, bool update) override;
	void UpdatePosition() override;
	void Move(Vector2f pos) override;
	void RenderUI() override;
	void OnHotpatch() override;
	void Tick() override;
	using Scene::Render;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	using Scene::HandleEvent;
	bool HandleEvent(const sf::Event & ev) override;

	bool my_tool_active = true;
};
}
