#include "pch.h"
#include "TiledBomb.h"
#include "Sprite.h"
#include "TiledTile.h"
#include "TiledUnit.h"

namespace Client
{
TiledBomb::TiledBomb():
	Object(ObjectType::Object, "TiledBomb")
{

}

TiledBomb::~TiledBomb()
{
	Explode();
}

void TiledBomb::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);

	tgt.draw(_circle, states);
}

void TiledBomb::Tick()
{
	Object::Tick();

	if(_tm.GetPercentLeft() < 25)
	{
		_circle.setFillColor(sf::Color::Yellow);	
	}

	if(_tm.Fire(false))
	{
		Explode();
	}
}

bool TiledBomb::HandleEvent(const sf::Event & ev)
{
	return Object::HandleEvent(ev);
}

void TiledBomb::OnHotpatch()
{
	_circle.setRadius(kTileSize / 4);
	_circle.setFillColor(sf::Color::Red);
	
	Object::OnHotpatch();
}

void TiledBomb::UpdatePosition()
{
	UpdatePosition(_unit);

	Object::UpdatePosition();
}

void TiledBomb::SetPosition(Vector2f pos, bool update)
{
	_circle.setPosition(pos);

	Object::SetPosition(pos, update);
}

void TiledBomb::Move(Vector2f pos)
{
	_circle.move(pos);
	
	Object::Move(pos);
}

void TiledBomb::UpdatePosition(const TiledUnit * unit)
{
	kazin::Log::Error("TiledBomb::UpdatePosition");
	SetPosition({unit->_map->_origin.x + unit->_tile->_pos.x * kTileSize + (kTileSize / 4),
		unit->_map->_origin.y + unit->_tile->_pos.y * kTileSize + (kTileSize / 4)}, false);
}

void TiledBomb::Explode()
{
	_circle.setFillColor(sf::Color::Transparent);
}
}