#include "pch.h"
#include "TiledMap.h"
#include "TiledTile.h"
#include "TiledUnit.h"

namespace Client
{
TiledMap::TiledMap(const string & map_name) :
	Object(ObjectType::Map, "TiledMap")
{
	Load(map_name);

	{
		auto unit = AddUnit(make_unique<TiledUnit>(
			format("Cogollo {}", _units.size() + 1)
		));

		unit->_self = true;

		SetUnit(unit, { 0, 0 });
	}

	{
		auto unit = AddUnit(make_unique<TiledUnit>(
			format("Cogollo {}", _units.size() + 1)
		));

		unit->_self = false;

		SetUnit(unit, { 6, 6 });
	}
}

TiledMap::~TiledMap()
= default;

TiledUnit * TiledMap::AddUnit(unique_ptr<TiledUnit> unit)
{
	auto object = AddObject(make_unique<Sprite>(*Sprite::List["cogollo/full/1.png"].get()));

	((Sprite*)object)->SetID(unit->_name);

	_units.emplace_back(std::move(unit));

	return _units.back().get();
}

bool TiledMap::Load(const string & map_name)
{
	_map_name = map_name;

	std::ifstream file(_map_name);
	if(!file.is_open())
		return false;

	szt idx = 0;
	string data;
	// (was `while(!eof) file >> data`: the read past the last word made one more
	// tile from an empty word, its flags read past the string's end)
	while(file >> data)
	{
		switch(idx++)
		{
		case 0:
			_size.x = stoi(data);
			break;

		case 1:
			_size.y = stoi(data);
			break;

		default:
			_tiles.push_back(make_unique<TiledTile>(data));
			break;
		}
	}

	{
		Vector2i i;
		for(i.x = 0; i.x < _size.x; ++i.x)
			for(i.y = 0; i.y < _size.y; ++i.y)
			{
				Get(i)->_pos = i;

				TiledTile::CurrentMap = this;
				Get(i)->UpdatePosition();
				TiledTile::CurrentMap = nullptr;
			}
	}

	return true;
}

unique_ptr<TiledTile> & TiledMap::Get(Vector2i pos)
{
	return _tiles[pos.y + pos.x * _size.y];
}

void TiledMap::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);

	for(auto & tile : _tiles)
		tile->Render(tgt, states);
}

void TiledMap::Tick()
{
	Object::Tick();

	for(auto & unit : _units)
		unit->Tick();

	for(auto & tile : _tiles)
		tile->Tick();
}

bool TiledMap::HandleEvent(const sf::Event & ev)
{
	for(auto & unit : _units)
		if(unit->HandleEvent(ev))
			return true;

	return Object::HandleEvent(ev);
}

void TiledMap::OnHotpatch()
{	
	for(auto & tile : _tiles)
		tile->OnHotpatch();

	for(auto & unit : _units)
		unit->OnHotpatch();
	
	Object::OnHotpatch();
}

void TiledMap::SetPosition(Vector2f pos, bool update)
{
	_origin = pos;

	Object::SetPosition(pos, update);
}

void TiledMap::Move(Vector2f pos)
{
	_origin += pos;

	Object::Move(pos);
}

void TiledMap::SetUnit(TiledUnit * unit, Vector2i pos)
{
	auto & tile = Get(pos);
	if(tile->_unit)
		return;
	
	if(unit->_tile)
		unit->_tile->_unit = nullptr;

	unit->_map = this;
	tile->_unit = unit;
	unit->_tile = tile.get();

	TiledUnit::_adding_unit = true;
	unit->UpdatePosition();
	TiledUnit::_adding_unit = false;
}

void TiledMap::UpdatePosition()
{
	{
		TiledTile::CurrentMap = this;
		for(auto & tile : _tiles)
			tile->UpdatePosition();
		TiledTile::CurrentMap = nullptr;
	}

	Object::UpdatePosition();
}
}
