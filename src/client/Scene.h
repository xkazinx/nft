#pragma once
#include "Object.h"

namespace Client
{
class Scene : public Object
{
public:
	virtual void RenderUI();

	explicit Scene(SceneID id = SceneID::None);
	~Scene() override = default;

	virtual void OnHotpatch();
	virtual void Tick();
	virtual void Render(sf::RenderTarget & tgt, sf::RenderStates states);
	virtual bool HandleEvent(const sf::Event & ev);

	const SceneID _id{};
};
}
