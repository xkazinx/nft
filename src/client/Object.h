#pragma once

namespace Client
{
class Object : public sf::Drawable
{
public:
	using Type = ObjectType;
	using UID = u32;

	Object(const Type type, const string & id);

	Object(const Object & object);

	Type   _type{};
	UID    _uid{};
	string _id{};

	~Object() override;

	virtual void OnHotpatch();
	virtual void Tick();
	virtual void Render(sf::RenderTarget & tgt, sf::RenderStates states = {});
	virtual bool HandleEvent(const sf::Event & ev);
	virtual void SetPosition(Vector2f pos, bool update);
	virtual void UpdatePosition();
	virtual void Move(Vector2f pos);

public:
	using Value = unique_ptr<Object>;
	vector<Value> _objects;

	Object * AddObject(Value object);
	void     RemoveObject(const string & id);

	template<typename T = Object>
	T * FindObject(const string & id)
	{
		for(auto & object : _objects)
		{
			if(object->_id == id)
				return (T*)(object.get());
		}

		return nullptr;
	}

	Value & BackObject()
	{
		return _objects.back();
	}

	void SetID(const string & id)
	{
		_id = id;
	}

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override
	{
		const_cast<Object*>(this)->Render(target, states);
	}
};
}
