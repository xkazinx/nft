#pragma once
#include "Object.h"
#include "Sprite.h"
#include "TiledBomb.h"

namespace Client
{
struct TiledTile;
struct TiledMap;

struct TiledUnit final : Object
{
	TiledUnit(const string & name);

	~TiledUnit() override;
	void UpdatePosition() override;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;

	void Tick() override;
	bool HandleEvent(const sf::Event & ev) override;
	void OnHotpatch() override;

	void Move(DirectionID dir);
	void SetBomb();

	void SetPosition(Vector2f pos, bool update = false) override;
	void Move(Vector2f pos) override;

	TiledTile *        _tile = nullptr;
	string             _name;
	TiledMap *         _map = nullptr;
	bool               _self = false;
	static inline bool _adding_unit = false;
};
}
