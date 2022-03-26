#pragma once
#include "Object.h"

namespace Client
{
class Sprite final : public Object
{
public:
	static unordered_map<string, Sprite>  List;
	static unordered_map<string, Texture> Textures;

	static Texture & GetTexture(const string & texture_name);

	static void Initialize();
	static void Deinitialize();

public:
	Sprite() :
		Object(ObjectType::Sprite, "Sprite")
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
		kazin::Log::Debug("Created sprite by copy");
	}

	Sprite(const string & texture_id) :
		Object(ObjectType::Sprite, "Sprite"),
		_sprite(GetTexture(texture_id))
	{
	}

	~Sprite() override;

public:
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	void Tick() override;
	bool HandleEvent(const sf::Event & ev) override;
	void OnHotpatch() override;
	void SetPosition(Vector2f pos, bool update = false) override;
	void Move(Vector2f pos) override;
	
	sf::Sprite _sprite;
};
}
