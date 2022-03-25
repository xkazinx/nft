#pragma once
#include "Object.h"
#include "TiledMap.h"

namespace Client
{
class TiledUnit;
class TiledMap;

class TiledTile final : public Object
{
public:
	static TiledMap * CurrentMap;

	explicit TiledTile(const string & data);
	explicit TiledTile(tile::Type id = tile::Type::Land, tile::Flag flag = {});

	~TiledTile() override;

	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void Tick() override;
	bool HandleEvent(const sf::Event & ev) override;
	void OnHotpatch() override;
	void SetPosition(Vector2f pos, bool update) override;
	void Move(Vector2f pos) override;
	void UpdatePosition() override;

public:
	Vector2i                      _pos{};
	tile::Type                    _type;
	underlying_type_t<tile::Flag> _flag{};

	TiledUnit *   _unit = nullptr;
	RectangleShape _square;

	sf::VertexArray _vertexes;
};
}
