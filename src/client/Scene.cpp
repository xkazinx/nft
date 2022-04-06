#include "pch.h"
#include "Scene.h"

namespace Client
{
Scene::Scene(const SceneID id) :
	Object(ObjectType::Scene, enum_name(id).data()),
	_id(id)
{
}

void Scene::RenderUI()
{
	text::Render(format("Scene: {}", enum_name(_id)));
}

void Scene::Render([[maybe_unused]] sf::RenderTarget & tgt, [[maybe_unused]] sf::RenderStates states)
{
	Object::Render(tgt, states);
}

void Scene::Tick()
{
	Object::Tick();
}

bool Scene::HandleEvent([[maybe_unused]] const sf::Event & ev)
{
	return Object::HandleEvent(ev);
}

void Scene::OnHotpatch()
{
		Object::OnHotpatch();
	}
}
