#include "pch.h"
#include "Sprite.h"

namespace Client
{
unordered_map<string, Sprite>  Sprite::List;
unordered_map<string, Texture> Sprite::Textures;

Texture & Sprite::GetTexture(const string & texture_name)
{
	if(!Textures.contains(texture_name))
	{
		Textures.insert(std::make_pair(texture_name, Texture{}));
		Textures[texture_name].loadFromFile(texture_name);
	}

	return Textures[texture_name];
}

void Sprite::Initialize()
{
	List =
	{
		{
			"cogollo",
			Sprite{ "gfx/nug_full.png" }
		}
	};

	ifstream f("configs.json");

	json j;

	f >> j;

	for(auto & sprite : j["sprites"])
	{
		Path path {sprite.value<string>("file", "")};
		path = "data" / path;

		kazin::Log::Debug(path.filename().string());
		List.insert(std::make_pair(path.filename().string(), Sprite{path.string()}));
		//List[path.filename().string()] = {path.string()};
	}

	for(auto & pair : List)
		kazin::Log::Debug("Sprite: {}", pair.first);
}

void Sprite::Deinitialize()
{
}

Sprite::~Sprite()
= default;

void Sprite::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);

	tgt.draw(_sprite, states);
}

void Sprite::Tick()
{
	Object::Tick();
}

bool Sprite::HandleEvent(const sf::Event & ev)
{
	return Object::HandleEvent(ev);
}

void Sprite::OnHotpatch()
{
	Object::OnHotpatch();
}

void Sprite::SetPosition(Vector2f pos, bool update)
{
	_sprite.setPosition(pos);

	Object::SetPosition(pos, update);
}

void Sprite::Move(Vector2f pos)
{
	_sprite.move(pos);
	
	Object::Move(pos);
}
}
