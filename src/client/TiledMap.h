#pragma once
#include "Object.h"

namespace Client
{
class TiledTile;
class TiledUnit;

class TiledMap final : public Object
{
public:
	explicit TiledMap(const string & map_name = "");
	~TiledMap() override = default;

	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void Tick() override;
	bool HandleEvent(const sf::Event & ev) override;
	void OnHotpatch() override;
	void SetPosition(Vector2f pos, bool update) override;
	void UpdatePosition() override;
	void Move(Vector2f pos) override;

public:
	string   _map_name;
	Vector2i _size;
	Vector2f _origin{ 200.f, 100.f };

	bool Load(const string & map_name);

private: // TiledTile
	vector<unique_ptr<TiledTile>> _tiles;

public:
	unique_ptr<TiledTile> & Get(Vector2i pos);


private: // TiledUnit
	vector<unique_ptr<TiledUnit>> _units;

public:
	TiledUnit * AddUnit(unique_ptr<TiledUnit> unit);
	void         SetUnit(TiledUnit * unit, Vector2i);
};
}
