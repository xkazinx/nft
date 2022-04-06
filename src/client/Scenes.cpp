#include "pch.h"
#include "Scenes.h"
#include "DummyScene.h"
#include "TiledScene.h"
#include "GenScene.h"

namespace Client
{
Scenes::Scenes() :
	Object(ObjectType::Scenes, "Scenes")
{
	//AddObject(make_unique<GenScene>());
	AddObject(make_unique<TiledScene>());
}

Scenes::~Scenes()
= default;

void Scenes::OnHotpatch()
{
	Object::OnHotpatch();
}

void Scenes::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);

	for(auto & object : _objects)
	{
		if(object->_type == ObjectType::Scene)
			((Scene*)object.get())->RenderUI();
	}
}

void Scenes::Tick()
{
	Object::Tick();
}

bool Scenes::HandleEvent(const sf::Event & ev)
{
	switch(ev.type)
	{
		using enum sf::Event::EventType;

	case KeyPressed:
		switch(ev.key.code)
		{
		case sf::Keyboard::S:
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				break;

			static underlying_type_t<ID> LastSceneID = enum_values<ID>()[0];
			if(++LastSceneID >= enum_count<ID>())
			{
				LastSceneID = enum_values<ID>()[0];
			}

			_objects.clear();
			AddObject(Create(ID(LastSceneID)));
			break;
		}
		}
		break;
	default: ;
	}

	return Object::HandleEvent(ev);
}

unique_ptr<Scene> Scenes::Create(ID id)
{
	switch(id)
	{
		using enum ID;

	case Dummy:
		return make_unique<DummyScene>();

	case PacMan:
		return make_unique<TiledScene>();

	case Gen:
		return make_unique<GenScene>();

	case None:
	default: ;
		break;
	}

	return make_unique<Scene>();
}
}
