#pragma once
#include "Object.h"

namespace Client
{
struct TiledTile;
struct TiledUnit;

struct TiledMap final : Object
{
	explicit TiledMap(const string & map_name = "");
	~TiledMap() override;

	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void Tick() override;
	bool HandleEvent(const sf::Event & ev) override;
	void OnHotpatch() override;
	void SetPosition(Vector2f pos, bool update) override;
	void UpdatePosition() override;
	void Move(Vector2f pos) override;

	string   _map_name;
	Vector2i _size;
	Vector2f _origin{ 200.f, 100.f };

	bool Load(const string & map_name);

	// TiledTile
	vector<unique_ptr<TiledTile>> _tiles;

	unique_ptr<TiledTile> & Get(Vector2i pos);

	// TiledUnit
	vector<unique_ptr<TiledUnit>> _units;

	TiledUnit * AddUnit(unique_ptr<TiledUnit> unit);
	void        SetUnit(TiledUnit * unit, Vector2i);
};
}
