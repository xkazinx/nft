#pragma once
#include "Object.h"

namespace Client
{
struct Sprite final : Object
{
	// By "<nft>/<category>/<file>.png" ('/' on every system)
	static unordered_map<string, unique_ptr<Sprite>> List;
	static unordered_map<string, Texture>            Textures;

	static unique_ptr<Sprite> & Add(const Path & file);

	static Texture & GetTexture(const string & texture_name);

	static void Initialize();
	static void Deinitialize();

	// (SFML 3: a sprite is made with its texture, so there is no empty one)
	Sprite(const Sprite & sprite) :
		Object(sprite),
		_sprite(sprite._sprite)
	{
	}

	Sprite(const Path & file) :
		Object(ObjectType::Sprite, "Sprite"),
		_sprite(GetTexture(file.generic_string()))
	{
	}

	Sprite(const sf::Texture & texture) :
		Object(ObjectType::Sprite, "Sprite"),
		_sprite(texture)
	{
	}

	Sprite(const sf::Sprite & sprite) :
		Object(ObjectType::Sprite, "Sprite"),
		_sprite(sprite)
	{
	}

	Sprite(const string & texture_id) :
		Object(ObjectType::Sprite, "Sprite"),
		_sprite(GetTexture(texture_id))
	{
	}

	~Sprite() override;

	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void Tick() override;
	bool HandleEvent(const sf::Event & ev) override;
	void OnHotpatch() override;
	void SetPosition(Vector2f pos, bool update = false) override;
	void Move(Vector2f pos) override;
	void SetScale(Vector2f value) override;

	sf::Sprite _sprite;
};
}
