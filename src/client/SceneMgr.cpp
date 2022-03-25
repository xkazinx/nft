#include "pch.h"
#include "SceneMgr.h"
#include "DummyScene.h"
#include "TiledScene.h"

namespace Client
{
SceneMgr::SceneMgr():
	Object(ObjectType::SceneMgr, "SceneMgr")
{
	AddObject(make_unique<TiledScene>());

	/*static auto scene = make_unique<TiledScene>();
	_ptr = scene.get();*/
}

SceneMgr::~SceneMgr()
= default;

void SceneMgr::OnHotpatch()
{
	if(_ptr)
		_ptr->OnHotpatch();
	
	Object::OnHotpatch();
}

void SceneMgr::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);

	for(auto & object : _objects)
	{
		if(object->_type == ObjectType::Scene)
			((TiledScene*)object.get())->RenderUI();
	}

	if(_ptr)
		_ptr->Render(tgt, states);
}

void SceneMgr::Tick()
{
	Object::Tick();

	if(_ptr)
		_ptr->Tick();
}

bool SceneMgr::HandleEvent(const sf::Event & ev)
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

	if(_ptr && _ptr->HandleEvent(ev))
		return true;

	return Object::HandleEvent(ev);
}

unique_ptr<Scene> SceneMgr::Create(ID id)
{
	switch(id)
	{
		using enum ID;

	case Dummy:
		return make_unique<DummyScene>();

	case PacMan:
		return make_unique<TiledScene>();

	case None:
	default: ;
		break;
	}

	return make_unique<Scene>();
}
}