#pragma once
#include "Object.h"
#include "Sprite.h"

namespace Client
{
struct TiledTile;
struct TiledUnit;

struct TiledBomb final : Object
{
	TiledBomb();
	~TiledBomb() override;

	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void Tick() override;
	bool HandleEvent(const sf::Event & ev) override;
	void OnHotpatch() override;
	void SetPosition(Vector2f pos, bool update) override;
	void Move(Vector2f pos) override;
	using Object::UpdatePosition;
	void UpdatePosition() override;

	void UpdatePosition(const TiledUnit * unit);
	void Explode();

	sf::CircleShape _circle;
	TiledUnit *     _unit = nullptr;

	time::Timer _tm{ 1500 };
};
}
