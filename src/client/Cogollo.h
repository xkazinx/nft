#pragma once
#include "NFT.h"

namespace Client
{
class Cogollo : public NFT
{
public:
	Cogollo();
	~Cogollo() override;
	
	void OnHotpatch() override;
	void Tick() override;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states = {}) override;
	bool HandleEvent(const sf::Event & ev) override;
	void SetPosition(Vector2f pos, bool update) override;
	void UpdatePosition() override;
	void Move(Vector2f pos) override;
};
}
