#include "pch.h"
#include "Scene.h"
#include "App.h"

namespace Client
{
Scene::Scene(const SceneID id) :
	Object(ObjectType::Scene, string(enum_name(id))),
	_id(id)
{
}

void Scene::RenderUI()
{
	text::Render(format("Scene: {}", enum_name(_id)));

	if(!_keys.empty())
		text::Render(_keys, 18, sf::Color(220, 220, 220), { 10.f, g_res_y - 30.f });
}

void Scene::Render([[maybe_unused]] sf::RenderTarget & tgt, [[maybe_unused]] sf::RenderStates states)
{
	Object::Render(tgt, states);
}

void Scene::Render()
{
	Render(GetWindow(), {});
}

void Scene::Tick()
{
	Object::Tick();
}

bool Scene::HandleEvent([[maybe_unused]] const sf::Event & ev)
{
	return Object::HandleEvent(ev);
}

void Scene::HandleEvent(const void * const event)
{
	if(event)
		HandleEvent(*static_cast<const sf::Event *>(event));
}

void Scene::OnHotpatch()
{
	Object::OnHotpatch();
}
}
