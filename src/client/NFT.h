#pragma once
#include "Object.h"

namespace Client
{
enum class NFT_Type
{
	Main,
	Category,
	Asset
};

struct NFT : Object
{
	NFT(const string & name, NFT_Type type);

	NFT(const NFT & nft) :
		Object(nft),
		_name(nft._name),
		_type(nft._type)
	{
	}

	~NFT() override;

	void OnHotpatch() override;
	void Tick() override;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	bool HandleEvent(const sf::Event & ev) override;
	void SetPosition(Vector2f pos, bool update) override;
	void UpdatePosition() override;
	void Move(Vector2f pos) override;

	NFT * Find(const string & name, NFT_Type type);

	string   _name;
	NFT_Type _type;

	unique_ptr<NFT> GenerateRandom();

	static unordered_map<string, unique_ptr<NFT>> List;
};
}
