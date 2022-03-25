#pragma once
#include "Object.h"
#include "Sprite.h"

namespace Client
{
class TiledTile;
class TiledUnit;

class TiledBomb final : public Object
{
public:
	TiledBomb();
	~TiledBomb() override;

	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void Tick() override;
	bool HandleEvent(const sf::Event & ev) override;
	void OnHotpatch() override;
	void SetPosition(Vector2f pos, bool update) override;
	void Move(Vector2f pos) override;
	void UpdatePosition() override;

public:
	void UpdatePosition(const TiledUnit * unit);
	void Explode();

	sf::CircleShape _circle;
	TiledUnit *    _unit = nullptr;

	time::Timer _tm{ 1500 };
};
}
