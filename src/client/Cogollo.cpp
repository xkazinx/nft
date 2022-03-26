#include "pch.h"
#include "Cogollo.h"
#include "Sprite.h"

namespace Client
{
Cogollo::Cogollo() :
	NFT("cogollo", NFT_Type::Main)
{
	OnHotpatch();
}

Cogollo::~Cogollo()
{
}

void Cogollo::OnHotpatch()
{
	Object::OnHotpatch();
}

void Cogollo::Tick()
{
	Object::Tick();
}

void Cogollo::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);
}

bool Cogollo::HandleEvent(const sf::Event & ev)
{
	return Object::HandleEvent(ev);
}

void Cogollo::SetPosition(Vector2f pos, bool update)
{
	Object::SetPosition(pos, update);
}

void Cogollo::UpdatePosition()
{
	Object::UpdatePosition();
}

void Cogollo::Move(Vector2f pos)
{
	Object::Move(pos);
}
}
