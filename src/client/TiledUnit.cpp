#include "pch.h"
#include "TiledUnit.h"
#include "Sprite.h"
#include "TiledTile.h"
#include "TiledBomb.h"
#include "TiledScene.h"
#include "Scenes.h"
#include "TiledMap.h"

namespace Client
{
TiledUnit::TiledUnit(const string & name):
	Object(ObjectType::Unit, "TiledUnit"),
	_name(name)
{
	AddObject(make_unique<Sprite>(*Sprite::List["cogollo\\full\\2.png"].get()))
			->SetID(_name);

	OnHotpatch();
}

void TiledUnit::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);
}

void TiledUnit::Tick()
{
	Object::Tick();
}

bool TiledUnit::HandleEvent(const sf::Event & ev)
{
	if(ev.type == sf::Event::KeyPressed)
	{
		using enum sf::Keyboard::Key;
		if(_self)
		{
			switch(ev.key.code)
			{
			case Left:
				Move(DirectionID::West);
				return true;

			case Up:
				Move(DirectionID::North);
				return true;

			case Right:
				Move(DirectionID::East);
				return true;

			case Down:
				Move(DirectionID::South);
				return true;

			case B:
				SetBomb();
				break;

			default: ;
			}
		}
		else
		{
			switch(ev.key.code)
			{
			case A:
				Move(DirectionID::West);
				return true;

			case W:
				Move(DirectionID::North);
				return true;

			case D:
				Move(DirectionID::East);
				return true;

			case S:
				Move(DirectionID::South);
				return true;

			case RShift:
				SetBomb();
				return true;

			default: ;
			}
		}
	}

	return Object::HandleEvent(ev);
}

void TiledUnit::SetBomb()
{
	auto bomb = (TiledBomb*)AddObject(make_unique<TiledBomb>());

	bomb->_unit = this;

	bomb->OnHotpatch();
}

void TiledUnit::SetPosition(Vector2f pos, bool update)
{
	Object::SetPosition(pos, update);
}

void TiledUnit::Move(Vector2f pos)
{
	Object::Move(pos);
}

void TiledUnit::OnHotpatch()
{
	auto obj = FindObject<Sprite>(_name);
	if(!obj)
	{
		kazin::Log::Debug("obj NOT FOUND!");
		return;
	}

	auto & sprite = obj->_sprite;

	constexpr auto kScale = 0.032f;
	sprite.setScale(kScale, kScale);

	if(_self)
		sprite.setColor(sf::Color::White);
	else
		sprite.setColor(sf::Color(200, 100, 100));
	kazin::Log::Debug("TiledUnit::OnHotpatch");
	Object::OnHotpatch();
}

void TiledUnit::UpdatePosition()
{
	if(!_map)
		return;
	kazin::Log::Debug("TiledUnit::UpdatePosition");
	Object::SetPosition(
	{
				_map->_origin.x + (_tile->_pos.x * kTileSize),
				_map->_origin.y + (_tile->_pos.y * kTileSize)
		}, false
	);

	Object::UpdatePosition();
}

void TiledUnit::Move(DirectionID dir)
{
	auto pos = _tile->_pos + direction::Delta<Vector2i>(dir);
	if(pos.x >= _map->_size.x || pos.x < 0 ||
		pos.y >= _map->_size.y || pos.y < 0)
	{
		kazin::Log::Debug("Returned {}", enum_integer(dir));
		return;
	}
	
	_map->SetUnit(this, pos);
}


TiledUnit::~TiledUnit()
{
}
}
