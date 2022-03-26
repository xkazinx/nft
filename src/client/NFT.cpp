#include "pch.h"
#include "NFT.h"

namespace Client
{
unordered_map<string, unique_ptr<NFT>> NFT::List;

NFT::NFT(const string & name, NFT_Type type):
	Object(ObjectType::NFT, "NFT"),
	_name(name), _type(type)
{
		
}

NFT::~NFT()
{
	
}

void NFT::OnHotpatch()
{
	Object::OnHotpatch();
}

void NFT::Tick()
{
	Object::Tick();
}

void NFT::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);
}

bool NFT::HandleEvent(const sf::Event & ev)
{
	return Object::HandleEvent(ev);
}

void NFT::SetPosition(Vector2f pos, bool update)
{
	Object::SetPosition(pos, update);
}

void NFT::UpdatePosition()
{
	Object::UpdatePosition();
}

void NFT::Move(Vector2f pos)
{
	Object::Move(pos);
}

NFT * NFT::Find(const string & name, NFT_Type type)
{
	for(auto & object : _objects)
	{
		if (object->_type != ObjectType::NFT)
			continue;

		auto nft = ((NFT*)object.get());
		if(nft->_type != type)
			continue;

		if(nft->_name == name)
			return nft;
	}

	return nullptr;
}
}
