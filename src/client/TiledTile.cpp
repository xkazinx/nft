#include "pch.h"
#include "TiledTile.h"
#include "TiledUnit.h"
#include "TiledMap.h"

namespace Client
{
TiledMap * TiledTile::CurrentMap = nullptr;

TiledTile::TiledTile(tile::Type id, tile::Flag flag):
	Object(ObjectType::Tile, "TiledTile"),
	_type(id),
	_flag(flag),
	_vertexes(sf::PrimitiveType::LineStrip, 4)
{
	//OnHotpatch();
}

TiledTile::TiledTile(const string & data) :
	Object(ObjectType::Tile, "TiledTile")
{
	szt i = 0;
	for(auto flag : enum_values<tile::Flag>())
		if(data[i++] == '1')
			_flag |= flag;

	OnHotpatch();
}

TiledTile::~TiledTile()
{
}

void TiledTile::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	tgt.draw(_square, states);

	Object::Render(tgt, states);

	if(_unit)
		_unit->Render(tgt, states);
}

void TiledTile::Tick()
{
	Object::Tick();
}

bool TiledTile::HandleEvent(const sf::Event & ev)
{
	return Object::HandleEvent(ev);
}

void TiledTile::OnHotpatch()
{
	_square.setSize({ kTileSize, kTileSize });
	_square.setFillColor(sf::Color::Transparent);
	_square.setOutlineColor(sf::Color::Yellow);
	_square.setOutlineThickness(1.f);

	Object::OnHotpatch();
}

void TiledTile::SetPosition(Vector2f pos, bool update)
{
	_square.setPosition(pos);

	kazin::Log::Debug("pos{} {}", pos.x, pos.y);
	if(update && _unit)
		_unit->UpdatePosition();

	Object::SetPosition(pos, update);
}

void TiledTile::Move(Vector2f pos)
{
	if(_unit)
		_unit->Move(pos);

	Object::Move(pos);
}

void TiledTile::UpdatePosition()
{
	if(CurrentMap)
	{
		SetPosition({
			            CurrentMap->_origin.x + (_pos.x * kTileSize),
			            CurrentMap->_origin.y + (_pos.y * kTileSize)
		            }, false);
	}

	if(_unit)
		_unit->UpdatePosition();

	Object::UpdatePosition();
}
}
