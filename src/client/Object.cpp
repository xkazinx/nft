#include "pch.h"
#include "Object.h"
#include "Scene.h"
#include "TiledScene.h"
#include "Sprite.h"
#include "NFT.h"

namespace Client
{
Object::Object(const Type type, const string & id):
	_type(type)
{
	static UID uid_ = 0;

	_uid = uid_++;

	if(id.empty())
		SetID(format("{}_{}", enum_name(type), _uid));
	else
		SetID(id);

	OnHotpatch();
}

Object::Object(const Object & object)
{
	for(auto & child : object._objects)
	{
		auto & ref = *child.get();

		Client::Object * obj = nullptr;

		switch(child->_type)
		{
		// #create_object_type
			using enum ObjectType;

		case Sprite:
			obj = AddObject(make_unique<Client::Sprite>((Client::Sprite&)ref));
			continue;
		case Scene:
		case Scenes:
		case Map:
		case Tile:
		case Unit:
		case Object:
			assert(0); // has sub_objects
			break;
		case NFT:
			obj = AddObject(make_unique<Client::NFT>((Client::NFT&)ref));
			break;
		default: ;
			break;
		}

		if(!obj)
			obj = AddObject(make_unique<Client::Object>(ref));

		obj->_type = ref._type;
		obj->_uid = ref._uid; // #todo
		obj->_id = ref._id;
	}
}

Object::~Object()
= default;

void Object::OnHotpatch()
{
	UpdatePosition();

	for(auto & object : _objects)
		object->OnHotpatch();
}

void Object::Tick()
{
	for(auto & object : _objects)
		object->Tick();
}

void Object::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	for(auto & object : _objects)
		object->Render(tgt, states);
}

bool Object::HandleEvent(const sf::Event & ev)
{
	for(auto & object : _objects)
		if(object->HandleEvent(ev))
			return true;

	return false;
}

void Object::SetPosition(Vector2f pos, bool update)
{
	for(auto & object : _objects)
		object->SetPosition(pos, update);

	if(update)
	{
		UpdatePosition();

		for(auto & object : _objects)
			object->UpdatePosition();
	}
}

void Object::Move(Vector2f pos)
{
	UpdatePosition();

	for(auto & object : _objects)
	{
		object->Move(pos);
		object->UpdatePosition();
	}
}

void Object::SetScale(Vector2f value)
{
	for(auto & object : _objects)
		object->SetScale(value);
}

Object * Object::AddObject(Value object)
{
	_objects.emplace_back(std::move(object));

	return _objects.back().get();
}

void Object::RemoveObject(const string & id)
{
	erase_if(
		_objects,
		[&](const auto & object)
		{
			return object->_id == id;
		}
	);
}

void Object::UpdatePosition()
{
	for(auto & object : _objects)
		object->UpdatePosition();
}
}
